/*
 * sensors_example.hpp
 *
 *  Created on: 31 Jan. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"

void sensors_example(){

	UART::set_up_printf(UART::uart2);

	double slope = 1.0,  offset = 0, value = 0.0;
	LinearSensor linear = LinearSensor(PF11, slope, offset, &value);

	PinState pin = PinState::OFF;
	DigitalSensor digital = DigitalSensor(PF0, &pin);

	Pin::start();
	Time::start();
	ADC::start();
	UART::start();
	Sensor::start();

	printf("\n\n\n\n\n\n\n\n\n\n");

	while (1) {
		digital.read();
		linear.read();

		printf("Value %f | Pin %d \r", value, pin);
		HAL_Delay(50);

		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}
