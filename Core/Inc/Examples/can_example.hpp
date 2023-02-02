/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Alejandro
 */
#pragma once

#include "ST-LIB.hpp"

int can_example(void)
{
	uint8_t fdcan = FDCAN::inscribe(FDCAN::fdcan1).value();

	STLIB::start(Board, "192.168.1.4", "255.255.0.0", "192.168.1.1", UART::uart2);

	array<uint8_t, 4> data = {0x34, 0x46, 0x25, 0x43};
	while (1) {
		FDCAN::transmit(fdcan, 0x34, data, FDCAN::DLC::BYTES_4);
		HAL_Delay(1);
	}
}
