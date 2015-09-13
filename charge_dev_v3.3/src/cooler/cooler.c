#include "cooler.h"
#include "stm32f10x_gpio.h"
#include "../common/common.h"
#include "../led/led.h"

void initCooler() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(COOLER_RCC_PERIPH_PORT, ENABLE);
	GPIO_InitStructure.GPIO_Pin = COOLER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(COOLER_PORT, &GPIO_InitStructure);
}

void enableCooler() {
	GPIO_SetBits(COOLER_PORT, COOLER_PIN);
}

void disableCooler() {
	GPIO_ResetBits(COOLER_PORT, COOLER_PIN);
}

void checkSystemTemperature() {
	if (systemTemperature >= TEMPERATURE_FOR_ENABLING_COOL) {
		enableCooler();
	}
	if (systemTemperature <= TEMPERATURE_FOR_DISABLING_COOL) {
		disableCooler();
	}
	if (systemTemperature >= MAX_SYSTEM_TEMPERATURE) {
		if (BATT_POWER_OUT > 0) {
			BATT_POWER_OUT--;
		}
		ledSwitchOn(led1Red);
	} else {
		if (BATT_POWER_OUT < userEnteredBatteryPower) {
			BATT_POWER_OUT++;
		}
		ledSwitchOff(led1Red);
	}
}
