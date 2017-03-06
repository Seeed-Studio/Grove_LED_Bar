/*
Grove LED Bar - Walk Multiple Example
This example will show you how to use setBits() function of this library.
Set any combination of LEDs using 10 bits.
This example walks through all 1024 (2^10) possible combinations on two LED Bars.

Ported for MSP-EXP430F5529, TM4c123 (Tiva C) LaunchPad By Cameron P. LaFollette
*/

#include <Grove_LED_Bar.h>

// Arduino Clock pin, Data pin, Orientation 
// Grove_LED_Bar bar1(9, 8, 0); // Clock pin, Data pin, Orientation
//Grove_LED_Bar bar2(7, 6, 1);  // Clock pin, Data pin, Orientation

// LaunchPad Clock pin, Data pin, Orientation
Grove_LED_Bar bar1(37, 38, 0);  // Clock pin, Data pin, Orientation
Grove_LED_Bar bar2(35, 36, 0);  // Clock pin, Data pin, Orientation



void setup()
{
  // nothing to initialize
  bar1.begin();
  bar2.begin();
}

void loop()
{
  // 0 = 0x0 = all 10 LEDs turned off
  // 1023 = 0x3FF = all 10 LEDs lit up
  for (int i = 0; i <= 1023; i++)
  {
    bar1.setBits(i);
    bar2.setBits(i);
    delay(50);
  }
}
