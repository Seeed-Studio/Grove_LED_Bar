/*
Grove LED Bar - Wave Example
...
*/

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
}

// Frames of continuous waves
unsigned char state[20] =
{
  0b11111111,
  0b01111111,
  0b00111111,
  0b00011111,
  0b00001111,
  0b00000111,
  0b00001111,
  0b00011111,
  0b00111111,
  0b01111111,
  0b11111111,
  0b01111111,
  0b00111111,
  0b00011111,
  0b00001111,
  0b00000111,
  0b00001111,
  0b00011111,
  0b00111111,
  0b01111111 
};

void loop()
{
  for (byte i = 0; i < 10; i++) {
    bar.setBits(state + i);
    delay(100);
  };
}
