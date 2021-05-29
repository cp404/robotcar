#include "motor.h"

int Motor_Speed[4];			//电机速度值
int Motor_DrctAdj[4];		//电机转向调

void Motor_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;//设置结构体
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);//时钟函数使能
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);

   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_Init(GPIOG,&GPIO_InitStruct);//IOG初始化
 
   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	 GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	 GPIO_Init(GPIOF,&GPIO_InitStruct);//IOF初始化
	
	 GPIO_ResetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	 GPIO_ResetBits(GPIOG,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);

	 Motor_DrctAdj[0]=1;Motor_DrctAdj[1]=1;Motor_DrctAdj[2]=1;Motor_DrctAdj[3]=1;//参数，实际为车的尺寸长乘宽
};

void Car_Control(int Y_Move,int X_Move,int Yaw)//通过ps2遥感值解算出四个轮的速度
{
	Motor_Speed[0] =  (-Y_Move + X_Move + Yaw)*Motor_DrctAdj[0];	Motor_Speed[2] = (Y_Move - X_Move + Yaw)*Motor_DrctAdj[2];
	Motor_Speed[1] = 	(-Y_Move - X_Move - Yaw)*Motor_DrctAdj[1];	Motor_Speed[3] = (Y_Move + X_Move - Yaw)*Motor_DrctAdj[3];	
};

void Set_Motor(int MotorA,int MotorB,int MotorC,int MotorD)
{
	
	if(MotorA>0)
	{
		MotorA1=0,			MotorA2=1;
		TIM5->CCR1=MotorA;
	}
	else
	{
		MotorA1=1,			MotorA2=0;
		TIM5->CCR1=-MotorA;
	}
	
/////////////////////////////	
	if(MotorB>0)
	{
		MotorB1=0,			MotorB2=1;
		TIM5->CCR2=MotorB;
	}
	else
	{
		MotorB1=1,			MotorB2=0;
		TIM5->CCR2=-MotorB;
	}
	///////////////////////////
		if(MotorC>0)
	{
		MotorC1=0,			MotorC2=1;
		TIM5->CCR3=MotorC;
	}
	else
	{
		MotorC1=1,			MotorC2=0;
		TIM5->CCR3=-MotorC;
	}
/////////////////////////////	
	if(MotorD>0)
	{
		MotorD1=0,			MotorD2=1;
		TIM5->CCR4=MotorD;
	}
	else
	{
		MotorD1=1,			MotorD2=0;
		TIM5->CCR4=-MotorD;
	}
}

