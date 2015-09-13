/*
 * common.h
 *
 *  Created on: 30 Ã�Â²Ã�ÂµÃ‘â‚¬. 2013
 *      Author: Ã�Å¾Ã�Â»Ã�ÂµÃ�ÂºÃ‘ï¿½Ã‘â€“Ã�Â¹
 */

#ifndef COMMON_H_
#define COMMON_H_
#include "stm32f10x.h"

//#define MAX_AMPERAGE 0.2
#define MAX_SYSTEM_TEMPERATURE 60

//min voltage when system initialize battery
#define MIN_BATTERY_VOLTAGE 3
#define CHARGED_BATTERY_VOLTAGE 14.8
#define DISCHARGED_BATTERY_VOLTAGE 9.0

#define BATT_SIG_FREQUENCY 100
#define MAX_BATT_POWER  100
#define BATT_POWER_INCREMENT 5
#define MIN_BATT_POWER 0
#define BATT_POWER_OUT TIM4->CCR4

//voltage when charger starts reduce amperage
#define SECOND_CHARGING_STEP_VOLTAGE  14.5
#define SECOND_CHARGING_STEP_KOEF  0.01 //=1/20

//delay for press menu for go to change amperage menu
#define MENU_CHANGE_AMPERAGE_DELAY 0
//delay for go to additional menu
#define MENU_ADDITIONAL_DELAY 1000
//delay while menu button is scanning
#define MENU_BUTTON_PRESSED_MAX_DELAY 3000

#define bool	_Bool
#define true	1
#define false	0
uint64_t time_ms;
uint8_t batteryPower;

double uFromBattery;
double uToBattery;
double amperage;
double systemTemperature;
int userEnteredBatteryPower;

void delayMs(int delayTime);
int getMax(int val1, int val2);
double calculateRation(int input, int maxValue);
void Int2Str(char *pStr, unsigned int value, int charCount);

#endif /* COMMON_H_ */
