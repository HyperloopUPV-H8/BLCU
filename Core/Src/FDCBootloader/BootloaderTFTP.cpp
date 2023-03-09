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
	const tftp_context* context = new tftp_context(&BTFTP::open, &BTFTP::close, &BTFTP::read, &BTFTP::write, &BTFTP::re);
	err_t error = tftp_init(context);

	//TODO: estaria bien comprobar antes que no esta ya ready
	//		ya sea aqui o denstro del set_up


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
	printf("Modo seleccionado: %s \ %s\n", mode, accepted_mode);
	if (strcmp(mode, accepted_mode)) {
		return nullptr;
	}

	uint32_t address = FLASH_SECTOR0_START_ADDRESS;
	BTFTP::BHandle* handle = new BTFTP::BHandle(string(fname), string(mode), write, address);

	return handle;
}

void BTFTP::close(void* handle){
	printf("Conexion closed, handler erased\n");
	free(handle);

}

int BTFTP::read(void* handle, void* buf, int bytes){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;

	uint16_t size = 0;
	if ((btftp_handle->max_addr - btftp_handle->address) > TFTP_MAX_DATA_SIZE) {
		size = TFTP_MAX_DATA_SIZE;
	}else{
		size = (btftp_handle->max_addr - btftp_handle->address);
	}

	vector<uint8_t> vec = vector<uint8_t>();
	//if (not FDCB::read_memory(vec, btftp_handle->address, 512)) {
	//	return -1;
	//}

	memcpy(buf, vec.data(), size);

 	btftp_handle->address += TFTP_MAX_DATA_SIZE;
	if (btftp_handle->address >  btftp_handle->max_addr) {
		return 511;
	}else{
		return TFTP_MAX_DATA_SIZE;
	}
}

void printf_address_debug(int add){
	//TODO: Remove debug print
	std::stringstream stream;
	stream << std::hex << add;
	std::string result( stream.str() );
	printf("Solicitud de escritura en 0x%s! \n", result.c_str());
}

int BTFTP::write(void* handle, struct pbuf* p){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
	if (btftp_handle->read_write == 0) {
		return -1;
	}

	printf_address_debug(btftp_handle->address);
	printf("Lenth = %d\n", p->len);

	vector<uint8_t> data = vector<uint8_t>((uint8_t*)p->payload, ((uint8_t*)p->payload) + p->len);
	//if (not FDCB::write_memory(btftp_handle->address, data)) {
	//	return -1;
	//}

//	if (!Flash::write((uint32_t*)p->payload, btftp_handle->address, 128)) {
//		return -1;
//	}
	btftp_handle->address += p->len;

	//TODO:Revisar que puede estar mal la suma, quizas falta dividir por el sizeof()
	//vector<uint8_t> data((uint8_t*)p->payload,((uint8_t*)p->payload) + p->len);

	//FDCB::write_memory(btftp_handle->address, data); TODO: descomentar esto

	return 1;
}

void BTFTP::re(void* handle){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
	btftp_handle->address -= TFTP_MAX_DATA_SIZE;
}


//#endif
