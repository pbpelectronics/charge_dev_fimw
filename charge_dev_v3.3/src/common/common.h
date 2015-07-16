/*
 * common.h
 *
 *  Created on: 30 вер. 2013
 *      Author: Олексій
 */

#ifndef COMMON_H_
#define COMMON_H_
#include "stm32f10x.h"

#define MAX_AMPERAGE 0.2

//min voltage when system initialize battery
#define MIN_BATTERY_VOLTAGE 3

#define BATT_SIG_FREQUENCY 100
#define MAX_BATT_POWER  100
#define BATTARY_POWER_OUT TIM4->CCR4

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

void delayMs(int delayTime);
int getMax(int val1, int val2);
void Int2Str(char *pStr, unsigned int value, int charCount);

#endif /* COMMON_H_ */
