/*
 * drv_uart1.c
 *
 *  Created on: 7 nov. 2022
 *      Author: laurentf
 */

#include "drv_uart1.h"


extern SemaphoreHandle_t semaphori;

uint8_t drv_uart1_receive(char * pData, uint16_t size)
{
	HAL_UART_Receive_IT(&huart1, (uint8_t*)(pData), size);

	printf("Je vais Take\r\n");
	if(xSemaphoreTake(semaphori,MAX_S_Time)==pdTRUE)
	{
		printf("Good Take semaphori\r\n");
	}
	else
	{
		printf("Error Take semaphori\r\n");
	}

	return 0;	// Life's too short for error management
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	BaseType_t HPTW = pdFALSE;
	printf("Je vais Give\r\n");
	if(xSemaphoreGiveFromISR(semaphori,HPTW)==pdTRUE)
	{
		printf("J ai Give\r\n");
	}
	else
	{
		printf("Error j ai pas Give\r\n");
	}

}


uint8_t drv_uart1_transmit(const char * pData, uint16_t size)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)pData, size, HAL_MAX_DELAY);

	return 0;	// Srsly, don't do that kids
}

