/*
 * BootloaderTFTP.hpp
 *
 *  Created on: 21 feb. 2022
 *      Author: Pablo
 */



#pragma once

#include "C++Utilities/CppUtils.hpp"
#include "lwip/apps/tftp_server.h"
#include "ErrorHandler/ErrorHandler.hpp"
#include "Flash/Flash.hpp"
//#include "FDCBootloader/FDCBootloader.hpp"

//#ifdef HAL_ETH_MODULE_ENABLED

class BTFTP{
public:

	struct BHandle{
		string name;
		string mode;
		uint8_t read_write;
		uint32_t address;
		uint32_t remaining = 0xFFFFF;

		static const uint32_t max_addr = 0x080FFFFF;
		static const uint32_t mem_size = 0xFFFFF;
	};


public:
	static void start();

//	static void on();
//
//	static void off();
//
//	static BTFTP::State get_state();
private:
	static bool ready;

	static void* open(const char* fname, const char* mode, u8_t write);

	static void close(void* handle);

	static int read(void* handle, void* buf, int bytes);

	static int write(void* handle, struct pbuf* p);

	static void re(void* handle);
};

//#endif
