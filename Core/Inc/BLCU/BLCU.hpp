/**
 * BLCU.h
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

#pragma once

#include "ST-LIB.hpp"
#include "C++Utilities/CppUtils.hpp"
#include "FDCBootloader/FDCBootloader.hpp"

class BLCU {
public:
    enum Target{
        Master,
        NOTARGET,
    };

    enum GeneralStates{
        READY,
        BOOTING,
        FAULT,
    };

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
public:

    static void reset_all();

    static void force_quit_bootmode(const Target& target);

    static void get_id(const Target& target);

    static void read(const Target& target, const uint32_t& address, const uint32_t& size);

    static void write(const Target& target, span<uint8_t> data);

    static void erase_all();

    static void set_up(string ip = "192.168.1.4", string mask = "255.255.0.0", string gateway = "192.168.1.1");

    static void start();

    static void update();

private:
    static void set_up_peripherals();

    static void set_up_state_machine();

    static void set_up_resets();

    static void set_up_boots();

    static void set_up_leds();

    static void resets_start();

    static void boots_start();

    static void leds_start();

    static void send_to_bootmode(Target target);

};
