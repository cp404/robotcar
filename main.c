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

	///////////////////////////////////��ֵ����//////////////////////////////////////
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
 ///////////////////////////////////��ģ���ʼ��///////////////////////////////////
	delay_init(168);
  uart_init(115200);
	LED_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	PS2_Init();
	Motor_Init();
	TIM2_Int_Init(999,8399);      //100ms �����ö�ʱ����ÿ100ms����һ�θ����жϷ��䳬����
	TIM4_Int_Init(1699,8399);     //200ms �����ö�ʱ����ÿ200ms����һ�θ����жϼ�⿪����ť�Ƿ���
	TIM3_Int_Init(49,8399);       //5ms   ����ö�ʱ����ÿ5ms����һ�θ����жϼ��ps2������ť״̬
  TIM5_Int_Init(4999,8399);     //500ms ����ö�ʱ����ÿ500ms����һ�θ����жϼ��ps2ң����ֵ
	TIM3_PWM_Init(1999,839);      //20ms  ���pwm����
	TIM5_PWM_Init(6000,83);       //6ms
	Tracking_GPIO_Init();
  Uln_init();            //��������ʼ��
  EXTI_ClearITPendingBit(EXTI_Line1); 

  while(1)
	{
	 if(powerflag==1)
	 {    
//		printf("%d",Distance1);
//		printf ("            ");	
///////////////////�������//////////////////////////
		 
	  TIM_SetCompare1(TIM3,x);//(��ʼֵ1950)
	  TIM_SetCompare2(TIM3,y);//(��ʼֵ1950)
	  TIM_SetCompare3(TIM3,z);//(��ʼֵ1950)
	  TIM_SetCompare4(TIM3,r);//(��ʼֵ1947)
		
//		printf("%d",x);//�����ô���ͨѶ����
//	  printf ("            ");
		 if(traflag==1)
		 {
			 Auto_Tracking();
		 }
		 
/////////////////////�Զ�ץȡ//////////////////////////		 
		if(Distance1<150)//��⵽����
		{	 
		Distance1=500;
		flag=0; //�رճ�����
		Set_Motor(-1000, 0,0,-1000);   //���ӷ�ת47msɲ��
			delay_ms(47);
		Set_Motor(0,0,0,0);	           //��ͣ��
		
			//Ԥ��ץȡ̬
	  TIM_SetCompare1(TIM3,1860);//pwm���ź���ԴPA7
		TIM_SetCompare2(TIM3,1840);//PA6
		  delay_ms(100);//��ʱ�ȴ��ö�������
			
		TIM_SetCompare3(TIM3,1850);//PB0         //���ڻ�е��̫�أ�һ������ȶ����ᵼ�»�е�۹���
			delay_ms(200);                         //���󣬹ʿ�����Ԥ��λ��ǰ��ͣ�½���һ��С����
		TIM_SetCompare3(TIM3,1860);//PB0
		  delay_ms(1000);
			
		//ץ
		TIM_SetCompare1(TIM3,1770);//PA7
		  delay_ms(900);
			
		//�ָ�
		TIM_SetCompare2(TIM3,1840);//PA6
		TIM_SetCompare3(TIM3,1820);//PB0
		delay_ms(300);
//		TIM_SetCompare4(TIM3,1840);//PC9
		
		Set_Motor(3000, -3000,-3000, 3000);   //���¸�һ�����ٶ���������ѭ��
		}
	 }
  }
}
