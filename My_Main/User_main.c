#include "User_main.h"
extern int16_t Coordinate1_One;
extern uint8_t _GetDistantRxVal ;
extern float _GetDistantResults; 
void Usermain(void)
{
//	HAL_TIM_Base_Start(&htim4);
//	HAL_TIM_Base_Start(&htim1);
//	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	User_GetErrorUart_Init();
	User_DebugUart_Init();
	User_DistantUart_Init();
	//printf("123456\n");
	
	while(1)
	{
		//OpenFire();
//		ShowError();
//		ShowDistant();
//		HAL_Delay(1500);
//		Lcd_Clear(WHITE);
//		HAL_Delay(50);
		//OpenFire();
		//printf("%f\n",_GetDistantResults);
		//__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,500);
		//printf("123456\n");
		stop=0;
		Locate_RunStep(1,1500,500);
		HAL_Delay(3000);
	//__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,10);
		stop = 0;
		HAL_Delay(3000);
		HAL_TIM_Base_Init(&htim2);
		HAL_TIM_Base_Start(&htim2);
		HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
		Locate_RunStep(0,1500,500);
		HAL_Delay(3000);
		
	//	LCDShowRefresh();

		//GaussGun_Fire(5000);
			//OpenFire();
		//HAL_Delay(2000);
//		}
		//LCDShowRefresh();
//		HAL_Delay(100);
//		Lcd_Clear(WHITE);

	}
}