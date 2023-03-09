 /**
  * Bootloader.hpp
  *
  *  Created on: Jan 21, 2022
  *      Author: Pablo
  */

#include "FDCBootloader/FDCBootloader.hpp"

uint8_t FDCB::fdcan = 0;
bool FDCB::ready = false;


void FDCB::set_up(FDCAN::Peripheral&  fdcan){
	optional<uint8_t> temp_fdcan = FDCAN::inscribe(fdcan);
	if (not temp_fdcan) {
		ErrorHandler("Unable to inscribe FDCAN %u", fdcan);
		return;
	}
	FDCB::fdcan = temp_fdcan.value();
	FDCB::ready = true;
}

bool FDCB::get_version(uint8_t& version){
	vector<uint8_t> data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	version = 0;

	FDCAN::transmit(FDCB::fdcan, FDCB::GET_VERSION, data, FDCAN::DLC::BYTES_64);

	if (not __wait_for_ack(FDCB::GET_VERSION, packet)) {
		return false;
	}

	if (not __wait_for_data_message(FDCB::GET_VERSION, &packet)) {
		return false;
	}
	version = packet.rx_data[0];

	if (not __wait_for_ack(FDCB::GET_VERSION, packet)) {
		version = 0;
		return false;
	}

	return true;
}

bool FDCB::read_memory(uint8_t sector, uint8_t* data){
	vector<uint8_t> tx_data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	packet.rx_data = vector<uint8_t>(64);
	uint16_t i;
	uint32_t index, counter;

	tx_data.at(0) = sector;

	FDCAN::transmit(FDCB::fdcan, FDCB::READ_MEMORY, tx_data, FDCAN::DLC::BYTES_64);
	printf("Read order send!\n");
	if (not __wait_for_ack(FDCB::READ_MEMORY, packet)) {
		return false;
	}
	printf("ACK Received!\n");
	if (not __send_ack(FDCB::READ_MEMORY)) {
		return false;
	}

	index = 0;
	counter = 0;
	for (i = 0; i < 2048; ++i) {
		if(not FDCB::__wait_for_data_message(FDCB::READ_MEMORY, &packet)) {
			return false;
		}

		memcpy(&data[index], &packet.rx_data[0], 64);
		index += 64;

		if (counter >= FDCB_BLOCK_SIZE) {
			if (not FDCB::__wait_for_ack(FDCB::READ_MEMORY, packet)) {
				return false;
			}

			FDCB::__send_ack(FDCB::READ_MEMORY);
			counter = 0;
		}
		counter++;
	}
	printf("All data received!\n");
	if (not __wait_for_ack(FDCB::READ_MEMORY, packet)) {
		return false;
	}
	printf("END!\n");
	return true;
}



bool FDCB::erase_memory(){
	vector<uint8_t> data = vector<uint8_t>(64);
	FDCAN::Packet packet = FDCAN::Packet();
	data.at(0) = 0;
	data.at(1) = 6;

	FDCAN::transmit(FDCB::fdcan, FDCB::ERASE_MEMORY, data, FDCAN::DLC::BYTES_64);

	if (not __wait_for_ack(FDCB::ERASE_MEMORY, packet)) {
		return false;
	}

	if (not __wait_for_ack(FDCB::ERASE_MEMORY, packet)) {
		return false;
	}

	return true;
}

//*******************************************************
//				Private functions
//*******************************************************

bool FDCB::__wait_for_data_message(uint8_t order, FDCAN::Packet* packet){
	if (not __wait_for_bootloader_message()) {
		return false;
	}

	if (not FDCAN::read(fdcan, packet)) {
		return false;
	}

	if (packet->identifier != order) {
		return false;
	}

	return true;
}

bool FDCB::__wait_for_ack(uint8_t order, FDCAN::Packet& packet){

	if (not __wait_for_bootloader_message()) {
		return false;
	}

	FDCAN::read(fdcan, &packet);

	if (packet.identifier != order) {
		return false;
	}else if(packet.rx_data[0] != FDCB_ACK){
		return false;
	}

	return true;
}

bool FDCB::__send_ack(uint8_t order){
	vector<uint8_t> data = vector<uint8_t>(64);
	data.at(0) = FDCB_ACK;
	return FDCAN::transmit(FDCB::fdcan, order, data, FDCAN::DLC::BYTES_64);
}

bool FDCB::__send_nack(uint8_t order){
	vector<uint8_t> data = vector<uint8_t>(64);
	data.at(0) = FDCB_NACK;
	return FDCAN::transmit(FDCB::fdcan, order, data, FDCAN::DLC::BYTES_64);
}

bool FDCB::__wait_for_bootloader_message(){
     bool exit = true;

     //TODO: ARREGLAR LOS TIMEOUTS *MUY IMPORTANTE*
//     Time::set_timeout(FDCB_TIMOUT_MS, [&](){
//    	exit = false;
//     });

     while(exit){

    	 if (FDCAN::received_test(fdcan)) {
			return true;
    	 }
     }

     //TODO:: Warning timeout
     return false;
}

void FDCB::__copy_data_from_packet(FDCAN::Packet& packet, uint8_t* data){
	//memcpy(data, &packet.rx_data[0], 64);

	uint8_t i;
	for (i = 0; i < 64; ++i) {
		data[i] = packet.rx_data.at(i);
	}
}













 bool FDCB::__write_memory_order(uint32_t address, vector<uint8_t> data){
//     vector<uint8_t> msg_content = {};
//
//     FDCB::__addr_to_byte_vector(msg_content, address);
//
//     msg_content.push_back(data.size() == 256 ? 255 : data.size());
//
//     if (not FDCAN::transmit(fdcan, FDCB::BootLoaderOrders::WRITE_MEMORY, msg_content, FDCAN::DLC::BYTES_64))
//         return false;
//
//
//     optional<FDCAN::Packet> res = FDCB::__wait_for_bootloader_message(FDCB::BootLoaderOrders::ACK);
//     if (!res.has_value())
//         return false;
//
//
//     while(data.size() > 0){
//
//         if (data.size() > 63) {
//             vector<uint8_t> sub_data(data.begin(), data.begin() + 63);
//             if (not FDCAN::transmit(FDCB::fdcan, FDCB::BootLoaderOrders::WRITE_MEMORY, sub_data, FDCAN::DLC::BYTES_64))
//                 return false;
//
//
//             data = {data.begin() + 64, data.end()};
//         }else{
//        	 //TODO: revisar esto
//            // vector<uint8_t> sub_data(data.begin(), data.begin() + data.size() - 1);
//             if (not FDCAN::transmit(FDCB::fdcan, FDCB::BootLoaderOrders::WRITE_MEMORY, data, FDCAN::DLC::BYTES_64))
//                 return false;
//
//             break;
//         }
//     }
//
//     res = FDCB::__wait_for_bootloader_message(FDCB::BootLoaderOrders::ACK);
//     if (!res.has_value()) {
//         return false;
//     }
//
//     return true;
 }

 bool FDCB::__wait_for_bootloader_command_response(vector<uint8_t>& data){
//     optional<FDCAN::Packet> msg =  FDCB::__wait_for_bootloader_message(FDCB::BootLoaderOrders::ACK);
//     if (!msg.has_value())
//         return false;
//
//     msg = FDCB::__wait_for_bootloader_message();
//     if (!msg.has_value())
//         return false;
//
//     while(msg.value().rx_data[0] != FDCB::BootLoaderOrders::NACK){
//         for(uint16_t i = 0; i < msg.value().data_length; i++)
//             data.push_back(msg.value().rx_data[i]);
//
//         msg = FDCB::__wait_for_bootloader_message();
//         if (!msg.has_value())
//             return false;
//     }
//
//     return true;
 }


 void FDCB::__addr_to_byte_vector(vector<uint8_t>& v, uint32_t addr){
     v.push_back( addr >> 24 );
     v.push_back( addr >> 16 );
     v.push_back( addr >>  8 );
     v.push_back( addr       );
 }


