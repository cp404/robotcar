#include "timer.h"
#include "led.h"
#include "ps2.h"
#include "stm32f4xx_tim.h"
#include "motor.h"
#include "ultrasonic.h"


unsigned int x=1870;
unsigned int y=1860;
unsigned int z=1820;
unsigned int r=1840;
short int PS2_CH[3];
extern int Motor_Speed[4];			//����ٶ�ֵ
extern int Motor_DrctAdj[4];
int powerflag = 0;
int traflag = 1;

//////////////////////////�������ж�/////////////////////////
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_DeInit(TIM2);											/* ����������ʱ�� */
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);						/* �������жϱ�־ */
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}
void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		Uln_Trig();//ÿ100ms����������һ��
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

//////////////////////////����ж�///////////////////////////
void TIM3_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_DeInit(TIM3);											/* ����������ʱ�� */
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);						/* �������жϱ�־ */
	
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM3,DISABLE);
	

}
void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
     u8	key;
		key=PS2_DataKey();
//    PS2_CH[0]=	0;						
//	  PS2_CH[1]=	0;
//	  PS2_CH[2]=	0;
//		printf("%d",Motor_Speed[0]);
//		printf("            ");
//		printf("%d",Motor_Speed[1]);
//		printf("            ");
//		printf("%d",Motor_Speed[2]);
//		printf("            ");

	   switch(key)
		 { //צ
			 case 14:if(x<1940)x++;break;//Բ��(1970)
		   case 16:if(x>1760)x--;break;//����
       //��
			 case 13:if(y<1890)y++;break;//����(1950)
			 case 15:if(y>1770)y--;break;//x		(1920)
			 //��
			 case 7:if(z<1940)z++;break;//��
			 case 5:if(z>1770)z--;break;//��
			 //��̨
			 case 8:if(r<1940)r++;break;//��
			 case 6:if(r>1760)r--;break;//��
			 default:break;
		 }
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
	
	
}
/////////////////////////////////����ж�///////////////////////////
void TIM5_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_DeInit(TIM5);											/* ����������ʱ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);						/* �������жϱ�־ */

	TIM_ITConfig(TIM5,TIM_IT_Update,DISABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5,DISABLE);
	
	PS2_CH[0]=	127;						
	PS2_CH[1]=	127;
	PS2_CH[2]=	127;
}
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET)
	{
   
		PS2_CH[0]=	PS2_AnologData(PSS_RY);						
		PS2_CH[1]=	PS2_AnologData(PSS_RX);
		PS2_CH[2]=	PS2_AnologData(PSS_LX);
		Car_Control((PS2_CH[1]-127)*3/5,(127-PS2_CH[0])*3/5,(PS2_CH[2]-127)/2);
	  Set_Motor(Motor_Speed[0]*25, Motor_Speed[1]*25,Motor_Speed[2]*25,Motor_Speed[3]*25);
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
 }
}

//////////////////////////���������ö�ʱ��///////////////////////////////////
void TIM4_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_DeInit(TIM4);											/* ����������ʱ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);						/* �������жϱ�־ */

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM4,ENABLE);
	
}
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		u8 key;
		key=PS2_DataKey();
		switch(key)
		 { 
			 case PSB_L1:  //�����������򣨳�ʼΪѭ��ģʽ��
			  powerflag=1;
			  GPIO_ResetBits(GPIOF,GPIO_Pin_10|GPIO_Pin_9);//ָʾ����
//			  TIM_SetCompare4(TIM3,1947);//(��ʼֵ1947)
//    	  TIM_SetCompare2(TIM3,1920);//(��ʼֵ1950)
//			  TIM_SetCompare3(TIM3,1935);//(��ʼֵ1950)
//			  TIM_SetCompare2(TIM3,1940);//(��ʼֵ1940)
//	      TIM_SetCompare1(TIM3,1950);//(��ʼֵ1950)צ��
			 
			  Set_Motor(5000, -5000,-5000, 5000);//��һ�����ٶ�����ֹ������
			  break;
		   case PSB_L2:  //�ر���������
				GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
				GPIO_ResetBits(GPIOG,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
			  GPIO_SetBits(GPIOF,GPIO_Pin_10|GPIO_Pin_9);//ָʾ����
			 	powerflag=0;
			  break;
			 case PSB_R1:  //�л�С��ģʽΪ�ֱ�ң��ģʽ
				Timer_ON();
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	      TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
			  traflag = 0;
			  break;
			 case PSB_R2:  //�ر�ң��ģʽ
				Timer_OFF();
				TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
	      TIM_ITConfig(TIM5,TIM_IT_Update,DISABLE);
			  traflag = 1;
			  break;
			 default:break;
		 
		 }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
 }
}

//////////////////////////�������ü�����/////////////////////////////////////
void TIM7_Int_Init(u16 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);
	TIM_ITConfig(TIM7,TIM_IT_Update,DISABLE);
	TIM_Cmd(TIM7,DISABLE);
}
/**************************************************************************************/
/************************������ʱ������************************************************/
void Timer_ON(void)
{	
	  TIM_Cmd(TIM3,ENABLE);
	  TIM_Cmd(TIM5,ENABLE);
}
/**************************************************************************************/
/************************�رն�ʱ������************************************************/
void Timer_OFF(void)
{	
	
	  TIM_Cmd(TIM3,DISABLE);
	  TIM_Cmd(TIM5,DISABLE);
//	 GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
//	 GPIO_ResetBits(GPIOG,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);

}
/**************************************************************************************/

