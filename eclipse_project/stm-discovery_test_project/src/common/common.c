#include "common.h"
#include "../adc/adc.h"
#include "../display/images_printing.h"

void delayMs(int delayTime) {
	uint64_t nextTime = time_ms + delayTime;
	while (time_ms < nextTime) {
		__NOP();
	}
}

int getMax(int val1, int val2) {
	if (val1 >= val2) {
		return val1;
	} else {
		return val2;
	}
}

void Int2Str(char *pStr, unsigned int value, int charCount) {
	pStr = pStr + (charCount - 1);
	do {
		*pStr-- = (value % 10) + '0';
		value /= 10;
	} while (charCount--);
}

void checkIfBattaryIsConnected() {
	if (isBattaryConnected){
		return;
	}
	BATTARY_POWER_OUT = 0;
	printBatteryWaitImage();
	while (!isBattaryConnected) {
//		reswitchLed(LED1, 0, 0, MAX_LED_POWER, 1000);
//		reswitchLed(LED1, 0, MAX_LED_POWER, 0, 1000);
//		reswitchLed(LED1, MAX_LED_POWER, 0, 0, 1000);
	}
	nlcd_Clear();
	printMainImageTemplate();
}


void checkAmperage() {
	if (amperage > MAX_AMPERAGE) {
		BATTARY_POWER_OUT = 0;
	}
}
