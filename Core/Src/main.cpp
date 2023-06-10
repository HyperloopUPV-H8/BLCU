#include "main.h"
#include "lwip.h"

#include "BLCU/BLCU.hpp"
#include "Runes/Runes.hpp"

//TODO: Cosas claras que falta es pasar las ordenes estas a el archivo correspondiente y comprobar que no mueren

HeapOrder ack = {
		3,
};


HeapOrder nack = {
		4,
};

HeapOrder get_version_order = {
		703,
		BLCU::get_version,
		&BLCU::orders_data.target,
		&BLCU::orders_data.version,
};


int main(void)
{
	HeapOrder write_program_order = {
			700,
			BLCU::write_program,
			&BLCU::orders_data.target,
	};

	HeapOrder read_program_order = {
			701,
			BLCU::read_program,
			&BLCU::orders_data.target,
	};

	HeapOrder erase_program_order = {
			702,
			BLCU::erase_program,
			&BLCU::orders_data.target,
	};

	HeapOrder reset_all_order = {
			704,
			BLCU::reset_all,
			&BLCU::orders_data.target,
	};

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
