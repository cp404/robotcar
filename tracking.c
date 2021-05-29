#include "tracking.h"
#include "motor.h"
#include "delay.h"

void Tracking_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //设置成上拉输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
}


void Auto_Tracking(void)
{
	if((D2==0 && D3 ==1 && D4==0))  //直行
		{
				Set_Motor(1000, -1000,-1000, 1000);
		}
		else if(D1==1&&D2==1&&D3==1&&D4==1&&D5==1)//启动区为亮面
		{
		    Set_Motor(800, -800,-800, 800);
		}
		else if ((D5==1)||(D1==1&&D5==1)) //右大转，当你的重心在前方够高，甚至能达到漂移的效果
		{   
			Set_Motor(5650, -5650,5250, -5250);//速度绝对值向前分量更多，实际为前右转	
//		if((D1==1&&D5==1)||D5==1||(D2==1 && D3 ==1 && D4==1))  //二重大转，以防止一重转完之后不能完全转过弯，红外情况为实测
//		{
//			Set_Motor(6000, -6000,6000, -6000);//速度绝对值相同，原地右转	
//		}
		}
		else if ((D1==1)||(D1==1&&D5==1)) //左大转，同理右大转
		{   
				Set_Motor(-5250, 5250,-5650, 5650);
//			if((D3==1&&D4==1)||(D5==1)||(D2==1 && D3 ==1 && D4==1)||(D2==1 && D3 ==1)||(D2 == 1)||(D3 == 1))//二重大转，以防止一重转完之后不能完全转过弯，红外情况为实测
//			{
//				Set_Motor(-6000, 6000,-6000, 6000);
//			}
		}


	  else if (D2==1 && D3 ==0 && D4==0 ) //左转
		{
				Set_Motor(-2000, 2000,-2000, 2000);
		}
	  else if (D2==1 && D3 ==1 && D4==0 ) //左小转（两条管压线，偏差很小）
		{
				Set_Motor(-1500, 1500,-1500, 1500);
		}
		else if ( D2==0 && D3 ==0 && D4==1) //右转
		{
				Set_Motor(2000, -2000,2000, -2000);	
		}
		else if ( D2==0 && D3 ==1 && D4==1) //右小转（两条管压线，偏差很小）
		{
				Set_Motor(1500, -1500,1500, -1500);	
		}

		else	Set_Motor(1000, -1000,-1000, 1000);  //其它情况默认直行
}
