/*
Grove LED Bar - Brightness Level Example
...
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
  bar.setGreenToRed(false);
  for (float i = 0; i < 10.1; i += 0.125) {
    bar.setLevel(i);
    delay(25);
  };
  for (float i = 0; i < 10.1; i += 0.125) {
    bar.setLevel(10-i);
    delay(25);
  };
  
  // Change orientation
  bar.setGreenToRed(true);
  for (float i = 0; i < 10.1; i += 0.125) {
    bar.setLevel(i);
    delay(25);
  };
  for (float i = 0; i < 10.1; i += 0.125) {
    bar.setLevel(10-i);
    delay(25);
  };
}
