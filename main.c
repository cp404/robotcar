#include "stm32f4xx.h"
#include "delay.h"
#include "LED.h"
#include "sys.h"
#include "usart.h"
#include "ps2.h"
#include "timer.h"
#include "pwm.h"
#include "ultrasonic.h"
#include "exti.h"
#include "motor.h"
#include "tracking.h"

	///////////////////////////////////数值声明//////////////////////////////////////
	extern unsigned int x;
	extern unsigned int y;
	extern unsigned int z;
	extern unsigned int r;
	extern unsigned int Distance1;
	extern unsigned int flag;
	extern int powerflag;
	extern int traflag;

int main()
{
 ///////////////////////////////////各模块初始化///////////////////////////////////
	delay_init(168);
  uart_init(115200);
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	PS2_Init();
	Motor_Init();
	TIM2_Int_Init(999,8399);      //100ms 启动用定时器，每100ms发生一次更新中断发射超声波
	TIM4_Int_Init(1699,8399);     //200ms 启动用定时器，每200ms发生一次更新中断检测开机按钮是否按下
	TIM3_Int_Init(49,8399);       //5ms   舵机用定时器，每5ms发生一次更新中断检测ps2按键按钮状态
  TIM5_Int_Init(4999,8399);     //500ms 电机用定时器，每500ms发生一次更新中断检测ps2遥感数值
	TIM3_PWM_Init(1999,839);      //20ms  舵机pwm周期
	TIM5_PWM_Init(6000,83);       //6ms
	Tracking_GPIO_Init();
  Uln_init();            //超声波初始化
  EXTI_ClearITPendingBit(EXTI_Line1); 

  while(1)
	{
	 if(powerflag==1)
	 {    
//		printf("%d",Distance1);
//		printf ("            ");	
///////////////////舵机控制//////////////////////////
		 
	  TIM_SetCompare1(TIM3,x);//(初始值1950)
	  TIM_SetCompare2(TIM3,y);//(初始值1950)
	  TIM_SetCompare3(TIM3,z);//(初始值1950)
	  TIM_SetCompare4(TIM3,r);//(初始值1947)
		
//		printf("%d",x);//调试用串口通讯程序
//	  printf ("            ");
		 if(traflag==1)
		 {
			 Auto_Tracking();
		 }
		 
/////////////////////自动抓取//////////////////////////		 
		if(Distance1<150)//检测到方块
		{	 
		Distance1=500;
		flag=0; //关闭超声波
		Set_Motor(-1000, 0,0,-1000);   //轮子反转47ms刹车
			delay_ms(47);
		Set_Motor(0,0,0,0);	           //车停下
		
			//预备抓取态
	  TIM_SetCompare1(TIM3,1860);//pwm波信号来源PA7
		TIM_SetCompare2(TIM3,1840);//PA6
		  delay_ms(100);//延时等待该动作做完
			
		TIM_SetCompare3(TIM3,1850);//PB0         //由于机械臂太重，一个大幅度动作会导致机械臂惯性
			delay_ms(200);                         //过大，故考虑在预设位置前先停下进行一个小缓冲
		TIM_SetCompare3(TIM3,1860);//PB0
		  delay_ms(1000);
			
		//抓
		TIM_SetCompare1(TIM3,1770);//PA7
		  delay_ms(900);
			
		//恢复
		TIM_SetCompare2(TIM3,1840);//PA6
		TIM_SetCompare3(TIM3,1820);//PB0
		delay_ms(300);
//		TIM_SetCompare4(TIM3,1840);//PC9
		
		Set_Motor(3000, -3000,-3000, 3000);   //重新给一个大速度启动继续循迹
		}
	 }
  }
}
