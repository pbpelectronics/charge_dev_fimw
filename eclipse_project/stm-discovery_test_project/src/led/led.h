/*
 * led.h
 *
 *  Created on: 30 ���. 2013
 *      Author: ������
 */

#ifndef LED_H_
#define LED_H_

void switchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower);
void clearLed(TIM_TypeDef * led);
void reswitchLed(TIM_TypeDef * led, int greenPower, int bluePower, int redPower, int timeout);

#endif /* LED_H_ */
