#include "stm_lib/inc/stm32f10x_gpio.h"
#include "stm_lib/inc/stm32f10x_rcc.h"
#include "stm_lib/inc/stm32f10x_adc.h"
#include "common.h"

void initADCPort() {
	GPIO_InitTypeDef initStructure;
	initStructure.GPIO_Mode = GPIO_Mode_AIN;
	initStructure.GPIO_Pin = GPIO_Pin_0 | AMPERMETER_INPUT_PIN
			| TEMPERATURE_INPUT_PIN;
	initStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(ADC_INPUT_PORT, &initStructure);
}

void initPorts() {
	initADCPort();
}

void initADC() {
	RCC_ADCCLKConfig (RCC_PCLK2_Div2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef adcInitStructure;
	adcInitStructure.ADC_ContinuousConvMode = DISABLE;
	adcInitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	adcInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adcInitStructure.ADC_Mode = ADC_Mode_InjecSimult;
	adcInitStructure.ADC_NbrOfChannel = 1;
	adcInitStructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &adcInitStructure);

	ADC_InjectedChannelConfig(ADC1, 0, 1, ADC_SampleTime_1Cycles5);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1))
		;

	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1))
		;
}

void enablePorts() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}
