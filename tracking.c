#include "tracking.h"
#include "motor.h"
#include "delay.h"

void Tracking_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //���ó���������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
}


void Auto_Tracking(void)
{
	if((D2==0 && D3 ==1 && D4==0))  //ֱ��
		{
				Set_Motor(1000, -1000,-1000, 1000);
		}
		else if(D1==1&&D2==1&&D3==1&&D4==1&&D5==1)//������Ϊ����
		{
		    Set_Motor(800, -800,-800, 800);
		}
		else if ((D5==1)||(D1==1&&D5==1)) //�Ҵ�ת�������������ǰ�����ߣ������ܴﵽƯ�Ƶ�Ч��
		{   
			Set_Motor(5650, -5650,5250, -5250);//�ٶȾ���ֵ��ǰ�������࣬ʵ��Ϊǰ��ת	
//		if((D1==1&&D5==1)||D5==1||(D2==1 && D3 ==1 && D4==1))  //���ش�ת���Է�ֹһ��ת��֮������ȫת���䣬�������Ϊʵ��
//		{
//			Set_Motor(6000, -6000,6000, -6000);//�ٶȾ���ֵ��ͬ��ԭ����ת	
//		}
		}
		else if ((D1==1)||(D1==1&&D5==1)) //���ת��ͬ���Ҵ�ת
		{   
				Set_Motor(-5250, 5250,-5650, 5650);
//			if((D3==1&&D4==1)||(D5==1)||(D2==1 && D3 ==1 && D4==1)||(D2==1 && D3 ==1)||(D2 == 1)||(D3 == 1))//���ش�ת���Է�ֹһ��ת��֮������ȫת���䣬�������Ϊʵ��
//			{
//				Set_Motor(-6000, 6000,-6000, 6000);
//			}
		}


	  else if (D2==1 && D3 ==0 && D4==0 ) //��ת
		{
				Set_Motor(-2000, 2000,-2000, 2000);
		}
	  else if (D2==1 && D3 ==1 && D4==0 ) //��Сת��������ѹ�ߣ�ƫ���С��
		{
				Set_Motor(-1500, 1500,-1500, 1500);
		}
		else if ( D2==0 && D3 ==0 && D4==1) //��ת
		{
				Set_Motor(2000, -2000,2000, -2000);	
		}
		else if ( D2==0 && D3 ==1 && D4==1) //��Сת��������ѹ�ߣ�ƫ���С��
		{
				Set_Motor(1500, -1500,1500, -1500);	
		}

		else	Set_Motor(1000, -1000,-1000, 1000);  //�������Ĭ��ֱ��
}
