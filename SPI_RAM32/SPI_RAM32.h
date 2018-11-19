#ifndef SPI_RAM32_h
#define SPI_RAM32_h
#include <arduino.h>
#include <SPI.h>

#define SPI_RAM32_READ 0x03
#define SPI_RAM32_WRITE 0x02

#define READ_STAT_REG 0x05
#define WRITE_STAT_REG 0x01

#define MODE_BYTE 0x00
#define MODE_SEQ 0x40
#define MODE_PAGE 0x80

#define SPI_RAM32_CS A1

class SPI_RAM32{
		
		public:
		SPI_RAM32();
		
		static void init();
		
		static void SPI_begin();
		static void SPI_end();
		static void selectMode(uint8_t);
		
		static uint8_t read(void*);
		static uint16_t read16(void*);
		static uint32_t read32(void*);
		
		static void write(void*, uint8_t);
		static void write16(void*, uint16_t);
		static void write32(void*, uint32_t);
		
		static void writeArray(void*, void*, uint16_t);
		static void writeLoop(void*, uint8_t, uint16_t);
		static void readArray(void*, void*, uint16_t);
		
		static void* malloc(uint16_t);
		static uint8_t* pointer;
};
#endif