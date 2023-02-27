/*
 * printf_freq.hpp
 *
 *  Created on: 24 feb. 2022
 *      Author: Pablo
 */

void print_freq(){
	uint32_t counter = HAL_RCC_GetSysClockFreq();
	printf("Clock = %lu MHz\n", counter / 1000000);
}
