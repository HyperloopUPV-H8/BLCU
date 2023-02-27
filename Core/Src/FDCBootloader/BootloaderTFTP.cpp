/*
 * BootloaderTFTP.cpp
 *
 *  Created on: 21 feb. 2022
 *      Author: Pablo
 */


#include "FDCBootloader/BootloaderTFTP.hpp"

//#ifdef HAL_ETH_MODULE_ENABLED
//Variables:
bool BTFTP::ready = false;

////Public:
//void BTFTP::on(){
//	BTFTP::current_state = BTFTP::State::ON;
//}
//
//void BTFTP::off(){
//	BTFTP::current_state = BTFTP::State::OFF;
//}
//
//BTFTP::State BTFTP::get_state(){
//	return BTFTP::current_state;
//}

void BTFTP::start(){
	const tftp_context* context = new tftp_context(&BTFTP::open, &BTFTP::close, &BTFTP::read, &BTFTP::write);
	err_t error = tftp_init(context);

	if (error != ERR_OK) {
		ErrorHandler("Unable to start TFTP server, error code: %lu.", error);
	}

	//TODO: Remove debug print
	printf("Servidor tftp inciado con éxito! Error code: %u\n", error);
}

//Private:

void* BTFTP::open(const char* fname, const char* mode, u8_t write){
//	if (not ready) {
//		return nullptr;
//	}

	const char* accepted_mode = "octet";
//	if (not strcmp(mode, accepted_mode)) {
//		return nullptr;
//	}

	BTFTP::BHandle* handle = new BTFTP::BHandle(string(fname), string(mode), write, 0x08000000);

	return handle;
}

void BTFTP::close(void* handle){
	free(handle);

}

int BTFTP::read(void* handle, void* buf, int bytes){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
//
//	uint16_t size = 0;
//	if (btftp_handle->max_addr - btftp_handle->address > 512) {
//		size = 512 / 8;
//	}else{
//		size = (btftp_handle->max_addr - btftp_handle->address) / 8;
//	}
//
//	Flash::read(btftp_handle->address, (uint32_t*)buf, size);
//
//	btftp_handle->address += 512;
//	if (btftp_handle->address >  btftp_handle->max_addr) {
//		return 0;
//	}else{
//		return 512;
//	}

	Flash::read(btftp_handle->address, (uint32_t*)buf, 64);

	return 511;
}

void printf_address_debug(int add){
//	//TODO: Remove debug print
//	std::stringstream stream;
//	stream << std::hex << add;
//	std::string result( stream.str() );
//	printf("Solicitud de escritura en 0x%s! \n", result.c_str());
}

int BTFTP::write(void* handle, struct pbuf* p){
//	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
//	if (btftp_handle->read_write == 0) {
//		return -1;
//	}
//
//	printf_address_debug(btftp_handle->address);
//
//	//TODO:Revisar que puede estar mal la suma, quizas falta dividir por el sizeof()
//	//vector<uint8_t> data((uint8_t*)p->payload,((uint8_t*)p->payload) + p->len);
//
//	//FDCB::write_memory(btftp_handle->address, data); TODO: descomentar esto
//
//	//btftp_handle->address += p->len;
//
//	return 1;
}


//#endif
