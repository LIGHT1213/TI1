#include "My_Uart.h"
void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart) 
{
	if(huart->Instance == UART4)
	{
		HAL_UART_Receive_DMA(&huart4,command,6);
	}

}