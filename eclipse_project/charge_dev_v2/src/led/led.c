/*
 * led.c
 *
 *  Created on: 30 βεπ. 2013
 *      Author: Ξλεκρ³ι
 */
#include "stm32f10x.h"
#include "led.h"
void initPort(struct Led led) {
	RCC_APB2PeriphClockCmd(led.perifId, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = led.pin;
	GPIO_Init(led.port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void initLeds() {
	led1Blue.perifId = RCC_APB2Periph_GPIOB;
	led1Blue.port = GPIOB;
	led1Blue.pin = GPIO_Pin_14;

	led1Green.perifId = RCC_APB2Periph_GPIOB;
	led1Green.port = GPIOB;
	led1Green.pin = GPIO_Pin_15;

	led1Red.perifId = RCC_APB2Periph_GPIOC;
	led1Red.port = GPIOC;
	led1Red.pin = GPIO_Pin_6;

	led2Blue.perifId = RCC_APB2Periph_GPIOC;
	led2Blue.port = GPIOC;
	led2Blue.pin = GPIO_Pin_7;

	led2Green.perifId = RCC_APB2Periph_GPIOC;
	led2Green.port = GPIOC;
	led2Green.pin = GPIO_Pin_8;

	led2Red.perifId = RCC_APB2Periph_GPIOC;
	led2Red.port = GPIOC;
	led2Red.pin = GPIO_Pin_9;

	initPort(led1Blue);
	initPort(led1Green);
	initPort(led1Red);
	initPort(led2Blue);
	initPort(led2Green);
	initPort(led2Red);
}
;
void ledSwitchOn(struct Led led) {
	GPIO_SetBits(led.port, led.pin);
}

void ledSwitchOff(struct Led led) {
	GPIO_ResetBits(led.port, led.pin);
}

//void switchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower) {
//	clearLed(led);
//	led->LED_BLUE = bluePower;
//	led->LED_GREEN = greenPower;
//	led->LED_RED = redPower;
//}
//
//void reswitchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower, int timeout) {
//	clearLed(led);
//	int maxPower = getMax(bluePower, getMax(greenPower, redPower));
//	int delay = timeout / maxPower;
//	if (delay == 0) {
//		delay = 1;
//	}
//	for (int ledPower = 0; ledPower < maxPower; ledPower++) {
//		if (bluePower > ledPower) {
//			led->LED_BLUE = ledPower;
//		}
//		if (greenPower > ledPower) {
//			led->LED_GREEN = ledPower;
//		}
//		if (redPower > ledPower) {
//			led->LED_RED = ledPower;
//		}
//		delayMs(delay);
//	}
//	for (int ledPower = maxPower; ledPower >=0; ledPower--) {
//		if (bluePower > ledPower) {
//			led->LED_BLUE = ledPower;
//		}
//		if (greenPower > ledPower) {
//			led->LED_GREEN = ledPower;
//		}
//		if (redPower > ledPower) {
//			led->LED_RED = ledPower;
//		}
//		delayMs(delay);
//	}
//}
//
//void clearLed(TIM_TypeDef * led) {
//	led->LED_RED = 0;
//	led->LED_GREEN = 0;
//	led->LED_BLUE = 0;
//}
