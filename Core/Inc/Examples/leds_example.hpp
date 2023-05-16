/**
 * leds_example.hpp
 *
 *  Created on: 7 Feb. 2023
 *      Author: Pablo
 */

#pragma once

#include "ST-LIB.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

void leds_example(){
    DigitalOutput LED_OPERATIONAL = DigitalOutput(PG8);
    DigitalOutput LED_FAULT = DigitalOutput(PG7);
    DigitalOutput LED_CAN = DigitalOutput(PG6);
    DigitalOutput LED_FLASH = DigitalOutput(PG5);
    DigitalOutput LED_SLEEP = DigitalOutput(PG4);

    STLIB::start();

    LED_OPERATIONAL.turn_on();
    LED_FAULT.turn_on();
    LED_CAN.turn_on();
    LED_FLASH.turn_on();
    LED_SLEEP.turn_on();

    while(1){
        ErrorHandlerModel::ErrorHandlerUpdate();
    }
}
