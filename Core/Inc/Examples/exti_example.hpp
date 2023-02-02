/*
 * sensors_example.hpp
 *
 *  Created on: 1 Feb. 2022
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

void exti_example(){
	int var = 0;
	PinState ps = OFF;
	SensorInterrupt exti = SensorInterrupt(PE0, [&](){var++;printf("Interrupt detected %d\n", var);}, ps);

	UART::set_up_printf(UART::uart2);

	Pin::start();
	UART::start();
	ExternalInterrupt::start();
	Sensor::start();

	printf("\n\n\n\n\n\n\n\n\n\n");

	while(1){
		exti.read();
		HAL_Delay(100);
	}
}
