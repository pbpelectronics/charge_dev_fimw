/*
 * adc.c
 *
 *  Created on: 3 жовт. 2013
 */

#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "../common/common.h"
#include "adc.h"
#include "../led/led.h"

double convertADCBufferToAmperageValue(uint32_t adcBufferVal) {
	return adcBufferVal * AMPERAGE_ADC_CONVERSATION_COEFFICIENT / MEASURES_NUMBER;
}

double convertADCBufferToVoltageValue(uint32_t adcBufferVal, uint32_t measuresCount) {
	return adcBufferVal * VOLTAGE_ADC_CONVERSATION_COEFFICIENT / measuresCount;
}

double convertADCBufferToTemperatureValue(uint32_t adcBufferVal) {
	long adcBufferVal0 = adcBufferVal / MEASURES_NUMBER;
	return SYS_TEMP0 - (SYS_TEMP_V0 - adcBufferVal0) * 0.203;
}

void clearMeasuringBuffers() {
	uFromBatteryBuffer[0] = 0;
	uFromBatteryBuffer[1] = 0;
	uToBatteryBuffer[0] = 0;
	uToBatteryBuffer[1] = 0;
	amperageBuffer = 0;
	systemTemperatureBuffer = 0;
	currentMeasureNumber = 0;
}

void handleShortSircuit() {
	ledErrorSwitchOn();
	BATT_POWER_OUT = 0;
}

void ADC1_IRQHandler(void) {
	if (ADC_GetITStatus(ADC1, ADC_IT_AWD) != RESET) {
		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
		handleShortSircuit();
		return;
	}
	ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
	int currentVoltage = ADC_GetInjectedConversionValue(ADC1, VOLTAGE_INJECTED_CHANNEL);
	if (currentVoltage > THRESHOLD_VOLTAGE) {
		uToBatteryBuffer[0] += currentVoltage;
		uToBatteryBuffer[1]++;
	} else {
		uFromBatteryBuffer[0] += currentVoltage;
		uFromBatteryBuffer[1]++;
	}

	int currAmp = ADC_GetInjectedConversionValue(ADC1, AMPERAGE_INJECTED_CHANNEL);

	amperageBuffer += ADC_GetInjectedConversionValue(ADC1, AMPERAGE_INJECTED_CHANNEL);
	systemTemperatureBuffer += ADC_GetInjectedConversionValue(ADC1, TEMPERATURE_INJECTED_CHANNEL);

	if ((++currentMeasureNumber) > MEASURES_NUMBER) {
		uFromBattery = convertADCBufferToVoltageValue(uFromBatteryBuffer[0], uFromBatteryBuffer[1]);

		uToBattery = convertADCBufferToVoltageValue(uToBatteryBuffer[0], uToBatteryBuffer[1]);
		amperage = convertADCBufferToAmperageValue(amperageBuffer);
		systemTemperature = convertADCBufferToTemperatureValue(systemTemperatureBuffer);
		clearMeasuringBuffers();
//		checkAmperage();
		checkSystemTemperature();
	}
}

//void checkAmperage() {
//	if (amperage > MAX_AMPERAGE) {
//		BATT_POWER_OUT = 0;
//		ledSwitchOn(led1Red);
//	}
//}

void initADC() {
	uFromBattery = 0;
	uToBattery = 0;
	amperage = 0;
	systemTemperature = 0;
	currentMeasureNumber = 0;

	clearMeasuringBuffers();

	ADC_DeInit(ADC1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = VOLTAGE_INPUT_PIN | AMPERAGE_INPUT_PIN | TEMPERATURE_INPUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 3;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* Set injected sequencer length */
	ADC_InjectedSequencerLengthConfig(ADC1, 3);

	/* ADC1 injected channel Configuration */
	ADC_InjectedChannelConfig(ADC1, VOLTAGE_ADC_CHANNEL, 1, ADC_SampleTime_28Cycles5);
	ADC_InjectedChannelConfig(ADC1, AMPERAGE_ADC_CHANNEL, 3, ADC_SampleTime_28Cycles5);
	ADC_InjectedChannelConfig(ADC1, TEMPERATURE_ADC_CHANNEL, 2, ADC_SampleTime_28Cycles5);

	/* ADC1 injected external trigger configuration */
	ADC_ExternalTrigInjectedConvConfig(ADC1, ADC_ExternalTrigInjecConv_None);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while (ADC_GetResetCalibrationStatus(ADC1)) {
		__NOP();
	}

	//enable watchdog to piling amperage
	ADC_AnalogWatchdogSingleChannelConfig(ADC1, AMPERAGE_ADC_CHANNEL);
	ADC_AnalogWatchdogThresholdsConfig(ADC1, 4023, 0);
	ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleInjecEnable);

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable ADC1_2 IRQChannel */
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable JEOC interrupt */
	ADC_ITConfig(ADC1, ADC_IT_JEOC, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while (ADC_GetCalibrationStatus(ADC1))
		__NOP();

	ADC_SoftwareStartInjectedConvCmd(ADC1, ENABLE);
}

