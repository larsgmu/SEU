/*
 * utility.c
 *
 *  Created on: Apr 30, 2021
 *      Author: pperez
 */

#include "main.h"
//#include "cmsis_os.h"
#include "utility.h"
extern UART_HandleTypeDef huart2;


unsigned portBASE_TYPE makeFreeRtosPriority (osPriority priority)
{
unsigned portBASE_TYPE fpriority = tskIDLE_PRIORITY;

if (priority != osPriorityError) {
fpriority += (priority - osPriorityIdle);
}

return fpriority;
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
	   // ITM_SendChar( *ptr++ );
	   HAL_UART_Transmit(&huart2, (uint8_t*)ptr++,1,1000);
	}

	return len;
}



