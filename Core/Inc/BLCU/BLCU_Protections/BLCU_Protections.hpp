#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{
	void __set_up_protections(){
		ProtectionManager::_add_protection(&BLCU::programming_error, Boundary<bool, EQUALS>(false));
	 }


}
