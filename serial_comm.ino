#include <gen_lib.h>


//data -> 11 pin, clk -> 13 pin, FNC -> 10 pin
const uint8_t FNC_PIN = 10; 
Generator gen(FNC_PIN);

void setup()
{
  Serial.begin(9600);
}

char buf[3];
char buf_p[3];
bool sin_triangle = false;

void loop()
{
  if (Serial.available() >= 3 && (buf[0] != buf_p[0] || buf[1] != buf[1]))
  {
    //String s = Serial.readString();
    Serial.readBytes(buf, 3);
    
    char row = buf[0] - 48;
    char col = buf[1] - 48;
    char state = buf[2] - 48;

    if (row == '0' && col == '3' && state == '1'){
    sin_triangle = (!sin_triangle); // Changing wave type
    }
    
    if(row == '0' && col == '0' && state == '1')
    {
      gen.write_freq(262);                // frequency of wave
      gen.write_control(1, sin_triangle); // 1 -> enabled output
      delay(300);
      gen.write_control(0, sin_triangle); // 0 -> disabled output
    }

    if(row == '0' && col == '1' && state == '1')
    {
      gen.write_freq(294);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle); // 0 -> disable output
    }

    if(row == '0' && col == '2' && state == '1')
    {
      gen.write_freq(330);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle); // 0 -> disable output
    }

    if(row == '1' && col == '0' && state == '1')
    {
      gen.write_freq(349);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle); // 0 -> enable/disable output
    }

    if(row == '1' && col == '1' && state == '1')
    {
      gen.write_freq(392);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle);
    }

    if(row == '1' && col == '2' && state == '1')
    {
      gen.write_freq(440);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle);
    }

    if(row == '2' && col == '0' && state == '1')
    {
      gen.write_freq(494);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle);
    }

    if(row == '2' && col == '1' && state == '1')
    {
      gen.write_freq(536);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle);
    }

    if(row == '2' && col == '2' && state == '1')
    {
      gen.write_freq(562);
      gen.write_control(1, sin_triangle);
      delay(300);
      gen.write_control(0, sin_triangle);
    }

    for(int i = 0; i < 3; ++i)
    {
      buf_p[i] = buf[i];
    }
  }
}
