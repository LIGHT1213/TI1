#include "My_PWM.h"
//********************************************************//
//	这个函数用于控制炮管使其能达到正确的教的是炮弹的远近合适
//********************************************************//
void ChannelOne_SetPositon(float Position)
{
	float temp = 1500;
	
	if(Position > 5000)
	{
		Position = 5000;
	}

	if(Position < -5000)
	{
		Position = -5000;
	}	
	
	temp += Position *(float)0.2;
	
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,(uint16_t)temp);
	
}
