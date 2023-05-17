#include "BLCU/BLCU.hpp"


void BLCU::__set_up_orders(){

    BLCU::orders_data = {
			BLCU::Target::NOTARGET,
			0
	};

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

	HeapOrder get_version_order = {
			703,
			BLCU::get_version,
			&BLCU::orders_data.target,
			&BLCU::orders_data.version,
	};

	HeapOrder reset_all_order = {
			704,
			BLCU::reset_all,
			&BLCU::orders_data.target,
	};

	HeapOrder ack = {
			4,
	};
}
