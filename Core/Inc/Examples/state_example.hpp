/*
 * sensors_example.hpp
 *
 *  Created on: 1 Feb. 2022
 *      Author: Ricardo
 */
#pragma once

#include "ST-LIB.hpp"

void state_example(){
	UART::set_up_printf(UART::uart2);

	PinState a = OFF;
	PinState b = OFF;
	PinState e = OFF;


	StateMachine Sm = StateMachine(0); //starting
	Sm.add_state(1); //operational
	Sm.add_state(2); //fault
	Sm.add_transition(1,2,[&](){return b == ON;});
	Sm.add_transition(2,1,[&](){return a == ON && b == OFF && e == OFF;});
	Sm.add_enter_action([&](){printf(" faulty pin active, entering fault state \n");},2);
	Sm.add_enter_action([&](){printf(" able to reset to operational \n");},1);

	DigitalSensor reset_pin = DigitalSensor(PA3,a);
	DigitalSensor soft_faulty_pin = DigitalSensor(PB0,b);
	SensorInterrupt hard_faulty_pin = SensorInterrupt(PE0,[&](){Sm.force_change_state(2);printf("hard fault \n");},e);


	Pin::start();
	Time::start();
	UART::start();
	ExternalInterrupt::start();
	Sensor::start();

	Sm.add_transition(0,1,[&](){return b == OFF && e == OFF;});
	printf("\n\n\n\n\n\n\n\n\n\n");

	while(1){
		printf("checking state\n");
		reset_pin.read();
		soft_faulty_pin.read();
		hard_faulty_pin.read();
		Sm.check_transitions();
		if(Sm.current_state == 1){
			printf("operational \n");
		}else if(Sm.current_state == 2){
			printf("fault \n");
		}else{
			printf("starting \n");
		}
		HAL_Delay(500);
	}
}
