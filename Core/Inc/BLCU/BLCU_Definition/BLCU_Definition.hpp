#pragma once

#include "ST-LIB.hpp"
#include "FDCBootloader/FDCBootloader.hpp"
#include "FDCBootloader/BootloaderTFTP.hpp"
#include "BLCU/Utilities/orders_data.hpp"

#define BLCU_IP 		"192.168.1.7"
#define BLCU_MASK 		"255.255.255.0"
#define BLCU_GATEWAY 	"192.168.1.1"
#define BLCU_PORT		((uint32_t)50500)
#define BLCU_ID         ((uint8_t)1)

extern HeapOrder ack;
extern HeapOrder nack;
extern HeapOrder get_version_order;

namespace BLCU {
	enum GeneralStates{
		INITIAL,
		OPERATIONAL,
		FAULT,
	};


    enum SpecificStates{
        READY,
        BOOTING,
    };

    static constexpr uint16_t max_tcp_connection_timeout = 30000;

    StateMachine specific_state_machine;
    StateMachine general_state_machine;

    unordered_map<Target, DigitalOutput> resets;
    unordered_map<Target, DigitalOutput> boots;

    uint8_t fdcan;
    uint8_t initial_led_timer;
    DigitalOutput LED_OPERATIONAL;
    DigitalOutput LED_FAULT;
    DigitalOutput LED_CAN;
    DigitalOutput LED_FLASH;
    DigitalOutput LED_SLEEP;

    Target current_target;

    string ip, mask, gateway;
    uint32_t port;
    ServerSocket* tcp_socket;
    bool tcp_timeout = false;

    bool programming_error = false;

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
    void get_version();
    void read_program();
    void write_program();
    void erase_program();

    void finish_write_read_order(bool error_ok);
    void __end_booting();
    void __abort_booting();
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

    void __set_up_general_state_machine();
    void __set_up_specific_state_machine();
    void __set_up_state_machine(); //TODO: revisar
    void __set_up_protections();
    void __set_up_peripherals();
    void __set_up_fdcan();
    void __set_up_ethernet();
    void __set_up_resets();
    void __set_up_boots();
    void __set_up_leds();

}
