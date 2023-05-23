#pragma once
#include "stdint.h"
#include "Target.hpp"

namespace BLCU{
	typedef struct {
		BLCU::Target target;
		uint16_t version;

		void clean_data(){
			target = BLCU::Target::NOTARGET;
			version = 0;
		}

	}orders_data_t;

}
