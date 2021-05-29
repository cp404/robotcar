#include "exti.h"
#include "delay.h"

	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PA0/PE2/PE3/PE4Ϊ�ж�����.
void EXTIX_Init(void)
{
	GPIO_InitTypeDef led;
  EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʱ������
  led.GPIO_Mode=GPIO_Mode_IN;//
	led.GPIO_OType=GPIO_OType_PP;//�������
	led.GPIO_Pin=GPIO_Pin_1;//
	led.GPIO_PuPd=GPIO_PuPd_DOWN;//����
	led.GPIO_Speed=GPIO_Speed_100MHz;//����Ƶ��
	GPIO_Init(GPIOB,&led);
	//io�ڳ�ʼ����echo��pB1��
		
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB,EXTI_PinSource1);

//	Ex_NVIC_Config(GPIOB,0,FTIR); 			//�½��ش���
//	Ex_NVIC_Config(GPIO_B,1,FTIR); 			//�½��ش���
	EXTI_InitStruct.EXTI_Line=EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
  NVIC_Init(&NVIC_InitStruct);	
 
}

