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
#include "ServerSocket.hpp"

#define BLCU_IP 		"192.168.1.4"
#define BLCU_MASK 		"255.255.0.0"
#define BLCU_GATEWAY 	"192.168.1.1"
#define BLCU_PORT		((uint32_t)50500)

namespace BLCU {

    enum Target{
        VCU,
		OBCCU,
		BMSA,
		LCUM,
		LCUS,
		PCU,
        NOTARGET,
    };

    enum GeneralStates{
        READY,
        BOOTING,
        FAULT,
    };

	typedef struct {
		BLCU::Target target;
		uint16_t version;

		void clean_data(){
			target = BLCU::Target::NOTARGET;
			version = 0;
		}

	}orders_data_t;


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
    ServerSocket tcp_socket;

	orders_data_t orders_data;
	HeapOrder write_program_order;
	HeapOrder read_program_order;
	HeapOrder erase_program_order;
	HeapOrder get_version_order;
	HeapOrder reset_all_order;
	HeapOrder ack;

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
    void __set_up_orders();
    void __set_up_peripherals();
    void __set_up_fdcan();
    void __set_up_ethernet();
    void __set_up_resets();
    void __set_up_boots();
    void __set_up_leds();

};
