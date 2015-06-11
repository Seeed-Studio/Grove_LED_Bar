/*
Grove LED Bar - Reverse Example
This example will show you how to use setGreenToRed() function of this library.
The function is used to reverse the orientation of the LED Bar.
Ported for MSP-EXP430F5529, TM4c123 (Tiva C) LaunchPad By Cameron P. LaFollette
*/

#include <Grove_LED_Bar.h>

// The 3rd parameter sets the initial orientation
// 0 = green to red, 1 = red to green
// You can always change it at runtime with the setGreenToRed() function

// Arduino Clock pin, Data pin, Orientation 
// Grove_LED_Bar bar(9, 8, 0); // Clock pin, Data pin, Orientation

// LaunchPad Clock pin, Data pin, Orientation
Grove_LED_Bar bar(35, 36, 0);  // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
  bar.begin();
}

void loop()
{
  // Start as red to green
  // Walk through the 10 levels
  for (int i = 0; i <= 10; i++)
  {
    bar.setLevel(i);
    delay(200);
  }
  bar.setLevel(0);

  // Swich to green to red
  bar.setGreenToRed(1);

  // Walk through the 10 levels
  for (int i = 0; i <= 10; i++)
  {
    bar.setLevel(i);
    delay(200);
  }
  bar.setLevel(0);

  // Switch back to red to green
  bar.setGreenToRed(0);
  delay(200);

  // Walk through the levels
  // Each reverse keeps the previously set level
  for (int i = 1; i <= 10; i++)
  {
    bar.setLevel(i);
    delay(500);

    bar.setGreenToRed(1);
    delay(500);

    bar.setGreenToRed(0);
  }
  bar.setLevel(0);
}
