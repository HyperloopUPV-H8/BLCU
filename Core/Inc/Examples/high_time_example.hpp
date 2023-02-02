/*
 * sensors_example.hpp
 *
 *  Created on: 1 Feb. 2022
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

extern TIM_HandleTypeDef htim5;

void high_time_example(){
	UART::set_up_printf(UART::uart2);
	printf("inicio\n");

	DigitalOutput led(PB0);

	Pin::start();
	Time::start();
	ADC::start();
	UART::start();

	int milis = 100;
	int a = 0;
	int b = 0;
	int c = 0;


	printf("\n\n\n\n\n\n\n\n\n\n");

	Time::register_low_precision_alarm(milis,[&](){c++;});
	Time::register_high_precision_alarm(milis*1000,[&](){a++;});
	Time::register_low_precision_alarm(1000,[&](){printf("number of high triggers = %d, low triggers = %d, HAL triggers = %d \n",a,c,b);});
	Time::register_high_precision_alarm(10000000,[&](){printf("Han pasado 10 segundos\n");});

	printf("listo\n");

	while(1){
		b++;
		HAL_Delay(milis);
	}
}
