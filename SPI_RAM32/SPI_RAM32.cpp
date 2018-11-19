#include "SPI_RAM32.h"

uint8_t* SPI_RAM32::pointer = (uint8_t*)1;

SPI_RAM32::SPI_RAM32(){};

void SPI_RAM32::init(){
	SPI.begin();
	pinMode(SPI_RAM32_CS, OUTPUT);
}

void SPI_RAM32::SPI_begin(){
	SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
	digitalWrite(SPI_RAM32_CS, LOW);
}

void SPI_RAM32::SPI_end(){
	digitalWrite(SPI_RAM32_CS, HIGH);
	SPI.endTransaction();
}

void SPI_RAM32::selectMode(uint8_t mode){
	/*if(mode != MODE_BYTE || mode != MODE_PAGE || mode != MODE_SEQ)
		return;*/
	
	SPI_begin();
	SPI.transfer(WRITE_STAT_REG);
	SPI.transfer(mode);
	SPI_end();
}

void SPI_RAM32::write(void *address, uint8_t data){
	selectMode(MODE_BYTE);
	
	SPI_begin();
	SPI.transfer(SPI_RAM32_WRITE);
	SPI.transfer16((uint16_t)address);
	SPI.transfer(data);
	SPI_end();
}

uint8_t SPI_RAM32::read(void *address){
	selectMode(MODE_BYTE);
	
	SPI_begin();
	SPI.transfer(SPI_RAM32_READ);
	SPI.transfer16((uint16_t)address);
	uint8_t data = SPI.transfer(0);
	SPI_end();
	
	return data;
}

void SPI_RAM32::writeLoop(void* address, uint8_t data, uint16_t length){
	selectMode(MODE_SEQ);
	
	SPI_begin();
	SPI.transfer(SPI_RAM32_WRITE);
	SPI.transfer16((uint16_t)address);	

	for(uint16_t i=0; i<length; i++){
		SPI.transfer(data);
	}
	SPI_end();
}

void SPI_RAM32::writeArray(void* address, void* data, uint16_t length){
	selectMode(MODE_SEQ);
	
	SPI_begin();
	SPI.transfer(SPI_RAM32_WRITE);
	SPI.transfer16((uint16_t)address);	
	uint8_t *data_array = (uint8_t*)data;

	for(uint16_t i=0; i<length; i++){
		SPI.transfer(data_array[i]);
	}
	SPI_end();
}

void SPI_RAM32::readArray(void* address, void* data, uint16_t length){
	selectMode(MODE_SEQ);
	
	SPI_begin();
	SPI.transfer(SPI_RAM32_READ);
	SPI.transfer16((uint16_t)address);	
	uint8_t *data_array = (uint8_t*)data;

	for(uint16_t i=0; i<length; i++){
		data_array[i] = SPI.transfer(0);
	}
	SPI_end();
}

void SPI_RAM32::write16(void* address, uint16_t data){
	writeArray(address, &data, 2);
}

void SPI_RAM32::write32(void* address, uint32_t data){
	writeArray(address, &data, 4);
}

uint16_t SPI_RAM32::read16(void* address){
	uint16_t var;
	readArray(address, &var, 2);
	return var;
}

uint32_t SPI_RAM32::read32(void* address){
	uint32_t var;
	readArray(address, &var, 4);
	return var;
}

void* SPI_RAM32::malloc(uint16_t size){
	uint8_t* temp_pointer = pointer;
	writeLoop(pointer, 0, size);
	pointer +=size;
	return temp_pointer;
}


