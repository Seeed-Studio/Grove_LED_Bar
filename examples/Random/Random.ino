/*
Grove LED Bar - Random Example
This example will show you how to use setBits() function of this library.
Set any combination of LEDs using 10 bits.
*/

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
  bar.begin();
}

void loop()
{
  // Display a random value between 0 (all LEDs off) and 1023 (all LEDs on)
  bar.setBits(random(1024));
  delay(50);
}
