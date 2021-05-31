/*
 * utility.h
 *
 *  Created on: Apr 30, 2021
 *      Author: pperez
 */

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


unsigned portBASE_TYPE makeFreeRtosPriority (osPriority priority);
int _write(int file, char *ptr, int len);


#endif /* INC_UTILITY_H_ */
