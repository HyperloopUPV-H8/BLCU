#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{
	void reset_all(){
		for (auto& [target, reset]: resets)
		{
			reset.turn_off();
		}

		for (auto& [target, reset]: resets)
		{
			reset.turn_on();
		}

		HAL_NVIC_SystemReset();//Good bye :)
	}

	void get_version(){
		if(BLCU::specific_state_machine.current_state != BLCU::SpecificStates::READY){
			BLCU::tcp_socket->send_order(nack);
			return;
		}

		BLCU::specific_state_machine.force_change_state(BOOTING);

		uint8_t temporal_value = 0;
		if (not FDCB::get_version(temporal_value)){
			BLCU::tcp_socket->send_order(nack);
			__abort_booting();
			return;
		}

		BLCU::orders_data.version = temporal_value;
		BLCU::tcp_socket->send_order(get_version_order);

		__end_booting();
	}

	void read_program(){
		if(BLCU::specific_state_machine.current_state != BLCU::SpecificStates::READY){
			BLCU::tcp_socket->send_order(nack);
			return;
		}

		BLCU::specific_state_machine.force_change_state(BOOTING);

		BTFTP::on(BTFTP::Mode::READ);

		BLCU::tcp_socket->send_order(ack);
	}

	void write_program(){
		if(BLCU::specific_state_machine.current_state != BLCU::SpecificStates::READY){
			BLCU::tcp_socket->send_order(nack);
			return;
		}

		BLCU::specific_state_machine.force_change_state(BOOTING);

		BTFTP::on(BTFTP::Mode::WRITE);

		BLCU::tcp_socket->send_order(ack);
	}

	void erase_program(){
		if(BLCU::specific_state_machine.current_state != BLCU::SpecificStates::READY){
			BLCU::tcp_socket->send_order(nack);
			return;
		}

		BLCU::specific_state_machine.force_change_state(BOOTING);

		if(not FDCB::erase_memory()){
			BLCU::tcp_socket->send_order(nack);
			__abort_booting();
			return;
		}else{
			BLCU::tcp_socket->send_order(ack);
		}

		__end_booting();
	}

}
