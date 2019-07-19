/*
Grove LED Bar - Control Single LED Example
...
*/

#include <Grove_LED_Bar.h>

//BE SURE USE CORRESPONDING DEVICE
//Grove_LED_Bar bar(6, 7, 0, LED_CIRCULAR_24);
//FOR LED_BAR_10
Grove_LED_Bar bar(7, 6, 0, LED_BAR_10); // Clock pin, Data pin, Orientation

void setup()
{
  // nothing to initialize
  bar.begin();
}

void loop()
{
  // Simulate police LED lights using setLed method
  for (float i = 0; i < 1.1; i += .125f)
  {
    bar.setLed(1, i);
    bar.setLed(2, i);
    bar.setLed(3, 1 - i);
    bar.setLed(4, 1 - i);
    delay(50);
  };

  for (float i = 0; i < 1.1; i += .125f)
  {
    bar.setLed(1, 1 - i);
    bar.setLed(2, 1 - i);
    bar.setLed(3, i);
    bar.setLed(4, i);
    delay(50);
  };
}
