#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "PinModel/Pin.hpp"
#include "Runes/Runes.hpp"
#include "FDCBootloader/FDCBootloader.hpp"
#include "FDCBootloader/BootloaderTFTP.hpp"
#include "BLCU/BLCU.hpp"
#include "Examples/examples_includes.hpp"
#include "BLCU/Utilities/utilities.hpp"

extern struct netif gnetif;


int main(void)
{

	FDCAN::inscribe(FDCAN::fdcan1);
	DigitalOutput led_op = DigitalOutput(PG8);
	uint8_t version;
	STLIB::start(Board, "192.168.1.4", "255.255.0.0", "192.168.1.1");
	//BTFTP::start();
   	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	led_op.turn_on();
	FDCB::get_version(version);
	printf("Version: 0x%X\n\n", version);


	uint8_t data[131072];
	int i;
	uint8_t v = 0xAA;
	for (i = 0; i < 131072; ++i) {
		data[i] = v++;
	}


	if (not FDCB::write_memory(0, data)) {
		printf("Error al escribir :(\n");
	}else{
		printf("EXITO!");
	}






//	int i ;
//	for (i = 0; i < 131072; ++i) {
//		data[i] = 0;
//	}
//
//	if (FDCB::read_memory(0, data)) {
//		printf("Read!\nData: ");
//	} else{
//		printf("ERROR!\nData: ");
//	}
//
//
//	for (int i = 0; i < 16; ++i) {
//		printf("0x%X | ", data[i]);
//	}
//	printf("\nData 2: ");
//	for (int i = 16; i < 32; ++i) {
//		printf("0x%X | ", data[i]);
//	}
//	printf("\nData 3: ");
//	for (int i = 131072 - 16; i < 131072; ++i) {
//		printf("0x%X | ", data[i]);
//	}

	while (1) {

		STLIB::update();

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
