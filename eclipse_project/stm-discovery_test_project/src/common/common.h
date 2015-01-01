/*
 * common.h
 *
 *  Created on: 30 βεπ. 2013
 *      Author: Ξλεκρ³ι
 */

#ifndef COMMON_H_
#define COMMON_H_
#include "stm32f10x.h"

#define MAX_AMPERAGE 10

#define VOLTAGE_INJECTED_CHANNEL ADC_InjectedChannel_1
#define AMPERAGE_INJECTED_CHANNEL ADC_InjectedChannel_2
#define TEMPERATURE_INJECTED_CHANNEL ADC_InjectedChannel_3
#define VOLTAGE_INPUT_PIN GPIO_Pin_0
#define AMPERAGE_INPUT_PIN GPIO_Pin_1
#define TEMPERATURE_INPUT_PIN GPIO_Pin_2
#define VOLTAGE_ADC_CHANNEL ADC_Channel_0
#define AMPERAGE_ADC_CHANNEL ADC_Channel_1
#define TEMPERATURE_ADC_CHANNEL ADC_Channel_2

//constants for thermometer
#define SYS_TEMP_V0 938
#define SYS_TEMP0 36

//min voltage when system initialize battery
#define MIN_BATTERY_VOLTAGE 3

#define MAX_LED_POWER 1000
#define LED_FREQUENCY 500
#define LED1 TIM3
#define LED_RED CCR3
#define LED_GREEN CCR2
#define LED_BLUE CCR1

#define BATT_SIG_FREQUENCY 100
#define MAX_BATT_POWER  100
#define BATTARY_POWER_OUT TIM3->CCR3

#define AMPERAGE_ADC_CONVERSATION_COEFFICIENT 0.0027645
#define VOLTAGE_ADC_CONVERSATION_COEFFICIENT 0.00995393
#define TEMPERATURE_ADC_CONVERSATION_COEFFICIENT 0.00995393

//delay for press menu for go to change amperage menu
#define MENU_CHANGE_AMPERAGE_DELAY 0
//delay for go to additional menu
#define MENU_ADDITIONAL_DELAY 1000
//delay while menu button is scanning
#define MENU_BUTTON_PRESSED_MAX_DELAY 3000

//value that define kind of voltage: from battery or to battery
#define THRESHOLD_VOLTAGE 1000
//number of steps for exact measuring U, I and T values
#define MEASURES_NUMBER 5000

#define bool	_Bool
#define true	1
#define false	0
uint64_t time_ms;
uint8_t batteryPower;
bool isBattaryConnected;

void delayMs(int delayTime);
int getMax(int val1, int val2);
void Int2Str(char *pStr, unsigned int value, int charCount);
void checkAmperage();
void checkIfBattaryIsConnected();

#endif /* COMMON_H_ */
