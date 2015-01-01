/*
 * led.c
 *
 *  Created on: 30 βεπ. 2013
 *      Author: Ξλεκρ³ι
 */
#include "../common/common.h"
#include "stm32f10x.h"

void switchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower) {
	clearLed(led);
	led->LED_BLUE = bluePower;
	led->LED_GREEN = greenPower;
	led->LED_RED = redPower;
}

void reswitchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower, int timeout) {
	clearLed(led);
	int maxPower = getMax(bluePower, getMax(greenPower, redPower));
	int delay = timeout / maxPower;
	if (delay == 0) {
		delay = 1;
	}
	for (int ledPower = 0; ledPower < maxPower; ledPower++) {
		if (bluePower > ledPower) {
			led->LED_BLUE = ledPower;
		}
		if (greenPower > ledPower) {
			led->LED_GREEN = ledPower;
		}
		if (redPower > ledPower) {
			led->LED_RED = ledPower;
		}
		delayMs(delay);
	}
	for (int ledPower = maxPower; ledPower >=0; ledPower--) {
		if (bluePower > ledPower) {
			led->LED_BLUE = ledPower;
		}
		if (greenPower > ledPower) {
			led->LED_GREEN = ledPower;
		}
		if (redPower > ledPower) {
			led->LED_RED = ledPower;
		}
		delayMs(delay);
	}
}

void clearLed(TIM_TypeDef * led) {
	led->LED_RED = 0;
	led->LED_GREEN = 0;
	led->LED_BLUE = 0;
}
