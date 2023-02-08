/**
 *  blcu_boots_and_resets.hpp
 *
 *  Created on: 7 Feb. 2023
 *      Author: Pablo
 */

#pragma once

#include "ST-LIB.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

void blcu_boots_and_resets(){
    vector<Pin*> boot_pins{&PA11, &PG2, &PD10, &PD8, &PE15, &PE7};
    vector<Pin*> reset_pins{&PA12, &PG3, &PD11, &PD9, &PB12, &PG1};
    //DigitalOutput aux = DigitalOutput(PA11);
    vector<DigitalOutput> boots = {};
    vector<DigitalOutput> resets = {};
    //boots.push_back(DigitalOutput(PA11));
    for (Pin* pin: boot_pins)
    {
        boots.push_back(DigitalOutput(*pin));
    }

    for (Pin* pin: reset_pins)
    {
        resets.push_back(DigitalOutput(*pin));
    }
    

    STLIB::start(Board);

    for (DigitalOutput& boot: boots)
    {
        boot.turn_on();
    }

    for (DigitalOutput& reset: resets)
    {
        reset.turn_on();
    }


    while(1){
        ErrorHandlerModel::ErrorHandlerUpdate();
    }
}
