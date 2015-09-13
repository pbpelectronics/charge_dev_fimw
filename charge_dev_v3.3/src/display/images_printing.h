/*
 * images_printing.h
 *
 *  Created on: 3 Ð»Ð¸Ð¿. 2013
 *      Author: ÑœÐ»ÐµÐºÑ�â‰¥Ð¹
 */
#ifndef _IMAGES_PRINTING_H_
#define _IMAGES_PRINTING_H_

void bootMessage(void);
void printMainImageDigits(char row, double val);
void printMainImageTemplate();
void printBattaryImage(char val);
void printTestImage();
void printBatteryWaitImage();
void printBatteryIsChargedImage();
void printChangeAmperageImage(int imageIdx);
void printInitChangeAmperageMenu();
void printAdditionalMenuDigits(double value);
void printAdditionalMenuDigits(double val);
#endif
