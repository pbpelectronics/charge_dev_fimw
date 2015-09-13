/*
 * encoder.c
 *
 *  Created on: 3 Ð¶Ð¾Ð²Ñ‚. 2013
 *      Author: ÑœÐ»ÐµÐºÑ�â‰¥Ð¹
 */
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "encoder.h"
#include "misc.h"
#include "stdbool.h"
#include "../common/common.h"

//for encoder
void TIM1_UP_TIM16_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update ) != RESET) {
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update );

		if (!capture_is_first)
			encoderIsActive = 1;

		capture_is_first = 0;
		captured_direction = (TIM1 ->CR1 & TIM_CR1_DIR ? FORWARD : BACKWARD);
	}
}

void initEncoder(void) {
	capture_is_first = 1;
	encoderIsActive = 0;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpio_cfg;
	GPIO_StructInit(&gpio_cfg);
	gpio_cfg.GPIO_Mode = GPIO_Mode_IPU;
	gpio_cfg.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpio_cfg);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef timer_base;
	TIM_TimeBaseStructInit(&timer_base);
	timer_base.TIM_Period = 4;
	timer_base.TIM_CounterMode = TIM_CounterMode_Down | TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &timer_base);

	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling );

	NVIC_InitTypeDef NVIC_InitStructure; //create NVIC structure
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM16_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
}

Direction getEncoderDirection() {
	NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
	encoderIsActive = 0;
	Direction direction = captured_direction;
	NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	return direction;
}

bool isMenuEncoderPressed(){
	return !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);
}
