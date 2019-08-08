#include "MricroStepDriver.h"
u8 rcr_remainder;   //重复计数余数部分
u8 is_rcr_finish=1; //重复计数器是否设置完成
long rcr_integer;	//重复计数整数部分
long target_pos=0;  //有符号方向
long current_pos=0; //有符号方向
DIR_Type motor_dir=CW;//顺时针
void Locate_Rle(long num,u32 frequency,DIR_Type dir) //相对定位函数
{
	if(num<=0) //数值小等于0 则直接返回
	{
		printf("\r\nThe num should be greater than zero!!\r\n");
		return;
	}
	if(TIM2->CR1&0x01)//上一次脉冲还未发送完成  直接返回
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//脉冲频率不在范围内 直接返回
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	motor_dir=dir;//得到方向	
	DRIVER_DIR=motor_dir;//设置方向
	
	if(motor_dir==CW)//顺时针
		target_pos=current_pos+num;//目标位置
	else if(motor_dir==CCW)//逆时针
		target_pos=current_pos-num;//目标位置
	
	rcr_integer=num/(RCR_VAL+1);//重复计数整数部分
	rcr_remainder=num%(RCR_VAL+1);//重复计数余数部分
	is_rcr_finish=0;//重复计数器未设置完成
	TIM8_Startup(frequency);// 开启TIM2
}
/********************************************
//绝对定位函数 
//num   -2147483648～2147483647
//frequency: 20Hz~100KHz
*********************************************/
void Locate_Abs(long num,u32 frequency)//绝对定位函数
{
	if(TIM2->CR1&0x01)//上一次脉冲还未发送完成 直接返回
	{
		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
		return;
	}
	if((frequency<20)||(frequency>100000))//脉冲频率不在范围内 直接返回
	{
		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
		return;
	}
	target_pos=num;//设置目标位置
	if(target_pos!=current_pos)//目标和当前位置不同
	{
		if(target_pos>current_pos)
			motor_dir=CW;//顺时针
		else
			motor_dir=CCW;//逆时针
		DRIVER_DIR=motor_dir;//设置方向
		
		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//重复计数整数部分
		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//重复计数余数部分
		is_rcr_finish=0;//重复计数器未设置完成
		TIM8_Startup(frequency);//开启TIM2
	}
}
void TIM8_Startup(u32 frequency)   //启动定时器8
{
	u16 temp_arr=1000000/frequency-1; 
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,temp_arr);
}
