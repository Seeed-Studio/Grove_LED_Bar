/*
Grove LED Bar - Walk Example
This example will show you how to use setBits() function of this library.
Set any combination of LEDs using 10 bits.
This example walks through all 1024 (2^10) possible combinations.
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
  // 0 = 0x0 = all 10 LEDs turned off
  // 1023 = 0x3FF = all 10 LEDs lit up
  for (int i = 0; i <= 1023; i++)
  {
    bar.setBits(i);
    delay(50);
  }
}
