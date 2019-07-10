/*
Grove LED Bar - Brightness Level Example
...
Ported for MSP-EXP430F5529, TM4c123 (Tiva C) LaunchPad By Cameron P. LaFollette
*/

#include <Grove_LED_Bar.h>

// Arduino Clock pin, Data pin, Orientation
Grove_LED_Bar bar(7, 6, 0, LED_BAR_10); // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
  bar.begin();
}

void loop()
{
  bar.setGreenToRed(false);
  for (float i = 0; i < 10.1; i += 0.125)
  {
    bar.setLevel(i);
    delay(25);
  };
  for (float i = 0; i < 10.1; i += 0.125)
  {
    bar.setLevel(10 - i);
    delay(25);
  };

  // Change orientation
  bar.setGreenToRed(true);
  for (float i = 0; i < 10.1; i += 0.125)
  {
    bar.setLevel(i);
    delay(25);
  };
  for (float i = 0; i < 10.1; i += 0.125)
  {
    bar.setLevel(10 - i);
    delay(25);
  };
}
