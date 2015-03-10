/*
Grove LED Bar - Toggle Example
This example will show you how to use toggleLed() function of this library.
The function lets you set a single led to the opposite of it's current value.
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
  // Start with all LEDs illuminated
  bar.setLevel(10);
  delay(1000);

  // Turn off LED 3
  bar.toggleLed(3);
  delay(1000);

  // Turn on LED 3
  bar.toggleLed(3);
  delay(1000);

  // Switch off all LEDs
  bar.setLevel(0);
  delay(1000);

  // Turn on LED 7
  bar.toggleLed(7);
  delay(1000);

  // Turn off LED 7
  bar.toggleLed(7);
  delay(1000);
}
