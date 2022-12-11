#include <Arduino.h>
#include <SPI.h>

struct Generator
{
  uint8_t latch_pin;

  Generator(uint8_t u_latch)
  {
    SPI.setDataMode(SPI_MODE2); //spi init
    SPI.begin();
    
    latch_pin = u_latch; //latch pin init
    pinMode(latch_pin, OUTPUT);
    digitalWrite(latch_pin, HIGH);
  }

  void write_control(bool reset, bool form) //reset -> enable/disable output
  {
    uint16_t cfg = 0;
    cfg |= 1 << 13; //enable to write in freq registers in two words
    cfg |= reset ? 0 : (1 << 8); //enable/disable output
    if(form)
      cfg |= 1 << 1; //uncomment to get triangle signal
    write2gen(cfg);
  }

  void write_freq(uint64_t out) //set freq to freq register
  {
    uint64_t freq = out * 1073741824 / 100000000;

    uint16_t lsb = 0x4000;
    lsb |= (uint16_t)(freq & 0x3FFF);

    uint16_t msb = 0x4000;
    msb |= (uint16_t)((freq & 0xFFFC000) >> 14);
    
    write2gen(lsb);
    write2gen(msb);
  }

  void write2gen(uint16_t data) //send cfg word to generator
  {
    digitalWrite(latch_pin, LOW);
    SPI.transfer(highByte(data));
    SPI.transfer(lowByte(data));
    digitalWrite(latch_pin, HIGH);
  }
};
