/*
 * led.h
 *
 *  Created on: 30 ���. 2013
 *      Author: ������
 */

#ifndef LED_H_
#define LED_H_

struct Led{
	uint32_t perifId;
	struct GPIO_TypeDef * port;
	uint16_t pin;
} led1Green, led1Blue, led1Red, led2Green, led2Blue, led2Red;

void initLeds();
void ledSwitchOn(struct Led led);
void ledSwitchOff(struct Led led);

#endif /* LED_H_ */
