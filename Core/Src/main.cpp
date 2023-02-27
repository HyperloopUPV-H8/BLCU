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

//	FDCB::set_up(FDCAN::fdcan1);
	STLIB::start(Board, "192.168.1.4", "255.255.0.0", "192.168.1.1");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	BTFTP::start();
	//BTFTP::on();
	//udp_packet_test udp = udp_packet_test();


	while (1) {
		//print_freq();
		//udp.send();
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
