#include "sys.h"		
#include "delay.h"	
#include "exti.h"
#include "timer.h"	
#include "ultrasonic.h"
#include "stm32f4xx.h"

unsigned int Distance1=500;

unsigned char TimeOut_Flag1=0;

unsigned int flag=1;

void Uln_init(void)
{
//RCC->APB2ENR|=1<<4;    //使能PORTC时钟	   	 
//GPIOC->CRL&=0XFFFFFF0F; 
//GPIOC->CRL|=0X00000030;//PC1 输出 
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);//IOC初始化
	
  Trig=0;	
  TIM7_Int_Init(4999,839);//计数一个数值，时间为1us
  EXTIX_Init();

}


void Uln_Trig(void)
{
if(flag)
{	
Trig=1;
delay_us(100);
Trig=0;
if(TimeOut_Flag1)Distance1=500;
TimeOut_Flag1=1;
TIM7->CNT=0;  			//设定计数器自动重装值 
TIM_Cmd(TIM7,ENABLE); 	//使能定时器7
}
}
void EXTI1_IRQHandler(void)
{

Distance1=TIM7->CNT;//声速为340m/s,一个计数时间为10us,那么声音传播的距离为0.0034m,即0.34cm
Distance1=(Distance1-72.572)/0.17142857+6; //单位0.1cm
//	Distance1=Distance1-80;
TimeOut_Flag1=0;
//printf("%d\n",Distance1);
//printf("              ");

//抓取态
//	  TIM_SetCompare1(TIM3,1950);//PA7
//		TIM_SetCompare2(TIM3,1949);//PA6
//		TIM_SetCompare3(TIM3,1958);//PB0
//		TIM_SetCompare4(TIM3,1953);//PC9
//		delay_ms(10);
//		//抓
//		TIM_SetCompare1(TIM3,1925);//PA7
//		delay_ms(10);
//		//恢复
//		TIM_SetCompare2(TIM3,1949);//PA6
//		TIM_SetCompare3(TIM3,1950);//PB0
//		TIM_SetCompare4(TIM3,1953);//PC9
	
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE1上的中断标志位  

	}
//	printf("%d\n",TIM7->CNT);
