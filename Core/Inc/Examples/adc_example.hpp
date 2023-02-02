/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"

int adc_example(void)
{
	optional<uint8_t> adc = ADC::inscribe(PF11);

	if (not adc.has_value()) {
		ErrorHandler("No se ha podido registrar el adc");
	}

	STLIB::start(Nucleo, "192.168.1.4", "255.255.0.0", "192.168.1.1", UART::uart2);
	printf("\n\n\n\n\n\n\n\n\n\n");

	ADC::turn_on(adc.value());

	while (1) {
		float value = ADC::get_value(adc.value()).value();
		printf("Value %f | \r", value);
		HAL_Delay(50);

		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}
