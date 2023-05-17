#include "BLCU/BLCU.hpp"

void BLCU::__set_up_state_machine(){
    BLCU::specific_state_machine = StateMachine(READY);
    BLCU::specific_state_machine.add_state(BOOTING);
    BLCU::specific_state_machine.add_state(FAULT);

    BLCU::specific_state_machine.add_transition(READY, FAULT, [&](){
        if(ErrorHandlerModel::error_triggered != 0){
            return true;
        }
        return false;
    });

    BLCU::specific_state_machine.add_transition(BOOTING, FAULT, [&](){
        if(ErrorHandlerModel::error_triggered != 0){
        	FDCB::erase_memory();
            return true;
        }
        return false;
    });


    BLCU::specific_state_machine.add_enter_action([&](){
    	BLCU::LED_OPERATIONAL.turn_off();
    	BLCU::LED_FAULT.turn_on();
    	BLCU::LED_CAN.turn_off();
   }, FAULT);

    BLCU::specific_state_machine.add_enter_action([&](){
    	BLCU::LED_OPERATIONAL.turn_on();
    	BLCU::LED_FAULT.turn_off();
    	BLCU::LED_CAN.turn_off();

        BLCU::reset_all();
    	BLCU::orders_data.clean_data();
    }, READY);

    BLCU::specific_state_machine.add_enter_action([&](){
    	BLCU::LED_OPERATIONAL.turn_on();
    	BLCU::LED_FAULT.turn_off();
    	BLCU::LED_CAN.turn_on();

		BLCU::__turn_off_all_boards();
		BLCU::__send_to_bootmode(BLCU::orders_data.target);

	}, BOOTING);


    Time::register_low_precision_alarm(1, [&](){
    	BLCU::specific_state_machine.check_transitions();
	});

}
