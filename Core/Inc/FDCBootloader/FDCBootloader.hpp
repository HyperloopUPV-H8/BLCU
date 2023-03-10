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


#define FDCB_CURRENT_VERSION        ((uint8_t)0x03)

#define FDCB_VERBOSE_LEVEL 			1
#define FDCB_TIMEOUT_MS 			2000
#define FDCB_FIRST_BYTE_NONE 		0xFF

#define FDCB_ACK  					((uint8_t)0x79)
#define FDCB_NACK					((uint8_t)0x1f)

#define SECTOR_SIZE_IN_32BITS_WORDS  ((uint16_t)32768U)
#define SECTOR_SIZE_IN_FDCAN_PACKETS ((uint16_t)2048U)

#define FDCB_BLOCK_SIZE				((uint8_t)8U)

class FDCB{
public:
	enum FDCB_State{
		READY,
		FAULT,
		NOSTATE,
	};
private:
	enum BootLoaderOrders{
	    GET_VERSION         = 0x50,
	    READ_MEMORY         = 0x40,
	    WRITE_MEMORY        = 0x30,
	    ERASE_MEMORY        = 0x20,
	    GO                  = 0x10,
	};



	static uint8_t fdcan;
	static bool ready;

public:

	static void set_up(FDCAN::Peripheral& fdcan);

	static bool get_version(uint8_t& version);

	//Data tiene que tener 131072 bytes alocados
	static bool read_memory(uint8_t sector, uint8_t* data);

	static bool write_memory(uint8_t sector, uint8_t* data);

	static bool erase_memory();

private:
	static bool __wait_for_data_message(uint8_t order, FDCAN::Packet& packet);
	static bool __wait_for_ack(uint8_t order, FDCAN::Packet& packet);
	static bool __wait_for_bootloader_message();
	static void __copy_data_from_packet(FDCAN::Packet& packet, uint8_t* data);
	static bool __send_ack(uint8_t order);
	static bool __send_nack(uint8_t order);


	 static bool __write_memory_order(uint32_t address, vector<uint8_t> data);
	 static bool __wait_for_bootloader_command_response(vector<uint8_t>& data);

	 static void __addr_to_byte_vector(vector<uint8_t>& v, uint32_t addr);
};
