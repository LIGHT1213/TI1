#include "User_main.h"
extern int16_t Coordinate1_One;
void Usermain(void)
{
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	User_GetErrorUart_Init();
	printf("123456\n");
	while(1)
	{
		//__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,500);
		//printf("123456\n");
		if(Key_scan()!=0)
		{
		Gui_DrawFont_Num32(50,50,5,5,Key_scan());
		
		}
		HAL_Delay(100);
		Lcd_Clear(WHITE);

	}
}