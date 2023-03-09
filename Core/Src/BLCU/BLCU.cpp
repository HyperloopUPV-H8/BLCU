/**
 * BLCU.cpp
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

#include "BLCU/BLCU.hpp"

StateMachine BLCU::blcu_state_machine = StateMachine();

unordered_map<BLCU::Target, DigitalOutput> BLCU::resets = {};
unordered_map<BLCU::Target, DigitalOutput> BLCU::boots = {};

uint8_t BLCU::fdcan = 0;

DigitalOutput BLCU::LED_OPERATIONAL = DigitalOutput();
DigitalOutput BLCU::LED_FAULT = DigitalOutput();
DigitalOutput BLCU::LED_CAN = DigitalOutput();
DigitalOutput BLCU::LED_FLASH = DigitalOutput();
DigitalOutput BLCU::LED_SLEEP = DigitalOutput();

BLCU::Target BLCU::current_target = BLCU::NOTARGET;

string BLCU::ip = "";
string BLCU::mask = "";
string BLCU::gateway = "";

void BLCU::force_quit_bootmode(const BLCU::Target& target){
	//TODO:
	return;
}

void BLCU::reset_all(){
	for (auto& [target, reset]: resets)
    {
        reset.turn_off();
    }

    for (auto& [target, reset]: resets)
    {
        reset.turn_on();
    }
}

void BLCU::set_up(string ip, string mask, string gateway)
{
	ip = ip;
	mask = mask;
	gateway = gateway;

    set_up_peripherals();
    set_up_state_machine();

}

void BLCU::start(){

    STLIB::start(Board, ip, mask, gateway, UART::uart2);
    resets_start();
    boots_start();
    leds_start();

}

void BLCU::update(){
    STLIB::update();
}

/***********************************************/
//                  Private methods
/***********************************************/

void BLCU::set_up_peripherals(){
    BLCU::set_up_resets();
    BLCU::set_up_boots();
    BLCU::set_up_leds();

    optional<uint8_t> fdcan_temporal = FDCAN::inscribe(FDCAN::fdcan1);

    if (not fdcan_temporal.has_value())
    {
        ErrorHandler("Unable to inscribe fdcan1");
    }    
}

void BLCU::set_up_state_machine(){
//    blcu_state_machine = StateMachine(READY);
//    blcu_state_machine.add_state(BOOTING);
//
//    blcu_state_machine.add_transition(BOOTING, READY, [](){
//        if (FDCB::get_state() == FDCB::FDCB_State::READY)
//        {
//            return true;
//        }
//        return false;
//    });
//
//    blcu_state_machine.add_transition(READY, FAULT, [&](){
//        if(ErrorHandlerModel::error_triggered != 0){
//            return true;
//        }
//        return false;
//    });
//
//    blcu_state_machine.add_transition(BOOTING, FAULT, [&](){
//        if(ErrorHandlerModel::error_triggered != 0){
//            force_quit_bootmode(current_target);
//            return true;
//        }
//        return false;
//    });
//
//    blcu_state_machine.add_enter_action([&](){
//        LED_FLASH.turn_on();
//    }, BOOTING);
//
//    blcu_state_machine.add_exit_action([&](){
//        LED_FLASH.turn_off();
//    }, BOOTING);
//
//    blcu_state_machine.add_enter_action([&](){
//        LED_OPERATIONAL.turn_off();
//        LED_FAULT.turn_on();
//    }, FAULT);


}

void BLCU::set_up_resets(){
    resets[Master] = DigitalOutput(PA12);
}

void BLCU::set_up_boots(){
    boots[Master] = DigitalOutput(PA11);

}

void BLCU::set_up_leds(){
    LED_OPERATIONAL = DigitalOutput(PG8);
    LED_FAULT = DigitalOutput(PG7);
    LED_CAN = DigitalOutput(PG6);
    LED_FLASH = DigitalOutput(PG5);
    LED_SLEEP = DigitalOutput(PG4);
}

void BLCU::resets_start(){
    for (auto& [target, reset]: resets)
    {
        reset.turn_on();
    }
}

void BLCU::boots_start(){
    for (auto& [target, boot]: boots)
    {
        boot.turn_off();
    }
}

void BLCU::leds_start(){
    LED_OPERATIONAL.turn_on();
    LED_FAULT.turn_off();
    LED_CAN.turn_off();
    LED_FLASH.turn_off();
    LED_SLEEP.turn_off();
}

void BLCU::send_to_bootmode(Target target){
    boots[target].turn_on();
    resets[target].turn_off();

    resets[target].turn_on();
    boots[target].turn_off();
}
