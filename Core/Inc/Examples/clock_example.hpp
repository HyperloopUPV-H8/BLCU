/*
 * sensors_example.hpp
 *
 *  Created on: 1 Feb. 2022
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

void clock_example(){

	Stopwatch Sw = Stopwatch();
	Counter c10 = Counter(10);
	Counter c100 = Counter(100);
	Counter c1000 = Counter(1000);
	Counter c5000 = Counter(5000);
	Sw.start("one");

	UART::set_up_printf(UART::uart2);

	Pin::start();
	UART::start();
	Time::start();

	printf("\n\n\n\n\n\n\n\n\n\n");

	while(1){
		c10.count();c100.count();c1000.count();c5000.count();
		printf("Frequency of HAL_Delay(100) on counters by precision 10ms = %f, 100ms = %f, 1000ms = %f, 5000ms = %f \n",c10.freq,c100.freq,c1000.freq,c5000.freq);
		printf("Time since last HAL_Delay = %d ms \n", (int) Sw.stop("one").value() / 1000000);
		Sw.start("one");
		HAL_Delay(100);
	}
}

