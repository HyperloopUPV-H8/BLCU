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

string BLCU::ip = "192.168.1.4";
string BLCU::mask = "255.255.0.0";
string BLCU::gateway = "192.167.1.1";
uint32_t BLCU::port = 50500;

ServerSocket BLCU::tcp_socket = ServerSocket(BLCU::ip, BLCU::port);

BLCU::orders_data_t BLCU::orders_data = {
		BLCU::Target::NOTARGET,
		0
};

HeapOrder BLCU::write_program_order = {
		700,
		&BLCU::orders_data.target,
};


HeapOrder BLCU::read_program_order = {
		701,
		&BLCU::orders_data.target,
};


HeapOrder BLCU::erase_program_order = {
		702,
		&BLCU::orders_data.target,
};


HeapOrder BLCU::get_version_order = {
		703,
		&BLCU::orders_data.target,
		&BLCU::orders_data.version,
};


HeapOrder BLCU::reset_all_order = {
		704,
		&BLCU::orders_data.target,

};

/***********************************************/
//                  Public methods
/***********************************************/


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

void BLCU::force_quit_bootmode(){//TODO: no deberia existir xD
	if (BLCU::orders_data.target == BLCU::Target::NOTARGET) {
		return;
	}

	BLCU::resets[BLCU::orders_data.target].turn_off();
	BLCU::resets[BLCU::orders_data.target].turn_on();
	return;
}

void BLCU::get_version(){
	BLCU::blcu_state_machine.force_change_state(BOOTING);

	uint8_t temporal_value = 0;
	FDCB::get_version(temporal_value);
	BLCU::orders_data.version = temporal_value;

	BLCU::blcu_state_machine.force_change_state(READY);
}

void BLCU::read_program(){
	BLCU::blcu_state_machine.force_change_state(BOOTING);

	BLCU::__turn_off_all_boards();
	BLCU::__send_to_bootmode(BLCU::orders_data.target);

	BTFTP::on(BTFTP::Mode::READ);
}

void BLCU::write_program(){
	BLCU::blcu_state_machine.force_change_state(BOOTING);

	BLCU::__turn_off_all_boards();
	BLCU::__send_to_bootmode(BLCU::orders_data.target);

	BTFTP::on(BTFTP::Mode::WRITE);
}

void BLCU::erase_program(){
	BLCU::blcu_state_machine.force_change_state(BOOTING);

	FDCB::erase_memory();

	BLCU::blcu_state_machine.force_change_state(READY);
}


void BLCU::finish_write_read_order(){
	BTFTP::off();

	BLCU::blcu_state_machine.force_change_state(READY);
}

void BLCU::set_up()
{
	BLCU::__set_up_orders();
    BLCU::__set_up_peripherals();
    BLCU::__set_up_state_machine();
}

void BLCU::start(){
    STLIB::start(ip, mask, gateway, UART::uart2);
    BTFTP::start();

	BLCU::__resets_start();
    BLCU::__boots_start();
    BLCU::__leds_start();
}

void BLCU::update(){
    STLIB::update();
}

/***********************************************/
//                  Private methods
/***********************************************/

	/***********************************************/
	//                  Orders methods
	/***********************************************/

void BLCU::__send_to_bootmode(const BLCU::Target& target){
	BLCU::boots[target].turn_on();
	BLCU::resets[target].turn_off();

	BLCU::resets[target].turn_on();
	BLCU::boots[target].turn_off();
}

void BLCU::__turn_off_all_boards(){
	for (auto& [target, reset_pin]: resets)
	{
		reset_pin.turn_off();
	}
}

	/***********************************************/
	//                  Start methods
	/***********************************************/
void BLCU::__resets_start(){
    for (auto& [target, reset_pin]: resets)
    {
    	reset_pin.turn_on();
    }
}

void BLCU::__boots_start(){
    for (auto& [target, boot_pin]: boots)
    {
    	boot_pin.turn_off();
    }
}

void BLCU::__leds_start(){
	BLCU::LED_OPERATIONAL.turn_on();
	BLCU::LED_FAULT.turn_off();
	BLCU::LED_CAN.turn_off();
	BLCU::LED_FLASH.turn_off();
	BLCU::LED_SLEEP.turn_off();
}

	/***********************************************/
	//                  SetUp methods
	/***********************************************/

void BLCU::__set_up_state_machine(){
    blcu_state_machine = StateMachine(READY);
    blcu_state_machine.add_state(BOOTING);

    blcu_state_machine.add_transition(READY, FAULT, [&](){
        if(ErrorHandlerModel::error_triggered != 0){
            return true;
        }
        return false;
    });

    blcu_state_machine.add_transition(BOOTING, FAULT, [&](){
        if(ErrorHandlerModel::error_triggered != 0){
        	FDCB::erase_memory();
            return true;
        }
        return false;
    });


    blcu_state_machine.add_enter_action([&](){
	   LED_OPERATIONAL.turn_off();
	   LED_FAULT.turn_on();
	   LED_CAN.turn_off();
   }, FAULT);

    blcu_state_machine.add_enter_action([&](){
        LED_OPERATIONAL.turn_on();
        LED_FAULT.turn_off();
        LED_CAN.turn_off();

        BLCU::reset_all();
    	BLCU::orders_data.clean_data();
    }, READY);

    blcu_state_machine.add_enter_action([&](){
		LED_OPERATIONAL.turn_on();
		LED_FAULT.turn_off();
		LED_CAN.turn_on();

		BLCU::__turn_off_all_boards();
		BLCU::__send_to_bootmode(BLCU::orders_data.target);

	}, BOOTING);


    Time::register_low_precision_alarm(1, [&](){
    	blcu_state_machine.check_transitions();
	});

}

void BLCU::__set_up_orders(){
//	BLCU::write_program_order.set_callback(BLCU::write_program);
//	BLCU::read_program_order.set_callback(BLCU::read_program);
//	BLCU::erase_program_order.set_callback(BLCU::erase_program);
//	BLCU::get_version_order.set_callback(BLCU::get_version);
//	BLCU::reset_all_order.set_callback(BLCU::reset_all);
}

void BLCU::__set_up_peripherals(){
    BLCU::__set_up_resets();
    BLCU::__set_up_boots();
    BLCU::__set_up_leds();

    optional<uint8_t> fdcan_temporal = FDCAN::inscribe(FDCAN::fdcan1);

    if (not fdcan_temporal.has_value())
    {
        ErrorHandler("Unable to inscribe fdcan1");
    }
}

void BLCU::__set_up_resets(){
	BLCU::resets[VCU] = DigitalOutput(PA12);
	BLCU::resets[OBCCU] = DigitalOutput(PG3);
	BLCU::resets[BMSA] = DigitalOutput(PD11);
	BLCU::resets[LCUM] = DigitalOutput(PD9);
	BLCU::resets[LCUS] = DigitalOutput(PB12);
	BLCU::resets[PCU] = DigitalOutput(PG1);
}

void BLCU::__set_up_boots(){
	BLCU::boots[VCU] = DigitalOutput(PA11);
	BLCU::boots[OBCCU] = DigitalOutput(PG2);
	BLCU::boots[BMSA] = DigitalOutput(PD10);
	BLCU::boots[LCUM] = DigitalOutput(PD8);
	BLCU::boots[LCUS] = DigitalOutput(PE15);
	BLCU::boots[PCU] = DigitalOutput(PE7);
}

void BLCU::__set_up_leds(){
	BLCU::LED_OPERATIONAL = DigitalOutput(PG8);
	BLCU::LED_FAULT = DigitalOutput(PG7);
	BLCU::LED_CAN = DigitalOutput(PG6);
	BLCU::LED_FLASH = DigitalOutput(PG5);
	BLCU::LED_SLEEP = DigitalOutput(PG4);
}
