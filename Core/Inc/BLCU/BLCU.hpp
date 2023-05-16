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


class BLCU {
public:

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
		double version;

		void clean_data(){
			target = BLCU::Target::NOTARGET;
			version = 0;
		}
	}orders_data_t;

private:
    static StateMachine blcu_state_machine;

    static unordered_map<Target, DigitalOutput> resets;
    static unordered_map<Target, DigitalOutput> boots;

    static uint8_t fdcan;
    static DigitalOutput LED_OPERATIONAL;
    static DigitalOutput LED_FAULT;
    static DigitalOutput LED_CAN;
    static DigitalOutput LED_FLASH;
    static DigitalOutput LED_SLEEP;

    static Target current_target;

    static string ip, mask, gateway;
    static uint32_t port;
    static ServerSocket tcp_socket;
    static orders_data_t orders_data;

	static HeapOrder write_program_order;
	static HeapOrder read_program_order;
	static HeapOrder erase_program_order;
	static HeapOrder get_version_order;
	static HeapOrder reset_all_order;
public:

    static void reset_all();

    static void force_quit_bootmode(); //ESta seguramente se vaya fuera

    static void get_version();

    static void read_program();

    static void write_program();

    static void erase_program();

    static void finish_write_read_order();

    static void set_up();

    static void start();

    static void update();

private:
	/***********************************************/
	//                  Orders methods
	/***********************************************/

    static void __send_to_bootmode(const BLCU::Target& target);

    static void __turn_off_all_boards();

    /***********************************************/
	//                  Start methods
	/***********************************************/
    static void __resets_start();

    static void __boots_start();

    static void __leds_start();

	/***********************************************/
	//                  SetUp methods
	/***********************************************/
    static void __set_up_state_machine(); //TODO:

    static void __set_up_orders(); //TODO:

    static void __set_up_peripherals();

    static void __set_up_resets();

    static void __set_up_boots();

    static void __set_up_leds();

};
