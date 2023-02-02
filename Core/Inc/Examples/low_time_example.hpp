/*
 * sensors_example.hpp
 *
 *  Created on: 1 Feb. 2022
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

void low_time_example(){
	UART::set_up_printf(UART::uart2);

	Pin::start();
	Time::start();
	ADC::start();
	UART::start();
	uint8_t alarm = 255;
	int second = 0;
	Time::set_timeout(3000,[&](){printf("3 seconds have passed, timeout A trigger\n");});
	Time::set_timeout(7000,[&](){printf("7 seconds have passed, timeout B trigger and alarm destroyed\n");Time::unregister_low_precision_alarm(alarm);});
	alarm = Time::register_low_precision_alarm(1000,[&](){second++;printf("%d seconds have passed, alarm trigger\n",second);});


	printf("\n\n\n\n\n\n\n\n\n\n");

	while(1){
		HAL_Delay(100);
	}
}
