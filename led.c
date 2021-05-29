#include "LED.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

void LED_Init(void)
{
	GPIO_InitTypeDef led;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//ʱ������

	led.GPIO_Mode=GPIO_Mode_OUT;//��ͨ���ģʽ
	led.GPIO_OType=GPIO_OType_PP;//�������
	led.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;//��Ӧled�Ƶ�9��10��io��
	led.GPIO_PuPd=GPIO_PuPd_UP;//����
	led.GPIO_Speed=GPIO_Speed_100MHz;//����Ƶ��
	
  GPIO_Init(GPIOF,&led);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_10|GPIO_Pin_9);//���øߵ�λ����
 
}
