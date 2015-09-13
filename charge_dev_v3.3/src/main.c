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

//change amperage menu. Returns new amperage value
void changePowerMenu() {
	int result = BATT_POWER_OUT;
	userEnteredBatteryPower = BATT_POWER_OUT;
	nlcd_Clear();
	printInitChangeAmperageMenu();
	printChangeAmperageMenuDigits(amperage);
	printPowerValueImage(calculateRation(result, MAX_BATT_POWER));
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
				result += BATT_POWER_INCREMENT;
			} else if (getEncoderDirection() == BACKWARD) {
				result -= BATT_POWER_INCREMENT;
			}
			int maxAllowedPower = getMaxAllowedPower();
			if (result > maxAllowedPower) {
				result = maxAllowedPower;
			}
			if (result < MIN_BATT_POWER) {
				result = MIN_BATT_POWER;
			}
			printPowerValueImage(calculateRation(result, MAX_BATT_POWER));
			userEnteredBatteryPower = result;
			BATT_POWER_OUT = result;
		}
	}
	while (isMenuEncoderPressed()) {
		__NOP();
	}
	nlcd_Clear();
}

//returns max out battery power based on battery voltage and temperature
int getMaxAllowedPower() {
	if (systemTemperature >= MAX_SYSTEM_TEMPERATURE) {
		return BATT_POWER_OUT;
	}
	if (uFromBattery >= SECOND_CHARGING_STEP_VOLTAGE) {
		return calculateMaxPowerForSecondCharginStep();
	}
	return MAX_BATT_POWER;
}

//calculates max battery power for second charging step (when power is
//inversely proportional to the voltage)
int calculateMaxPowerForSecondCharginStep() {
	return MAX_BATT_POWER - MAX_BATT_POWER * uFromBattery * SECOND_CHARGING_STEP_KOEF;
}

bool isBattaryConnected() {
	return uFromBattery >= MIN_BATTERY_VOLTAGE;
}

void checkIfBattaryIsConnected() {
	if (isBattaryConnected()) {
		return;
	}

	BATT_POWER_OUT = 0;
	printBatteryWaitImage();
	ledErrorSwitchOn();
	while (!isBattaryConnected()) {
		__NOP();
	}
	ledErrorSwitchOff();
	BATT_POWER_OUT = userEnteredBatteryPower;
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

void indicateBatteryIsChanged() {
	ledSwitchOn(led1Green);
	printBatteryIsChargedImage();
	while (isBattaryConnected()) {
		__NOP();
	}
	ledSwitchOff(led1Green);
}

void showMainWindow() {
	printMainImageTemplate();
	printBattaryChargingImage(uFromBattery / CHARGED_BATTERY_VOLTAGE);
	printMainImageDigits(1, uFromBattery);
	printMainImageDigits(2, amperage);
}

bool isBattaryCharged() {
	return uFromBattery >= CHARGED_BATTERY_VOLTAGE;
}

int main(void) {
	SystemCoreClockUpdate();
	__enable_irq();
	initTimerCounter();
	nlcd_Init();
	initLeds();
	initADC();
	initPWM4();
	initEncoder();
	initCooler();
	clearMeasuringBuffers();
	userEnteredBatteryPower = 0;
	while (1) {
		nlcd_Clear();
		checkIfBattaryIsConnected();
		showMainWindow();
		while (!isBattaryCharged()) {
			checkIfBattaryIsConnected();
			if (encoderIsActive) {
				changePowerMenu();
				showMainWindow();
			}
			printBattaryChargingImage(
					calculateRation((uFromBattery - DISCHARGED_BATTERY_VOLTAGE),
							(CHARGED_BATTERY_VOLTAGE - DISCHARGED_BATTERY_VOLTAGE)));
			printMainImageDigits(1, uFromBattery);
			printMainImageDigits(2, amperage);
		}
		indicateBatteryIsChanged();
	}
	return 0;
}
