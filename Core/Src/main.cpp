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
	//optional<uint8_t> fdcan =  FDCAN::inscribe(FDCAN::fdcan1);
	DigitalOutput LED_OPERATIONAL = DigitalOutput(PG8);
//
//	if (not fdcan.has_value()) {
//		ErrorHandler("Unable to inscribe pin");
//	}
//
//	BLCU blcu = BLCU(fdcan.value());
//	blcu.add_boots();
//	blcu.add_resets();

	STLIB::start(Board);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	LED_OPERATIONAL.turn_on();

//	blcu.send_to_bootmode(BLCU::Master);

//	uint32_t id = 69;
//
//	bool res = blcu.get_board_id(id);
//	printf("Ger borad %u | ", res);
//
//    bool res2 = blcu.exit_bootmode();
//	printf("Ger exit %u | ", res2);
//
//
//	printf("Id = %lu |  \n", id);
	while (1) {

		//ErrorHandlerModel::ErrorHandlerUpdate();
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
