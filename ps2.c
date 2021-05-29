#include "ps2.h"
#include "delay.h"
#include "usart.h"
#include "stm32f4xx.h"
#include "motor.h"
/*********************************************************
File：PS2驱动程序
Description: PS2驱动程序
**********************************************************/	 
extern int Motor_Speed[4];			//电机速度值
extern int Motor_DrctAdj[4];		//电机转向调整

u16 Handkey;
u8 Comd[2]={0x01,0x42};	//开始命令。请求数据
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组，其中1号位为手柄操作模式，3~4号为16个按键状态存储位，5~8号为手柄摇杆状态存储位
u16 MASK[]=
  {
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键说明



void PS2_Init(void)
{
    //输入  DI->PB9   		
	GPIO_InitTypeDef GPIO_InitStructure; 
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;//PB9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; //下拉输入模式
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
 	GPIO_Init(GPIOB,&GPIO_InitStructure);

	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_13 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 	
		
  
}


//向手柄发送命令
void PS2_Cmd(u8 CMD)
{
	volatile u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)	DO_H; //输出以为控制位
		else DO_L;
		CLK_H;                        //时钟拉高
		delay_us(10);
		CLK_L;
		delay_us(10);
		CLK_H;
		if(DI)	Data[1] = ref|Data[1];
	}
}
//判断是否为红灯模式
//返回值；0，红灯模式
//		  其他，其他模式
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	volatile u8 byte=0;
	volatile u16 ref=0x01;

	CS_L;

	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据

	for(byte=2;byte<9;byte++)          //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			delay_us(10);
			CLK_L;
			delay_us(10);
			CLK_H;
		  if(DI)	Data[byte] = ref|Data[byte];
		}
    delay_us(10);
	}
	CS_H;	
}

//对读出来的PS2的数据进行处理      只处理了按键部分         默认数据是红灯模式  只有一个按键按下时
//按下为0， 未按下为1
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)//取出mask中的键值减一使1（即0000000000000001）左移多少位，然后将左移后的1和handkey进行按位与操作由于1中只有一个位为1只有1到达相应的0时整个按位与运算才能每一位都为0
		return index+1;//数组编号从0开始，宏定义数值从1开始，故数组元素编号＋1即为键值
	}
	return 0;          //没有任何按键按下
}

//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];//遥感值已在头文件中宏定义
}

//清除数据缓冲区
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}




