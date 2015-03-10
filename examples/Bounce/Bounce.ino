/*
Grove LED Bar - Bounce Example
This example will show you how to use getBits() function of this library.
The getBits() function returns the current state so you can modify it.
Use the setBits() function to save the new state.
*/

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

unsigned int state;

void setup()
{
  // nothing to initialize
  bar.begin();
}

void loop()
{
  // Switch on the first two LEDs
  bar.setLevel(2);

  // Get the current state (which is 0x3)
  state = bar.getBits();

  // Bounce to the right
  for (int i = 0; i < 8; i++)
  {
    // Bit shift left and update
    state <<= 1;
    bar.setBits(state);
    delay(200);
  }

  // Bounce to the left
  for (int i = 0; i < 8; i++)
  {
    // Bit shift right and update
    state >>= 1;
    bar.setBits(state);
    delay(200);
  }
}
