/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Alejandro & Pablo
 */
#pragma once

#include "ST-LIB.hpp"

int can_example(void)
{
	optional<uint8_t> fdcan = FDCAN::inscribe(FDCAN::fdcan1);

	if (not fdcan.has_value()) {
		ErrorHandler("Unable to inscribe fdcan");
	}

	STLIB::start(Board, "192.168.1.4", "255.255.0.0", "192.168.1.1", UART::uart2);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	std::vector<uint8_t> v = {1, 2, 3, 4, 5, 0x69, 0x43};

	FDCAN::Packet packet = FDCAN::Packet(v, 0x68, FDCAN::DLC::BYTES_8);
	uint32_t counter = 0;
	while (1) {
		FDCAN::transmit(fdcan.value(), 0x69, v, FDCAN::DLC::BYTES_8);

		if (FDCAN::received_test(fdcan.value())) {
			FDCAN::read(fdcan.value(), &packet);

			printf("Packet received %lu | Id = %lu, Data =", counter, packet.identifier);
			for (auto v : packet.rx_data) {
				printf(" %x ", v);
			}
			printf("| \r");

			counter++;
		}else{

			HAL_Delay(100);
		}

		ErrorHandlerModel::ErrorHandlerUpdate();

	}

}
