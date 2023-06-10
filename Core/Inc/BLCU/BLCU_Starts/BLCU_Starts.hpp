#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{
    void __tcp_start(){
        BLCU::tcp_socket = new ServerSocket(BLCU::ip, BLCU::port);
    }

    void __resets_start(){
        for (auto& [target, reset_pin]: BLCU::resets)
        {
        	reset_pin.turn_on();
        }
    }

    void __boots_start(){
        for (auto& [target, boot_pin]: BLCU::boots)
        {
        	boot_pin.turn_off();
        }
    }

    void __leds_start(){
    	BLCU::LED_OPERATIONAL.turn_on();
    	BLCU::LED_FAULT.turn_off();
    	BLCU::LED_CAN.turn_off();
    	BLCU::LED_FLASH.turn_off();
    	BLCU::LED_SLEEP.turn_off();
    }
}
