/**
 * BLCU.cpp
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

#include "BLCU/BLCU.hpp"


void BLCU::set_up()
{
	BLCU::__set_up_orders();
    BLCU::__set_up_peripherals();
    BLCU::__set_up_state_machine();
}

void BLCU::start(){
    STLIB::start(ip, mask, gateway, UART::uart2);
    BLCU::__tcp_start();
    BTFTP::start();

	BLCU::__resets_start();
    BLCU::__boots_start();
    BLCU::__leds_start();
}

void BLCU::update(){
    STLIB::update();
}


	/***********************************************/
	//                  Orders methods
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

    BLCU::orders_data.clean_data();
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
	BLCU::specific_state_machine.force_change_state(BOOTING);

	uint8_t temporal_value = 0;
	FDCB::get_version(temporal_value);
	BLCU::orders_data.version = temporal_value;

	//TODO: ahora se deberia mandar el valor de la version

	BLCU::orders_data.clean_data();
	BLCU::specific_state_machine.force_change_state(READY);
}

void BLCU::read_program(){
	BLCU::specific_state_machine.force_change_state(BOOTING);

	BLCU::__turn_off_all_boards();
	BLCU::__send_to_bootmode(BLCU::orders_data.target);

	BTFTP::on(BTFTP::Mode::READ);

	BLCU::tcp_socket.send_order(ack);
}

void BLCU::write_program(){
	BLCU::specific_state_machine.force_change_state(BOOTING);

	BLCU::__turn_off_all_boards();
	BLCU::__send_to_bootmode(BLCU::orders_data.target);

	BTFTP::on(BTFTP::Mode::WRITE);

	BLCU::tcp_socket.send_order(ack);
}

void BLCU::erase_program(){
	BLCU::specific_state_machine.force_change_state(BOOTING);

	FDCB::erase_memory();

	BLCU::orders_data.clean_data();
	BLCU::specific_state_machine.force_change_state(READY);
}


void BLCU::finish_write_read_order(){
	BTFTP::off();

	BLCU::orders_data.clean_data();
	BLCU::specific_state_machine.force_change_state(READY);
}


void BLCU::__send_to_bootmode(const BLCU::Target& target){
	BLCU::boots[target].turn_on();
	BLCU::resets[target].turn_off();

	BLCU::resets[target].turn_on();
	BLCU::boots[target].turn_off();
}

void BLCU::__turn_off_all_boards(){
	for (auto& [target, reset_pin]: BLCU::resets)
	{
		reset_pin.turn_off();
	}
}

	/***********************************************/
	//                  Start methods
	/***********************************************/
void BLCU::__tcp_start(){
    BLCU::tcp_socket = ServerSocket(BLCU::ip, BLCU::port);
}

void BLCU::__resets_start(){
    for (auto& [target, reset_pin]: BLCU::resets)
    {
    	reset_pin.turn_on();
    }
}

void BLCU::__boots_start(){
    for (auto& [target, boot_pin]: BLCU::boots)
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


void BLCU::__set_up_peripherals(){
	BLCU::__set_up_fdcan();
	BLCU::__set_up_ethernet();
    BLCU::__set_up_resets();
    BLCU::__set_up_boots();
    BLCU::__set_up_leds();
}

void BLCU::__set_up_fdcan(){
	optional<uint8_t> fdcan_temporal = FDCAN::inscribe(FDCAN::fdcan1);

	if (not fdcan_temporal.has_value())
	{
		ErrorHandler("Unable to inscribe fdcan1");
		return;
	}

	BLCU::fdcan = fdcan_temporal.value();
}

void BLCU::__set_up_ethernet(){
	BLCU::ip = BLCU_IP;
	BLCU::mask = BLCU_MASK;
	BLCU::gateway = BLCU_GATEWAY;
	BLCU::port = BLCU_PORT;
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
