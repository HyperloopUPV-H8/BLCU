#include "main.h"
#include "lwip.h"

#include "BLCU/BLCU.hpp"
#include "Runes/Runes.hpp"

int main(void)
{
	BLCU::set_up();
	BLCU::start();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("BLCU iniciada!\n");

	while (1) {
		BLCU::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
