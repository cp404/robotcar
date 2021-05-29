#include "pwm.h"

//////////////////舵机用pwm////////////////////////////////////////////////////////////
void TIM3_PWM_Init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStruct;//设置结构体

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//时钟函数使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//IOA初始化
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//IOB初始化
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);//IOC初始化

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);//IO口复用为TIM3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 1820;
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}

///////////////电机pwm//////////////////////////////////////////////////////////////////
void TIM5_PWM_Init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStruct;//设置结构体

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//时钟函数使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//IOA端口初始化

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);//IO口复用为TIM5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStruct);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM5,&TIM_OCInitStructure);
	TIM_OC2Init(TIM5,&TIM_OCInitStructure);
	TIM_OC3Init(TIM5,&TIM_OCInitStructure);
	TIM_OC4Init(TIM5,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM5,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM5,ENABLE);
	
	TIM_Cmd(TIM5,ENABLE);
}

