/*
Grove LED Bar - Level Example
This example will show you how to use setLevel() function of this library.
The setLevel() function illuminates the given number of LEDs from either side.

Syntax setLevel(level)
0  = all LEDs off
5  = 5 LEDs on
10 = all LEDs on
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
  // Walk through the levels
  for (int i = 0; i <= 10; i++)
  {
    bar.setLevel(i);
    delay(100);
  }
}
