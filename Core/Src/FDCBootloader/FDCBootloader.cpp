/*
 * Bootloader.hpp
 *
 *  Created on: Jan 21, 2022
 *      Author: Pablo
 */

#include "FDCBootloader/FDCBootloader.hpp"

uint8_t FDCB::fdcan = 0;

bool FDCB::ready = false;

void FDCB::set_up(uint8_t fdcan){
	FDCB::fdcan = fdcan;

	FDCB::ready = true;
}

bool FDCB::get(vector<uint8_t> &res){
	if (!FDCAN::transmit(fdcan, FDCB::Orders::GET, {}, FDCAN::DLC::BYTES_64))
		return false;


	if(!FDCB::__wait_for_bootloader_command_response(res))
		return false;


	return true;
}

bool FDCB::get_version(uint32_t& res){
	if (!FDCAN::transmit(fdcan, FDCB::Orders::GET_VERSION, {}, FDCAN::DLC::BYTES_64))
			return false;

	vector<uint8_t> v = {};
	if(!FDCB::__wait_for_bootloader_command_response(v))
		return false;

	res = v[0];

	return true;
}


bool FDCB::get_id(uint32_t& res){
	if (!FDCAN::transmit(fdcan, FDCB::Orders::GET_ID, {}, FDCAN::DLC::BYTES_64))
		return false;

	vector<uint8_t> v = {};
	if(!FDCB::__wait_for_bootloader_command_response(v))
		return false;

	res = v[0] + (v[1] << 8);

	return true;
}

bool FDCB::read_memory(vector<uint8_t>& res, uint32_t address, uint32_t byte_count){
	res = {};

	while(byte_count > 0){

		vector<uint8_t> msg_content = {};
		FDCB::__addr_to_byte_vector(msg_content, address);
		msg_content.push_back(byte_count - 1);

		if (!FDCAN::transmit(fdcan, FDCB::Orders::READ_MEMORY, msg_content, FDCAN::DLC::BYTES_64))
			return false;

		vector<uint8_t> v = {};
		if(!FDCB::__wait_for_bootloader_command_response(v))
			return false;

		res.insert(res.end(), v.begin(), v.end());

		byte_count -= 256;
		address += 256;
	}

	return true;
}

bool FDCB::exit_bootloader(uint32_t& address){
	vector<uint8_t> v = {};
	FDCB::__addr_to_byte_vector(v, address);

	if (!FDCAN::transmit(fdcan, FDCB::Orders::GO, v, FDCAN::DLC::BYTES_64))
		return false;

	optional<FDCAN::Packet> p = FDCB::__wait_for_bootloader_message(FDCB::Orders::ACK);

	if (!p.has_value()) {
		return false;
	}

	return true;

}

bool FDCB::write_memory(uint32_t address, vector<uint8_t>& data){

	while(data.size() > 0){
		if (data.size() > 255) {
			vector<uint8_t> sub_data(data.begin(), data.begin() + 255);
			if(!FDCB::__write_memory_order(address, sub_data))
				return false;

			data = {data.begin() + 256, data.end()};

		}else{
			vector<uint8_t> sub_data(data.begin(), data.begin() + data.size() - 1);
			if(!FDCB::__write_memory_order(address, sub_data))
				return false;

			break;
		}
	}

	return true;
}

bool FDCB::erase_memory(){
	array<uint8_t, 2> p = {0xff, 0xff};
	if (!FDCAN::transmit(fdcan, FDCB::Orders::ERASE_MEMORY, p, FDCAN::DLC::BYTES_64))
		return false;

	vector<uint8_t> res = {};
	if(!FDCB::__wait_for_bootloader_command_response(res))
		return false;

	return true;
}

bool FDCB::write_protect(){
	//Buen intento crack, te falte calle
	return false;
}

bool FDCB::write_unprotect(){
	//Buen intento crack, te falte calle
	return false;

}

bool FDCB::readout_protect(){
	//Buen intento crack, te falte calle
	return false;
}

bool FDCB::readout_unprotect(){
	//Buen intento crack, te falte calle
	return false;
}

//*******************************************************
//				Private functions
//*******************************************************

bool FDCB::__write_memory_order(uint32_t address, vector<uint8_t> data){
	vector<uint8_t> msg_content = {};

	FDCB::__addr_to_byte_vector(msg_content, address);

	msg_content.push_back(data.size() == 256 ? 255 : data.size());

	if (not FDCAN::transmit(fdcan, FDCB::Orders::WRITE_MEMORY, msg_content, FDCAN::DLC::BYTES_64))
		return false;


	optional<FDCAN::Packet> res = FDCB::__wait_for_bootloader_message(FDCB::Orders::ACK);
	if (!res.has_value())
		return false;


	while(data.size() > 0){

		if (data.size() > 63) {
			vector<uint8_t> sub_data(data.begin(), data.begin() + 63);
			if (not FDCAN::transmit(FDCB::fdcan, FDCB::Orders::WRITE_MEMORY, sub_data, FDCAN::DLC::BYTES_64))
				return false;


			data = {data.begin() + 64, data.end()};
		}else{
			vector<uint8_t> sub_data(data.begin(), data.begin() + data.size() - 1);
			if (not FDCAN::transmit(FDCB::fdcan, FDCB::Orders::WRITE_MEMORY, sub_data, FDCAN::DLC::BYTES_64))
				return false;

			break;
		}
	}

	res = FDCB::__wait_for_bootloader_message(FDCB::Orders::ACK);
	if (!res.has_value()) {
		return false;
	}

	return true;
}

bool FDCB::__wait_for_bootloader_command_response(vector<uint8_t>& data){
	optional<FDCAN::Packet> msg =  FDCB::__wait_for_bootloader_message(FDCB::Orders::ACK);
	if (!msg.has_value())
		return false;

	msg = FDCB::__wait_for_bootloader_message();
	if (!msg.has_value())
		return false;

	while(msg.value().rx_data[0] != FDCB::Orders::NACK){
		for(uint16_t i = 0; i < msg.value().data_length; i++)
			data.push_back(msg.value().rx_data[i]);

		msg = FDCB::__wait_for_bootloader_message();
		if (!msg.has_value())
			return false;
	}

	return true;
}

optional<FDCAN::Packet> FDCB::__wait_for_bootloader_message(uint8_t match_first_byte){
	bool exit = false;

	FDCAN::Packet packet = {};

	while(exit){
		Time::set_timeout(TIMOUT_MS, [&](){exit = true;});

		FDCAN::wait_and_read(fdcan, &packet);

		if ((match_first_byte == NONE) or (packet.rx_data[0] == match_first_byte))
			return packet;
	}

	//TODO: WARNING ErrorHandler("Timeout time exceeded waiting the next FDCAN message.", "");
	return nullopt;
}

void FDCB::__addr_to_byte_vector(vector<uint8_t>& v, uint32_t addr){
    v.push_back( addr >> 24 );
    v.push_back( addr >> 16 );
    v.push_back( addr >>  8 );
    v.push_back( addr       );
}


