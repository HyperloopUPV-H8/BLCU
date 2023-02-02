/*
 * adc_example.hpp
 *
 *  Created on: 30 Jan. 2022
 *      Author: Alejandro
 */
#pragma once

#include "ST-LIB.hpp"

int protection_manager_example(void)
{
	#define BOARD_ID 54
	ProtectionManager::set_id(BOARD_ID);

	double variable = 5.3;
	ProtectionManager_add_protection(&variable, OUT_OF_RANGE, 1, 20, NOT_EQUALS, 5);

	variable = 8;
	ProtectionManager::check_protections();

	variable = 5;
	ProtectionManager::check_protections();

	variable = 20;
	ProtectionManager::check_protections();

	variable = 21;
	ProtectionManager::check_protections();
}
