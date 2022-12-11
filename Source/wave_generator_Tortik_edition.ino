#include "gen_lib.h" // wave generator library
#include "Keypad.h"  // keypad library

// Бинд клавиш клавиатуры
const byte ROWS = 4; // 4 rows
const byte COLS = 4; // 4 cols
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; 

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//data -> 11 pin, clk -> 13 pin, FNC -> 10 pin
const uint8_t FNC_PIN = 10; 

//notes freq (C, D, E, F, G, A, B)
uint16_t notes[7] = { 262, 294, 330, 349, 392, 440, 494 };
enum notes { C, D, E, F, G, A, B };
// Later smth went wrong and I wrote curtain frequency

Generator gen(FNC_PIN);

void setup() 
{
 Serial.begin(9600);
}

bool sin_triangle = false;

void loop() 
{
 char key = keypad.getKey();  // read key
 
 //  Changing type of wave, sin = 0, triangle = 1
  if (key == 'C'){
    Serial.println(key); 
    sin_triangle = (!sin_triangle); // Changing wave type
  }

  // if 1 => С(До) etc.
  if(key == '1'){
    Serial.println(key); // Checking input in Seial port
    gen.write_freq(262);                // frequency of wave
    gen.write_control(1, sin_triangle); // 1 -> enabled output
    delay(300);
    gen.write_control(0, sin_triangle); // 0 -> disabled output
  }
  
  if(key == '2'){
    Serial.println(key);
    gen.write_control(0, sin_triangle);
    gen.write_freq(294);
    gen.write_control(1, sin_triangle);
    delay(300);
  }
  
    if(key == '3'){
    Serial.println(key);
    gen.write_freq(330);
    gen.write_control(1, sin_triangle);
    delay(300);
    gen.write_control(0, sin_triangle); // 0 -> disable output
  }
  
    if(key == '4') {
    Serial.println(key);
    gen.write_freq(349);
    gen.write_control(1, sin_triangle);
    delay(300);
    gen.write_control(0, sin_triangle); // 0 -> enable/disable output
  }
  
    if(key == '5'){
    Serial.println(key);
    gen.write_freq(392);
    gen.write_control(1, sin_triangle);
    delay(300);
    gen.write_control(0, sin_triangle);
  }
  
    if(key == '6'){
    Serial.println(key);
    gen.write_freq(440);
    gen.write_control(1, sin_triangle);
    delay(300);
    gen.write_control(0, sin_triangle);
  }
  
    if(key == '7'){
    Serial.println(key);
    gen.write_freq(494);
    gen.write_control(1, sin_triangle);
    delay(300);
    gen.write_control(0, sin_triangle);
  }  
  
 /*
  // Recorded song
  uint8_t voice_one_amount = 6;
  uint8_t voice_one_notes[voice_one_amount] = {C, D, E, C, D, C};
  uint16_t voice_one_duration = 1000;

  uint8_t voice_two_amount = 5;
  uint8_t voice_two_notes[voice_two_amount] = {G, F, E, D, C};
  uint16_t voice_two_duration = 1000;

  // Playing recorded song
  melody_player(voice_one_notes, voice_one_amount, voice_one_duration);
  
  delay(2000);

  melody_player(voice_two_notes, voice_two_amount, voice_two_duration);
  */
}

void melody_player(uint8_t* note, uint8_t amount, uint16_t duration) {
  for(uint8_t i = 0; i < amount; ++i) 
  {
    gen.write_control(0, 1);
    gen.write_freq(notes[note[i]]);
    gen.write_control(1, 1);
    delay(duration);
  }
}
