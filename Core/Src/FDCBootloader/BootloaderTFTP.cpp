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

BTFTP::Mode BTFTP::mode = BTFTP::Mode::NONE;

BTFTP::btftp_file_t* BTFTP::file = nullptr;

//Public:
void BTFTP::on(BTFTP::Mode mode){
	BTFTP::ready = true;
	BTFTP::mode = mode;
}

void BTFTP::off(){
	BTFTP::ready = false;
	BTFTP::mode = BTFTP::Mode::NONE;;
}

void BTFTP::start(){
	const tftp_context* context = new tftp_context(&BTFTP::open, &BTFTP::close, &BTFTP::read, &BTFTP::write, &BTFTP::re);
	err_t error = tftp_init(context);

	//TODO: estaria bien comprobar antes que no esta ya ready
	//		ya sea aqui o denstro del set_up

	if (error != ERR_OK) {
		ErrorHandler("Unable to start TFTP server, error code: %lu.", error);
	}

	BTFTP::file->payload = (uint8_t*)malloc(SECTOR_SIZE_IN_BYTES);
	if (BTFTP::file->payload == nullptr) {
		ErrorHandler("BLCU could not allocate enough memory for tftp file buffer");
		return;
	}

	//TODO: Remove debug print
	printf("Servidor tftp inciado con éxito! Error code: %u\n", error);
}

//Private:

void* BTFTP::open(const char* fname, const char* mode, u8_t write){
	if (not BTFTP::ready || write != (uint8_t)BTFTP::mode) {
		return nullptr;
	}

	const char* accepted_mode = "octet";
	if (strcmp(mode, accepted_mode)) {
		return nullptr;
	}
	printf("File opened in %s mode.\n", accepted_mode);

	uint8_t version = 0x0;;

	if (not FDCB::get_version(version)){
		//TODO: WARNING: Bootloader not respondig, unable to start read/write operation!
		printf("Bootloader not respondig, unable to start read/write operation!");
		return nullptr;
	}

	if (version != FDCB_CURRENT_VERSION) {
		ErrorHandler("Mismatch in bootloader version, current version in host: 0x%X in target: 0x%X.", FDCB_CURRENT_VERSION, version);
		return nullptr;
	}



	uint32_t address = FLASH_SECTOR0_START_ADDRESS;
	BTFTP::BHandle* handle = new BTFTP::BHandle(string(fname), string(mode), write, address);
	handle->file = BTFTP::file;
	handle->current_sector = 0;
	BTFTP::file->max_pointer = SECTOR_SIZE_IN_BYTES - 1;

	if (handle->read_write == 1) {
		handle->file->pointer = 0;
	}else{
		handle->file->pointer = handle->file->max_pointer;
	}

	return handle;
}

void BTFTP::close(void* handle){
	free(handle);
	BLCU::finish_write_read_order();
}

int BTFTP::read(void* handle, void* buf, int bytes){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
	if (btftp_handle->read_write == 1) {
		return -1;
	}

	if (btftp_handle->file->pointer >= btftp_handle->file->max_pointer) {

		if (btftp_handle->current_sector > 6) {
			return 0;
		}else{
			if (not FDCB::read_memory(btftp_handle->current_sector, btftp_handle->file->payload)) {
				return -1;
			}
			btftp_handle->file->pointer = 0;
			btftp_handle->current_sector++;
		}
	}

	memcpy((uint8_t*)buf, &btftp_handle->file->payload[btftp_handle->file->pointer], 512);
	btftp_handle->file->pointer += TFTP_MAX_DATA_SIZE;

	return 512;
}

int BTFTP::write(void* handle, struct pbuf* p){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
	if (btftp_handle->read_write == 0) {
		return -1;
	}



	if (btftp_handle->file->pointer >= btftp_handle->file->max_pointer) {
		if (btftp_handle->current_sector > 6) {
			return 1;
		}else{
			if (not FDCB::write_memory(btftp_handle->current_sector, btftp_handle->file->payload)) {
				return -1;
			}
			btftp_handle->file->pointer = 0;
			btftp_handle->current_sector++;
		}
	}

	memcpy(&btftp_handle->file->payload[btftp_handle->file->pointer], (uint8_t*)p->payload, p->len);
	btftp_handle->file->pointer += TFTP_MAX_DATA_SIZE;

	if (p->len < TFTP_MAX_DATA_SIZE) {
		if (not FDCB::write_memory(btftp_handle->current_sector, btftp_handle->file->payload)) {
			return -1;
		}
		return 0;
	}

	return 1;
}

void BTFTP::re(void* handle){
	BTFTP::BHandle* btftp_handle = (BTFTP::BHandle*)handle;
	btftp_handle->file->pointer -= TFTP_MAX_DATA_SIZE;
}


//#endif
