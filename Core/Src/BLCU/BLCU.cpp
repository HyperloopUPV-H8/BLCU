/**
 * BLCU.cpp
 *
 *  Created on: Feb 3, 2023
 *      Author: Pablo
 */

//#include "BLCU/BLCU.hpp"
#include "Packets/Order.hpp"
#include "BLCU/Utilities/orders_data.hpp"

namespace BLCU{
	extern void write_program();
	extern void read_program();
	extern void erase_program();
	extern void get_version();
	extern void reset_all();
	extern orders_data_t orders_data;
}

