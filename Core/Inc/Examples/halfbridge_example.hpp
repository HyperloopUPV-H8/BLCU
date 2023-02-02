/*
 * halfbridge_example.hpp
 *
 *  Created on: 2 Feb. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"

void halfbridge_example(){

	HalfBridge half_simple1 = HalfBridge(PB14, PB15, PC13);
	HalfBridge half_simple2 = HalfBridge(PB4, PB5, PG1);
	HalfBridge half_simple3 = HalfBridge(PC8, PD12, PE7);
	HalfBridge half_simple4 = HalfBridge(PD13, PD15, PF4);
	HalfBridge half_simple5 = HalfBridge(PE14, PE6, PB2);
	HalfBridge half_simple6 = HalfBridge(PF1, PF2, PG0);


	HalfBridge half_double1 = HalfBridge(PB8, PB6, PB9, PB7, PF15);
	HalfBridge half_double2 = HalfBridge(PE11, PE10, PE13, PE12, PE2);
	HalfBridge half_double3 = HalfBridge(PE5, PE4, PE9, PE8, PE3);

	STLIB::start(Nucleo, "192.168.1.4", "255.255.0.0", "192.168.1.1", UART::uart2);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");

	half_simple1.turn_on();
	half_simple2.turn_on();
	half_simple3.turn_on();
	half_simple4.turn_on();
	half_simple5.turn_on();
	half_simple6.turn_on();

	half_double1.turn_on();
	half_double2.turn_on();
	half_double3.turn_on();
	int8_t duty = 0;
	bool direction = true;
	while (1) {

		half_simple1.set_duty_cycle(duty);
		half_simple2.set_duty_cycle(duty);
		half_simple3.set_duty_cycle(duty);
		half_simple4.set_duty_cycle(duty);
		half_simple5.set_duty_cycle(duty);
		half_simple6.set_duty_cycle(duty);

		half_double1.set_duty_cycle(duty);
		half_double2.set_duty_cycle(duty);
		half_double3.set_duty_cycle(duty);

		if (abs(duty) > 90) {
			direction = !direction;
		}

		if (direction) {
			duty += 10;
		}else{
			duty -= 10;
		}
		printf("Duty = %d | \r", duty);
		HAL_Delay(200);

		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}
