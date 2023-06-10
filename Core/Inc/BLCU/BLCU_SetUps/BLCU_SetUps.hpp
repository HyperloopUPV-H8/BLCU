#pragma once

#include "BLCU/BLCU_Definition/BLCU_Definition.hpp"

namespace BLCU{

	void __set_up_peripherals(){
		BLCU::__set_up_fdcan();
		BLCU::__set_up_ethernet();
		BLCU::__set_up_resets();
		BLCU::__set_up_boots();
		BLCU::__set_up_leds();
	}

   void __set_up_fdcan(){
	   BLCU::fdcan = FDCAN::inscribe(FDCAN::fdcan1);
   }

   void __set_up_ethernet(){
		BLCU::ip = BLCU_IP;
		BLCU::mask = BLCU_MASK;
		BLCU::gateway = BLCU_GATEWAY;
		BLCU::port = BLCU_PORT;
   }

   void __set_up_resets(){
		BLCU::resets[VCU] = DigitalOutput(PA12);
		BLCU::resets[OBCCU] = DigitalOutput(PG3);
		BLCU::resets[BMSA] = DigitalOutput(PD11);
		BLCU::resets[LCUM] = DigitalOutput(PD9);
		BLCU::resets[LCUS] = DigitalOutput(PB12);
		BLCU::resets[PCU] = DigitalOutput(PG1);
   }

   void __set_up_boots(){
		BLCU::boots[VCU] = DigitalOutput(PA11);
		BLCU::boots[OBCCU] = DigitalOutput(PG2);
		BLCU::boots[BMSA] = DigitalOutput(PD10);
		BLCU::boots[LCUM] = DigitalOutput(PD8);
		BLCU::boots[LCUS] = DigitalOutput(PE15);
		BLCU::boots[PCU] = DigitalOutput(PE7);
   }

   void __set_up_leds(){
		BLCU::LED_OPERATIONAL = DigitalOutput(PG8);
		BLCU::LED_FAULT = DigitalOutput(PG7);
		BLCU::LED_CAN = DigitalOutput(PG6);
		BLCU::LED_FLASH = DigitalOutput(PG5);
		BLCU::LED_SLEEP = DigitalOutput(PG4);
   }

}
