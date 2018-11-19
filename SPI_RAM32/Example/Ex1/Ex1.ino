#include <SPI_RAM32.h>


void setup() {
  Serial.begin(9600);
  SPI_RAM32::init();


  byte *v = (byte*)SPI_RAM32::malloc(sizeof(byte));
  SPI_RAM32::write(v, 255);

  Serial.print("Adres =>");
  Serial.print((word)v);
  Serial.print("   Deger =>");
  Serial.println(SPI_RAM32::read(v));

  word *a = (word*)SPI_RAM32::malloc(sizeof(word));
  SPI_RAM32::write16(a, 65535);

  Serial.print("Adres =>");
  Serial.print((word)a);
  Serial.print("   Deger =>");
  Serial.println(SPI_RAM32::read16(a));

  unsigned long *b = (unsigned long*)SPI_RAM32::malloc(sizeof(unsigned long));
  SPI_RAM32::write32(b, 123456789);

  Serial.print("Adres =>");
  Serial.print((word)b);
  Serial.print("   Deger =>");
  Serial.println(SPI_RAM32::read32(b));

  for(int i=0; i<1024; i+=2){
    SPI_RAM32::write16((void*)i, i);
  }

  for(int i=0; i<1024; i+=2){
    Serial.print(i);
    Serial.print(" => ");
    word data = SPI_RAM32::read16((void*)i);
    
    if(i != data)
      Serial.print(" HATA ");
      
    Serial.println(data);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}