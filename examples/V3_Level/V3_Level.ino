/*
Grove LED Bar - Brightness Level Example
...
*/

#include <Grove_LED_Bar.h>

#define USE_LED_CIRCULAR_24
#ifdef USE_LED_CIRCULAR_24
Grove_LED_Bar bar(7, 6, 0, LED_CIRCULAR_24); // Clock pin, Data pin, Orientation
#else
Grove_LED_Bar bar(6, 7, 0, LED_BAR_10); // Clock pin, Data pin, Orientation
#endif

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
