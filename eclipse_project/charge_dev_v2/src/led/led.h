/*
 * led.h
 *
 *  Created on: 30 βεπ. 2013
 *      Author: Ξλεκρ³ι
 */

#ifndef LED_H_
#define LED_H_

#define LED1_RED
#define LED1_GREEN 500
#define LED1_BLUE

#define LED2_RED
#define LED2_GREEN 500
#define LED2_BLUE

struct Led{
	uint32_t perifId;
	struct GPIO_TypeDef * port;
	uint16_t pin;
} led1Green, led1Blue, led1Red, led2Green, led2Blue, led2Red;

void initLeds();
void ledSwitchOn(struct Led led);
void ledSwitchOff(struct Led led);

#endif /* LED_H_ */
