/*
 * Bootloader.hpp
 *
 *  Created on: Jan 21, 2022
 *      Author: Pablo
 */

#pragma once
#undef HAL_ETH_MODULE_ENABLED

#include "ST-LIB.hpp"
#include "C++Utilities/CppUtils.hpp"


#define VERBOSE_LEVEL 1
#define TIMOUT_MS 2000
#define FDCB_FIRST_BYTE_NONE 0xFF

//Dependencias, TIM START
//				PIN START
//				PRINTF setUP
//				UART START
//				FDCAN inscribe
//				FDCAN START


class FDCB{
public:
	enum FDCB_State{
		READY,
		FAULT,
		NOSTATE,
	};
private:
	enum BootLoaderOrders{
	    ACK                 = 0x79,
	    NACK                = 0x1f,
	    GET                 = 0x00,
	    GET_VERSION         = 0x01,
	    GET_ID              = 0x02,
	    READ_MEMORY         = 0x11,
	    WRITE_MEMORY        = 0x31,
	    ERASE_MEMORY        = 0x44,
	    WRITE_PROTECT       = 0x63,
	    WRITE_UNPROTECT     = 0x73,
	    READOUT_PROTECT     = 0x82,
	    READOUT_UNPROTECT   = 0x92,
	    GO                  = 0x21,
	};



	static uint8_t fdcan;
	static vector<uint8_t> empty_data;

	static bool ready;

	static StateMachine fdcb_state_machine;

public:

	static void set_up(uint8_t fdcan);

	static void send_order(BootLoaderOrders order = FDCB::NACK);

	static void update();

	static FDCB_State get_state();

private:
	// /*The Get command allows the host to get the version of the bootloader and the supported commands. When the
	// bootloader receives the Get command, it transmits the bootloader version and the supported command codes to
	// the host.*/
	// static bool get(vector<uint8_t>& res);

	// /*The Get Version command is used to get the bootloader version.*/
	// static bool get_version(uint32_t& res);

	// /*The Get ID command is used to get the version of the STM32 product ID (identification). */
	// static bool get_id(uint32_t& res);

	// /*The Read Memory command is used to read data from any valid memory address: RAM, flash memory, and
	// information block (system memory or option byte areas).*/
	// static bool read_memory(vector<uint8_t>& res, uint32_t address, uint32_t byte_count = 64);

	// /*The Exit command is used to execute downloaded code .*/
	// static bool go_to(const uint32_t& address);

	// /*The Write Memory command is used to write data to any valid memory address of the RAM, flash memory,
	// or option byte area. */
	// static bool write_memory(uint32_t address, vector<uint8_t>& data);

	// /*The Erase Memory command allows the host to erase flash memory pages.*/
	// static bool erase_memory();

	// /*The Write Protect command is used to enable the write protection for some or all flash memory sectors.*/
	// static bool write_protect();

	// /*The Write Unprotect command is used to disable the write protection of all the flash memory sectors. */
	// static bool write_unprotect();

	// /*The Readout Protect command is used to enable the flash memory readout protection*/
	// static bool readout_protect();

	// /*The Readout Unprotect command is used to disable the flash memory readout protection.*/
	// static bool readout_unprotect();

	// static bool __write_memory_order(uint32_t address, vector<uint8_t> data);
	// static bool __wait_for_bootloader_command_response(vector<uint8_t>& data);
	// static optional<FDCAN::Packet> __wait_for_bootloader_message(uint8_t match_first_byte = FDCB_FIRST_BYTE_NONE);
	// static void __addr_to_byte_vector(vector<uint8_t>& v, uint32_t addr);
};
