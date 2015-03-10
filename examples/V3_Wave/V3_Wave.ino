/*
Grove LED Bar - Wave Example
...
*/

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
  bar.begin();
}

// Frames of continuous waves
unsigned char state[] =
{
  0b11111111,
  0b01111111,
  0b00111111,
  0b00011111,
  0b00001111,
  0b00000111,
  0b00000011,
  0b00000001,
  0b00000000,
  0b00000001,
  0b00000011,
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
  0b00000011,
  0b00000001,
  0b00000000
};

void loop()
{
  for (byte i = 0; i < (sizeof(state) - 9); i++) {
    bar.setBits(state + i);
    delay(50);
  };
}
