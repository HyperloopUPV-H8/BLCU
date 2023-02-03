/*
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
	};

public:
	unordered_map<Target, DigitalOutput> resets;
	unordered_map<Target, DigitalOutput> boots;

	uint8_t fdcan;
	bool boot_mode = false;


	BLCU(uint8_t fdcan) : fdcan(fdcan){
		FDCB::set_up(fdcan);
	}

	void add_resets(){
		resets[Master] = DigitalOutput(PA12);
		//...
	}

	void add_boots(){
		boots[Master] = DigitalOutput(PA11);
		//...
	}

	void send_to_bootmode(Target target){
		boots[target].turn_on();
		resets[target].turn_off();
		int i;
		for (i = 0; i < 10000000; ++i) {
			__NOP();
		}
		resets[target].turn_on();
		boots[target].turn_off();

		boot_mode = true;
	}

	bool exit_bootmode(){
		bool res = FDCB::go_to(0x8000000);

		if (res) {
			boot_mode = false;
			return res;
		}

		return res;
	}

	bool get_board_id(uint32_t& id){
		return FDCB::get_id(id);
	}

};
