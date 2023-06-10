
#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{
	void __set_up_state_machine(){
		__set_up_general_state_machine();
		__set_up_specific_state_machine();
		BLCU::general_state_machine.add_state_machine(specific_state_machine, GeneralStates::OPERATIONAL);

		Time::register_low_precision_alarm(1, [&](){
					BLCU::general_state_machine.check_transitions();
		});

   }

   void __set_up_general_state_machine(){
	   BLCU::general_state_machine = {GeneralStates::INITIAL};
		BLCU::general_state_machine.add_state(GeneralStates::OPERATIONAL);
		BLCU::general_state_machine.add_state(GeneralStates::FAULT);

		ProtectionManager::link_state_machine(general_state_machine, GeneralStates::FAULT);
		ProtectionManager::set_id(Boards::ID::BLCU_VEHICLE);

		//Enter actions
		BLCU::general_state_machine.add_enter_action([&](){
			Time::set_timeout(BLCU::max_tcp_connection_timeout, [&](){
				if(not (BLCU::tcp_socket->state == ServerSocket::ServerState::ACCEPTED )){
							tcp_timeout = true;
				}
			});
		}, GeneralStates::INITIAL);

		BLCU::general_state_machine.add_enter_action([&](){
			LED_FAULT.turn_on();
		}, GeneralStates::FAULT);

		BLCU::general_state_machine.add_enter_action([&](){
			LED_OPERATIONAL.turn_on();
		}, GeneralStates::OPERATIONAL);

		//Exit actions
		BLCU::general_state_machine.add_exit_action([&](){
			LED_OPERATIONAL.turn_off();
		}, GeneralStates::INITIAL);

		BLCU::general_state_machine.add_exit_action([&](){
			LED_FAULT.turn_off();
		}, GeneralStates::FAULT);

		BLCU::general_state_machine.add_exit_action([&](){
			LED_OPERATIONAL.turn_off();
		}, GeneralStates::OPERATIONAL);

		//Transitions
		BLCU::general_state_machine.add_transition(GeneralStates::INITIAL, GeneralStates::OPERATIONAL, [&](){
			return BLCU::tcp_socket->state == ServerSocket::ServerState::ACCEPTED;
		});
		BLCU::general_state_machine.add_transition(GeneralStates::INITIAL, GeneralStates::FAULT, [&](){
			if(BLCU::tcp_timeout) ErrorHandler("TCP connections could not be established in time and timed out");
			return BLCU::tcp_timeout;
		});
		BLCU::general_state_machine.add_transition(GeneralStates::OPERATIONAL, GeneralStates::FAULT, [&](){
			if(BLCU::tcp_socket->state!= ServerSocket::ServerState::ACCEPTED){
				ErrorHandler("TCP connections fell");
				return true;
			}
			return false;
		});

		//Cyclic actions
		BLCU::general_state_machine.add_low_precision_cyclic_action([&](){LED_OPERATIONAL.toggle();}, (chrono::milliseconds)150, INITIAL);

		BLCU::general_state_machine.add_low_precision_cyclic_action(ProtectionManager::check_protections, (chrono::milliseconds)1 , OPERATIONAL);
   }

   void __set_up_specific_state_machine(){
   	BLCU::specific_state_machine = StateMachine(SpecificStates::READY);
		BLCU::specific_state_machine.add_state(SpecificStates::BOOTING);


		//Enter actions
		BLCU::specific_state_machine.add_enter_action([&](){
			BLCU::LED_OPERATIONAL.turn_on();
		}, SpecificStates::READY);

		BLCU::specific_state_machine.add_enter_action([&](){
			BLCU::__turn_off_all_boards();
			BLCU::__send_to_bootmode(BLCU::orders_data.target);
		}, SpecificStates::BOOTING);

		//Exit actions
		BLCU::specific_state_machine.add_exit_action([&](){
			BLCU::LED_OPERATIONAL.turn_off();
		}, SpecificStates::READY);

		BLCU::specific_state_machine.add_exit_action([&](){
			BLCU::LED_CAN.turn_off();
		}, SpecificStates::BOOTING);

		//Cyclic actions
		BLCU::general_state_machine.add_low_precision_cyclic_action([&](){LED_CAN.toggle();}, (chrono::milliseconds)75, SpecificStates::BOOTING);
   }

}
