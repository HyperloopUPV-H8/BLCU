/**
 * BLCU.h
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

#pragma once

#include "ST-LIB.hpp"
#include "FDCBootloader/FDCBootloader.hpp"
#include "FDCBootloader/BootloaderTFTP.hpp"
#include "Utilities/orders_data.hpp"

#define BLCU_IP 		"192.168.1.4"
#define BLCU_MASK 		"255.255.255.0"
#define BLCU_GATEWAY 	"192.168.1.1"
#define BLCU_PORT		((uint32_t)50500)

extern HeapOrder ack;

namespace BLCU {
    enum GeneralStates{
        READY,
        BOOTING,
        FAULT,
    };


    StateMachine specific_state_machine;
    StateMachine general_state_machine;

    unordered_map<Target, DigitalOutput> resets;
    unordered_map<Target, DigitalOutput> boots;

    uint8_t fdcan;
    DigitalOutput LED_OPERATIONAL;
    DigitalOutput LED_FAULT;
    DigitalOutput LED_CAN;
    DigitalOutput LED_FLASH;
    DigitalOutput LED_SLEEP;

    Target current_target;

    string ip, mask, gateway;
    uint32_t port;
    ServerSocket* tcp_socket;


    orders_data_t orders_data = {
   			BLCU::Target::NOTARGET,
   			0
   	};

    void set_up();
	void start();
	void update();

	/***********************************************/
	//              Orders methods
	/***********************************************/
    void reset_all();
    void force_quit_bootmode(); //ESta seguramente se vaya fuera
    void get_version();
    void read_program();
    void write_program();
    void erase_program();
    void finish_write_read_order();

    void __end_booting();
    void __send_to_bootmode(const BLCU::Target& target);
    void __turn_off_all_boards();

    /***********************************************/
	//                  Start methods
	/***********************************************/
    void __tcp_start();
    void __resets_start();
    void __boots_start();
    void __leds_start();

	/***********************************************/
	//                  SetUp methods
	/***********************************************/
    void __set_up_state_machine(); //TODO: revisar
    void __set_up_peripherals();
    void __set_up_fdcan();
    void __set_up_ethernet();
    void __set_up_resets();
    void __set_up_boots();
    void __set_up_leds();


    /////////////////////////////////////////////////////////////////

    void set_up()
    {
        BLCU::__set_up_peripherals();
        BLCU::__set_up_state_machine();
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


    	/***********************************************/
    	//                  Orders methods
    	/***********************************************/

    void reset_all(){
    	for (auto& [target, reset]: resets)
        {
            reset.turn_off();
        }

        for (auto& [target, reset]: resets)
        {
            reset.turn_on();
        }

        orders_data.clean_data();
    }

    void force_quit_bootmode(){//TODO: no deberia existir xD
    	if (BLCU::orders_data.target == BLCU::Target::NOTARGET) {
    		return;
    	}

    	BLCU::resets[BLCU::orders_data.target].turn_off();
    	BLCU::resets[BLCU::orders_data.target].turn_on();
    	return;
    }

    void get_version(){
    	BLCU::specific_state_machine.force_change_state(BOOTING);

    	uint8_t temporal_value = 0;
    	if (not FDCB::get_version(temporal_value)){//TODO: molaria manda NACK si falla
            __end_booting();
            return;   
        }
            
    	BLCU::orders_data.version = temporal_value;

    	//TODO: ahora se deberia mandar el valor de la version

    	__end_booting();
    }

    void read_program(){
    	BLCU::specific_state_machine.force_change_state(BOOTING);

    	BLCU::__turn_off_all_boards();
    	BLCU::__send_to_bootmode(BLCU::orders_data.target);

    	BTFTP::on(BTFTP::Mode::READ);
    	printf("Solicitud lectura\n");
    	BLCU::tcp_socket->send_order(ack);
    	printf("ACK mandado!\n");

    }

    void write_program(){
    	BLCU::specific_state_machine.force_change_state(BOOTING);

    	BLCU::__turn_off_all_boards();
    	BLCU::__send_to_bootmode(BLCU::orders_data.target);

    	BTFTP::on(BTFTP::Mode::WRITE);

    	BLCU::tcp_socket->send_order(ack);
    }

    void erase_program(){
    	BLCU::specific_state_machine.force_change_state(BOOTING);

    	FDCB::erase_memory();//TODO: molaria manda NACK si falla

    	__end_booting();
    }


    void finish_write_read_order(){
    	BTFTP::off();

    	__end_booting();
    }

    void __end_booting(){
        BLCU::orders_data.clean_data();
    	BLCU::specific_state_machine.force_change_state(READY);
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

    	/***********************************************/
    	//                  Start methods
    	/***********************************************/
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

    	/***********************************************/
    	//                  SetUp methods
    	/***********************************************/
    void __set_up_state_machine(){
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


    void __set_up_peripherals(){
    	BLCU::__set_up_fdcan();
    	BLCU::__set_up_ethernet();
        BLCU::__set_up_resets();
        BLCU::__set_up_boots();
        BLCU::__set_up_leds();
    }

    void __set_up_fdcan(){
    	BLCU::fdcan = FDCAN::inscribe(FDCAN::fdcan1);
    }

    void __set_up_ethernet(){
    	BLCU::ip = BLCU_IP;
    	BLCU::mask = BLCU_MASK;
    	BLCU::gateway = BLCU_GATEWAY;
    	BLCU::port = BLCU_PORT;
    }

    void __set_up_resets(){
    	BLCU::resets[VCU] = DigitalOutput(PA12);
    	BLCU::resets[OBCCU] = DigitalOutput(PG3);
    	BLCU::resets[BMSA] = DigitalOutput(PD11);
    	BLCU::resets[LCUM] = DigitalOutput(PD9);
    	BLCU::resets[LCUS] = DigitalOutput(PB12);
    	BLCU::resets[PCU] = DigitalOutput(PG1);
    }

    void __set_up_boots(){
    	BLCU::boots[VCU] = DigitalOutput(PA11);
    	BLCU::boots[OBCCU] = DigitalOutput(PG2);
    	BLCU::boots[BMSA] = DigitalOutput(PD10);
    	BLCU::boots[LCUM] = DigitalOutput(PD8);
    	BLCU::boots[LCUS] = DigitalOutput(PE15);
    	BLCU::boots[PCU] = DigitalOutput(PE7);
    }

    void __set_up_leds(){
    	BLCU::LED_OPERATIONAL = DigitalOutput(PG8);
    	BLCU::LED_FAULT = DigitalOutput(PG7);
    	BLCU::LED_CAN = DigitalOutput(PG6);
    	BLCU::LED_FLASH = DigitalOutput(PG5);
    	BLCU::LED_SLEEP = DigitalOutput(PG4);
    }


};
