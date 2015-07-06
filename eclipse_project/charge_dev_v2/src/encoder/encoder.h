/*
 * encoder.h
 *
 *  Created on: 3 ����. 2013
 *      Author: ������
 */

#ifndef ENCODER_H_
#define ENCODER_H_

typedef enum {
	FORWARD, BACKWARD
} Direction;

void initEncoder(void);
Direction getEncoderDirection();
volatile uint8_t capture_is_first, encoderIsActive;
volatile Direction captured_direction;

#endif /* ENCODER_H_ */
