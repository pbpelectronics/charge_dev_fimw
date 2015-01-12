/*
 * boot_message.c
 *
 * Created: 20.01.2013 19:05:46
 *  Author: Олексій
 */
#include "pictures.h"
#include "../common/common.h"
#include "../led/led.h"
#include "images_printing.h"
#include "nokia1100_lcd_lib.h"
#include <math.h>
void bootMessage(void) {
	nlcd_Clear();
	int i;
	for (i = 0; i < 17; i++) {
		nlcd_Pict(0, 0, boot_image[i]);
		delayMs(10);
	}
}

void printMainImageDigits(char row, double val) {
	char xPosition = POSITION_MAIN_IMAGE_SECOND_PART_X;
	char yPosition = POSITION_MAIN_IMAGE_SECOND_PART_Y_ROW1;
	if (row == 2) {
		yPosition = POSITION_MAIN_IMAGE_SECOND_PART_Y_ROW2;
	}
	printDigits(xPosition, yPosition, val);
}

void printDigits(int xPosition, int yPosition, double val) {
	char integerPart = val;
	double fractionalPart = val - integerPart;

	if (integerPart >= 10) {
		char integerPartDigs[2];

		double buff = integerPart * 0.1;
		integerPartDigs[1] = buff;
		integerPartDigs[0] = (buff - integerPartDigs[1]) * 10;

		char fractionalPartDigs = fractionalPart * 10;

		nlcd_Pict(xPosition, yPosition, digitals[integerPartDigs[1]]);
		xPosition += WIDTH_DIGITAL_IMAGE;

		nlcd_Pict(xPosition, yPosition, digitals[integerPartDigs[0]]);
		xPosition += WIDTH_DIGITAL_IMAGE;

		nlcd_Pict(xPosition, yPosition, point);
		xPosition += WIDTH_POINT_IMAGE;

		nlcd_Pict(xPosition, yPosition, digitals[fractionalPartDigs]);
	} else {
		char integerPartDigs = integerPart;

		char fractionalPartDigs[2];
		fractionalPart = fractionalPart * 10;
		fractionalPartDigs[1] = fractionalPart;
		fractionalPartDigs[0] = (fractionalPart - fractionalPartDigs[1]) * 10;

		nlcd_Pict(xPosition, yPosition, digitals[integerPartDigs]);
		xPosition += WIDTH_DIGITAL_IMAGE;

		nlcd_Pict(xPosition, yPosition, point);
		xPosition += WIDTH_POINT_IMAGE;

		nlcd_Pict(xPosition, yPosition, digitals[fractionalPartDigs[1]]);
		xPosition += WIDTH_DIGITAL_IMAGE;

		nlcd_Pict(xPosition, yPosition, digitals[fractionalPartDigs[0]]);
	}
}
void printAdditionalMenuDigits(double val) {
	char integerPart = val;
	double fractionalPart = val - integerPart;

	char xPosition = ADDITIONAL_MENU_DIGITS_LEFT_MARGIN;
	if (integerPart >= 10) {
		char integerPartDigs[2];

		double buff = integerPart * 0.1;
		integerPartDigs[1] = buff;
		integerPartDigs[0] = (buff - integerPartDigs[1]) * 10;

		char fractionalPartDigs = fractionalPart * 10;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[integerPartDigs[1]]);
		xPosition += ADDITIONAL_MENU_DIGITS_WIDTH;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[integerPartDigs[0]]);
		xPosition += ADDITIONAL_MENU_DIGITS_WIDTH;

//		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, point);
//		xPosition += WIDTH_POINT_IMAGE;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[fractionalPartDigs]);
	} else {
		char integerPartDigs = integerPart;

		char fractionalPartDigs[2];
		fractionalPart = fractionalPart * 10;
		fractionalPartDigs[1] = fractionalPart;
		fractionalPartDigs[0] = (fractionalPart - fractionalPartDigs[1]) * 10;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[integerPartDigs]);
		xPosition += ADDITIONAL_MENU_DIGITS_WIDTH;

//		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, point);
//		xPosition += WIDTH_POINT_IMAGE;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[fractionalPartDigs[1]]);
		xPosition += ADDITIONAL_MENU_DIGITS_WIDTH;

		nlcd_Pict(xPosition, ADDITIONAL_MENU_DIGITS_TOP_MARGIN, additionalMenuDigitals[fractionalPartDigs[0]]);
	}
}

void printAdditionalMenuAnimation(int value) {
	char animationIdx;
	for (animationIdx = value; animationIdx < 6; animationIdx++) {
		nlcd_Pict(ADDITIONAL_MENU_RIGTH_ANIMATION_LEFT_MARGIN + animationIdx * ADDITIONAL_MENU_ANIMATION_WIDTH, ADDITIONAL_MENU_RIGHT_ANIMATION_TOP_MARGIN,
				additionalMenuRightAnimation[0]);
		nlcd_Pict(ADDITIONAL_MENU_LEFT_ANIMATION_LEFT_MARGIN - animationIdx * ADDITIONAL_MENU_ANIMATION_WIDTH, ADDITIONAL_MENU_LEFT_ANIMATION_TOP_MARGIN,
				additionalMenuLeftAnimation[0]);
	}
	for (animationIdx = 0; animationIdx < value; animationIdx++) {
		nlcd_Pict(ADDITIONAL_MENU_RIGTH_ANIMATION_LEFT_MARGIN + animationIdx * ADDITIONAL_MENU_ANIMATION_WIDTH, ADDITIONAL_MENU_RIGHT_ANIMATION_TOP_MARGIN,
				additionalMenuRightAnimation[animationIdx+1]);
		nlcd_Pict(ADDITIONAL_MENU_LEFT_ANIMATION_LEFT_MARGIN - animationIdx * ADDITIONAL_MENU_ANIMATION_WIDTH, ADDITIONAL_MENU_LEFT_ANIMATION_TOP_MARGIN,
				additionalMenuLeftAnimation[animationIdx+1]);
	}

}

//print template of main image (i=.....A; U=...V)
void printMainImageTemplate() {
	nlcd_Pict(POSITION_MAIN_IMAGE_FIRST_PART_X, POSITION_MAIN_IMAGE_FIRST_PART_Y, main_image_first_part);
	nlcd_Pict(POSITION_MAIN_IMAGE_THIRD_PART_X, POSITION_MAIN_IMAGE_THIRD_PART_Y, main_image_third_part);
}

void printBatteryWaitImage() {
	nlcd_Pict(0, 0, bat_not_conn_image);
}
void printBattaryImage(char val) {
	nlcd_Pict(POSITION_BATTERY_IMAGE_X, POSITION_MAIN_BATTERY_IMAGE_Y, battery_image[val]);
}

void printChangeAmperageImage(int imageIdx) {
	int idx;
	for (idx = 1; idx <= imageIdx; idx++) {
		nlcd_Pict(POWER_IMAGE_LEFT_INDENT + POWER_IMAGE_WIDTH * idx, POWER_IMAGE_Y_POSITION, power_images[idx]);
	}
	for (idx = imageIdx + 1; idx < 11; idx++) {
		nlcd_Pict(POWER_IMAGE_LEFT_INDENT + POWER_IMAGE_WIDTH * idx, POWER_IMAGE_Y_POSITION, power_images[0]);
	}
}

void printInitChangeAmperageMenu() {
	nlcd_Clear();
	nlcd_Pict(MENU_I_SYMBOL_LEFT_INDENT, MENU_I_SYMBOL_TOP_INDENT, menuISymbol);
	nlcd_Pict(MENU_AMPERAGE_SYMBOL_LEFT_INDENT, MENU_AMPERAGE_SYMBOL_TOP_INDENT, menuAmperageSymbol);
}

void printChangeAmperageMenuDigits(double value) {
	printDigits(MENU_DIGITS_LEFT_INDENT, MENU_DIGITS_TOP_INDENT, value);
}

//void printAdditionalMenuDigits(double value){
//	nlcd_Clear();
//	nl
//}
void printTestImage() {
	nlcd_Pict(1, 1, test_pict);
}
