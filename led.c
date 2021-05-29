#include "LED.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

void LED_Init(void)
{
	GPIO_InitTypeDef led;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//时钟设置

	led.GPIO_Mode=GPIO_Mode_OUT;//普通输出模式
	led.GPIO_OType=GPIO_OType_PP;//推挽输出
	led.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_10;//对应led灯的9和10号io口
	led.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	led.GPIO_Speed=GPIO_Speed_100MHz;//设置频率
	
  GPIO_Init(GPIOF,&led);
	
	GPIO_SetBits(GPIOF,GPIO_Pin_10|GPIO_Pin_9);//设置高电位灯灭
 
}
