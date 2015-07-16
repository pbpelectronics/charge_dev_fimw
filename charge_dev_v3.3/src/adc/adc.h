/*
 * adc.h
 *
 *  Created on: 3 жовт. 2013
 */

#ifndef ADC_H_
#define ADC_H_

#define VOLTAGE_INJECTED_CHANNEL ADC_InjectedChannel_1
#define AMPERAGE_INJECTED_CHANNEL ADC_InjectedChannel_3
#define TEMPERATURE_INJECTED_CHANNEL ADC_InjectedChannel_2
#define VOLTAGE_INPUT_PIN GPIO_Pin_0
#define AMPERAGE_INPUT_PIN GPIO_Pin_2
#define TEMPERATURE_INPUT_PIN GPIO_Pin_1
#define VOLTAGE_ADC_CHANNEL ADC_Channel_0
#define AMPERAGE_ADC_CHANNEL ADC_Channel_2
#define TEMPERATURE_ADC_CHANNEL ADC_Channel_1

//constants for thermometer
#define SYS_TEMP_V0 2570
#define SYS_TEMP0 36

#define AMPERAGE_ADC_CONVERSATION_COEFFICIENT 0.0027645
#define VOLTAGE_ADC_CONVERSATION_COEFFICIENT 0.00995393
#define TEMPERATURE_ADC_CONVERSATION_COEFFICIENT 0.00995393

//value that define kind of voltage: from battery or to battery
#define THRESHOLD_VOLTAGE 1507
//number of steps for exact measuring U, I and T values
#define MEASURES_NUMBER 5000

int currentMeasureNumber;

uint32_t uFromBatteryBuffer[2];
uint32_t uToBatteryBuffer[2];
uint32_t amperageBuffer;
uint32_t systemTemperatureBuffer;

void initADC();

#endif /* ADC_H_ */
