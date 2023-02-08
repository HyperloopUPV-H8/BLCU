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

	BLCU::set_up();
	BLCU::start();


	while (1) {
		BLCU::update();
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
