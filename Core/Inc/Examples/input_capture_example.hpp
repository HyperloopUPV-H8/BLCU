/*
 * input_capture_example.hpp
 *
 *  Created on: 31 Jan. 2022
 *      Author: Pablo
 */
#pragma once

#include "ST-LIB.hpp"
#include "DMA/DMA.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

void input_capture_example(void){
	UART::set_up_printf(UART::uart2);

	optional<uint8_t> input = InputCapture::inscribe(PF0);
	optional<uint8_t> pwm = PWMservice::inscribe(PB15);

	if (not input.has_value()) {
		ErrorHandler("No se ha podido registrar el input", 0);
	}

	if (not pwm.has_value()) {
		ErrorHandler("No se ha podido registrar el pwm", 0);
	}

	Pin::start();
	TimerPeripheral::start();
	UART::start();

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	uint32_t freq = 0;
	uint8_t duty = 0;
	InputCapture::turn_on(input.value());

	PWMservice::turn_on(pwm.value());

	PWMservice::set_duty_cycle(pwm.value(), 30);

	while (1) {

		freq = InputCapture::read_frequency(input.value()).value();
		duty = InputCapture::read_duty_cycle(input.value()).value();

		printf("Freq = %lu; Duty = %u | \r", freq, duty);
		HAL_Delay(50);

		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}
