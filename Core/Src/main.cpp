#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "PinModel/Pin.hpp"
#include "Runes/Runes.hpp"
#include "FDCBootloader/FDCBootloader.hpp"
#include "BLCU/BLCU.hpp"
#include "Examples/examples_includes.hpp"

extern struct netif gnetif;

int main(void)
{

	// BLCU::set_up();
	// BLCU::start();
	get_order_example();
	optional<uint8_t> fdcan_temp = FDCAN::inscribe(FDCAN::fdcan1);
	DigitalOutput LED_OPERATIONAL = DigitalOutput(PG8);
    DigitalOutput LED_FAULT = DigitalOutput(PG7);
    DigitalOutput LED_CAN = DigitalOutput(PG6);
    DigitalOutput LED_FLASH = DigitalOutput(PG5);
    DigitalOutput LED_SLEEP = DigitalOutput(PG4);

	uint8_t fdcan = 0;
	if (not fdcan_temp.has_value())
	{
		ErrorHandler("Unable to register fdcan");
	}

	STLIB::start();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	LED_OPERATIONAL.turn_on();

	vector<uint8_t> empty_data = vector<uint8_t>(64, 0);
	empty_data[0] = 0x08;
	empty_data[1] = 0x0A;
	empty_data[2] = 0x00;
	empty_data[3] = 0x0;
	empty_data[4] = 8;
	printf("Direction 0x%X 0x%X 0x%X 0x%X %u \n", empty_data[0], empty_data[1], empty_data[2], empty_data[3], empty_data[4]);
	LED_CAN.turn_on();
	FDCAN::transmit(fdcan, 0x31, empty_data, FDCAN::DLC::BYTES_64);
	HAL_Delay(10);
	LED_CAN.turn_off();
	

	FDCAN::Packet ack = FDCAN::Packet();
	FDCAN::Packet data = FDCAN::Packet();

	while(not FDCAN::received_test(fdcan)){
		if (ErrorHandlerModel::error_triggered != 0) {
			break;
		}
		LED_FLASH.toggle();
		HAL_Delay(50);
	}
	LED_SLEEP.turn_off();

	FDCAN::read(fdcan, &ack);
	if (ack.rx_data[0] == 0x1F) {
		printf("\t\t\t       NACK \n");
	}else{
		printf("\t\t\t       ACK \n");
	}

	data.rx_data = {0xAA, 0xBB, 0xCC, 0xDD, 0x00, 0x00, 0x00 ,0x00};
	FDCAN::transmit(fdcan, 0x31, data.rx_data, FDCAN::DLC::BYTES_8);

	while(not FDCAN::received_test(fdcan)){
		if (ErrorHandlerModel::error_triggered != 0) {
			break;
		}
		LED_SLEEP.toggle();
		HAL_Delay(50);
	}

	FDCAN::read(fdcan, &ack);
	if (ack.rx_data[0] == 0x1F) {
		printf("\t\t\t       NACK \n");
	}else{
		printf("\t\t\t       ACK \n");
	}

	uint32_t counter = 0;
	while (1) {
		// BLCU::update();
		printf("Counter = %06lu | ID = 0x%X | ACK = 0x%X |", counter, (uint8_t)ack.identifier, (uint8_t)ack.rx_data[0]);
		counter++;
//		uint32_t aux = 1;
//		for(auto& d: data.rx_data){
//			printf("Byte%lu = 0x%X | ", aux++, d);
//		}
		printf("FDCAN RX queue = %03lu", (uint32_t)FDCAN::available_fdcans.at(FDCAN::fdcan1)->rx_queue.size());
		printf("\r");

		if (ErrorHandlerModel::error_triggered != 0) {
			LED_FAULT.turn_on();
			LED_OPERATIONAL.turn_off();
		}
		ErrorHandlerModel::ErrorHandlerUpdate();
	}
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	ErrorHandler("HAL error handler triggered");
  /* User can add his own implementation to report the HAL error return state */
  //__disable_irq();
  //while (1){}
  /* USER CODE END Error_Handler_Debug */
}
