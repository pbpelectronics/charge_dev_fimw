/*
 * adc.h
 *
 *  Created on: 3 ����. 2013
 *      Author: ������
 */

#ifndef ADC_H_
#define ADC_H_

int currentMeasureNumber;
double uFromBattery;
double uToBattery;
double amperage;
double systemTemperature;

uint32_t uFromBatteryBuffer[2];
uint32_t uToBatteryBuffer[2];
uint32_t amperageBuffer;
uint32_t systemTemperatureBuffer;

void initADC();

#endif /* ADC_H_ */
