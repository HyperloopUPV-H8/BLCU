#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{
	void finish_write_read_order(bool error_ok){
		BTFTP::off();

		if(not error_ok){
			BLCU::tcp_socket->send_order(nack);
			__abort_booting();
			return;
			}else{
				BLCU::tcp_socket->send_order(ack);
			}

		__end_booting();
   }

   void __end_booting(){
       BLCU::orders_data.clean_data();
       BLCU::specific_state_machine.force_change_state(SpecificStates::READY);
   }

   void __abort_booting(){
		BLCU::orders_data.clean_data();
		BLCU::programming_error = true;
   }

   void __send_to_bootmode(const BLCU::Target& target){
		BLCU::boots[target].turn_on();
		BLCU::resets[target].turn_off();

		BLCU::resets[target].turn_on();
		BLCU::boots[target].turn_off();
   }

   void __turn_off_all_boards(){
		for (auto& [target, reset_pin]: BLCU::resets)
		{
			reset_pin.turn_off();
		}
   }

}
