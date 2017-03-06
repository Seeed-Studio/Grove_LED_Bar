/*
Grove LED Bar - Basic Control Example
This example will show you how to use the setBits() function of this library.
Set any combination of LEDs using 10 bits.
Least significant bit controls the first LED.

The setBits() function sets the current state, one bit for each LED.
First 10 bits from the right control the 10 LEDs.

eg. 0b00000jihgfedcba
a = LED 1, b = LED 2, c = LED 3, etc.

dec    hex     binary
0    = 0x0   = 0b000000000000000 = all LEDs off
5    = 0x05  = 0b000000000000101 = LEDs 1 and 3 on, all others off
341  = 0x155 = 0b000000101010101 = LEDs 1,3,5,7,9 on, 2,4,6,8,10 off
1023 = 0x3ff = 0b000001111111111 = all LEDs on
                      |        |
                      10       1

The bits >10 are ignored, shown here as x: 0bxxxxx0000000000

Ported for MSP-EXP430F5529, TM4c123 (Tiva C) LaunchPad By Cameron P. LaFollette
*/

#include <Grove_LED_Bar.h>

// Arduino Clock pin, Data pin, Orientation 
// Grove_LED_Bar bar(7, 6, 0);  

// LaunchPad Clock pin, Data pin, Orientation
Grove_LED_Bar bar(35, 36, 0);  

void setup()
{
  // nothing to initialize
  bar.begin();
  
}

void loop()
{
  // Turn on all LEDs
  bar.setBits(0x3ff);
  delay(1000);

  // Turn off all LEDs
  bar.setBits(0x0);
  delay(1000);

  // Turn on LED 1
  // 0b000000000000001 can also be written as 0x1:
  bar.setBits(0b000000000000001);
  delay(1000);

  // Turn on LEDs 1 and 3
  // 0b000000000000101 can also be written as 0x5:
  bar.setBits(0b000000000000101);
  delay(1000);

  // Turn on LEDs 1, 3, 5, 7, 9
  bar.setBits(0x155);
  delay(1000);

  // Turn on LEDs 2, 4, 6, 8, 10
  bar.setBits(0x2AA);
  delay(1000);

  // Turn on LEDs 1, 2, 3, 4, 5
  // 0b000000000011111 == 0x1F
  bar.setBits(0b000000000011111);
  delay(1000);

  // Turn on LEDs 6, 7, 8, 9, 10
  // 0b000001111100000 == 0x3E0
  bar.setBits(0b000001111100000);
  delay(1000);
}

