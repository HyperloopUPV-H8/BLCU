/**
 * BLCU.h
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

#pragma once

#include "BLCU_Orders/BLCU_Orders.hpp"
#include "BLCU_Orders/BLCU_PrivateFunctions.hpp"
#include "BLCU_Orders/BLCU_PublicFunctions.hpp"
#include "BLCU_Protections/BLCU_Protections.hpp"
#include "BLCU_SetUps/BLCU_SetUps.hpp"
#include "BLCU_Starts/BLCU_Starts.hpp"
#include "BLCU_StateMachine/BLCU_StateMachine.hpp"

namespace BLCU{

    void set_up()
    {
        BLCU::__set_up_peripherals();
        BLCU::__set_up_state_machine();
        BLCU::__set_up_protections();
    }

    void start(){
        STLIB::start(ip, mask, gateway, UART::uart2);
        BLCU::__tcp_start();
        BTFTP::start();

    	BLCU::__resets_start();
        BLCU::__boots_start();
        BLCU::__leds_start();
    }

    void update(){
        STLIB::update();
    }

}
