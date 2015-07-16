#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "../common/common.h"

//for timer
void TIM7_IRQHandler(void) {
	time_ms++;
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}

void initTimerCounter() {
	int prescaler = 800;
	TIM_TimeBaseInitTypeDef timer7;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_TimeBaseStructInit(&timer7);
	timer7.TIM_Prescaler = prescaler;
	timer7.TIM_Period = SystemCoreClock/(prescaler*1000);
	TIM_TimeBaseInit(TIM7, &timer7);

	NVIC_InitTypeDef NVIC_InitStructure; //create NVIC structure
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ(TIM7_IRQn);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM7, ENABLE);
}

void initPWM2() {
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	GPIO_InitTypeDef GPIO_Config;
	GPIO_Config.GPIO_Pin = GPIO_Pin_10;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Config);
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
	GPIO_Config.GPIO_Pin = GPIO_Pin_2;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Config);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_BaseConfig;
	TIM_OCInitTypeDef TIM_OCConfig;

	TIM_BaseConfig.TIM_Prescaler = SystemCoreClock / BATT_SIG_FREQUENCY
			/ MAX_BATT_POWER;
	TIM_BaseConfig.TIM_Period = MAX_BATT_POWER;
	TIM_BaseConfig.TIM_ClockDivision = 0;
	TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &TIM_BaseConfig);

	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	//	TIM_OC1Init(TIM4, &TIM_OCConfig);
	//	TIM_OC2Init(TIM4, &TIM_OCConfig);
	TIM_OC3Init(TIM2, &TIM_OCConfig);
	//	TIM_OC4Init(TIM4, &TIM_OCConfig);

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM2, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

//timer for battery output
void initPWM3() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitTypeDef GPIO_Config;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Config.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_Config);

	TIM_TimeBaseInitTypeDef TIM_BaseConfig;
	TIM_OCInitTypeDef TIM_OCConfig;

	TIM_BaseConfig.TIM_Prescaler = SystemCoreClock / BATT_SIG_FREQUENCY
			/ MAX_BATT_POWER;
	TIM_BaseConfig.TIM_Period = MAX_BATT_POWER;
	TIM_BaseConfig.TIM_ClockDivision = 0;
	TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &TIM_BaseConfig);

	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCConfig);
	TIM_OC2Init(TIM3, &TIM_OCConfig);
	TIM_OC3Init(TIM3, &TIM_OCConfig);
	TIM_OC4Init(TIM3, &TIM_OCConfig);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
}

void initPWM4() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitTypeDef GPIO_Config;
	GPIO_Config.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Config);

	TIM_TimeBaseInitTypeDef TIM_BaseConfig;
	TIM_OCInitTypeDef TIM_OCConfig;

	TIM_BaseConfig.TIM_Prescaler = SystemCoreClock / BATT_SIG_FREQUENCY
			/ MAX_BATT_POWER;
	TIM_BaseConfig.TIM_Period = MAX_BATT_POWER;
	TIM_BaseConfig.TIM_ClockDivision = 0;
	TIM_BaseConfig.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_BaseConfig);

	TIM_OCConfig.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCConfig.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCConfig.TIM_Pulse = 0;
	TIM_OCConfig.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM4, &TIM_OCConfig);
//	TIM_OC2Init(TIM4, &TIM_OCConfig);
//	TIM_OC3Init(TIM4, &TIM_OCConfig);
	TIM_OC4Init(TIM4, &TIM_OCConfig);

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
}
