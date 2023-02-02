#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "PinModel/Pin.hpp"
#include "Runes/Runes.hpp"
#include "FDCBootloader/FDCBootloader.hpp"
extern struct netif gnetif;

int main(void)
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
		}
		string pin = "PF0";
		printf("Pint %s \n", PA0.to_string().c_str());

		ErrorHandlerModel::ErrorHandlerUpdate();

		HAL_Delay(100);
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
