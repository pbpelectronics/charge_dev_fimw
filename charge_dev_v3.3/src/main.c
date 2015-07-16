#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_adc.h"
#include "misc.h"

#include "lcd_1100/nokia1100_lcd_lib.h"
#include "display/images_printing.h"
#include "common/common.h"
#include "adc/adc.h"
#include "timers/timers.h"
#include "encoder/encoder.h"
#include "led/led.h"

void changeAmperageMenu() {
	nlcd_Clear();
	printInitChangeAmperageMenu();
	printChangeAmperageMenuDigits(amperage);
	uint64_t timeStampMenu = time_ms;
	uint64_t timeStampDisplayRefr = time_ms;
	while (!isMenuEncoderPressed() && time_ms - timeStampMenu < 5000) {
		if (time_ms - timeStampDisplayRefr > 500) {
			printChangeAmperageMenuDigits(amperage);
			timeStampDisplayRefr = time_ms;
		}
		if (encoderIsActive) {
			timeStampMenu = time_ms;
			if (getEncoderDirection() == FORWARD) {
				if (BATTARY_POWER_OUT > 95) {
					BATTARY_POWER_OUT = 100;
				} else {
					BATTARY_POWER_OUT += 5;
				}
			} else if (getEncoderDirection() == BACKWARD) {
				if (BATTARY_POWER_OUT < 1) {
					BATTARY_POWER_OUT = 0;
				} else {
					BATTARY_POWER_OUT -= 5;
				}
			}
			printChangeAmperageImage(batteryPower / 10);
		}
	}
	while (isMenuEncoderPressed()) {
		__NOP();
	}
	nlcd_Clear();
}


bool isBattaryConnected() {
	return uFromBattery >= MIN_BATTERY_VOLTAGE;
}

void checkIfBattaryIsConnected() {
	if (isBattaryConnected()) {
		return;
	}

	BATTARY_POWER_OUT = 0;
	printBatteryWaitImage();
	while (!isBattaryConnected()) {
		__NOP();
	}
	nlcd_Clear();
	printMainImageTemplate();
}

void additinalMenu() {
	while (isMenuEncoderPressed()) {
		__NOP();
	}
	nlcd_Clear();
	printAdditionalMenuDigits(amperage);
	char animationIdx = 0;
	while (!isMenuEncoderPressed()) {
		if (++animationIdx > 5) {
			animationIdx = 0;
		}
		printAdditionalMenuAnimation(animationIdx);
		delayMs(500);
	}
	while (isMenuEncoderPressed()) {
		__NOP();
	}
	nlcd_Clear();
}

int main(void) {
	SystemCoreClockUpdate();
	__enable_irq();
	initTimerCounter();
	nlcd_Init();
//	bootMessage();
	initLeds();
	initADC();
	initPWM4();
	initEncoder();
	initCooler();
	nlcd_Clear();
	clearMeasuringBuffers();
	printMainImageTemplate();
	int power = 0;
	while (1) {
		delayMs(1000);
		BATTARY_POWER_OUT = power;
		power+=1;
		checkIfBattaryIsConnected();
		if (encoderIsActive) {
			changeAmperageMenu();
			printMainImageTemplate();
		}
		printMainImageDigits(1, uFromBattery);
		printMainImageDigits(2, amperage);
	}
	return 0;
}
