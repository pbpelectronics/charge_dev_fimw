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

double calculateRation(int input, int maxValue) {
	double result = input / (double) maxValue;
	return result > 0 ? result : 0;
}
