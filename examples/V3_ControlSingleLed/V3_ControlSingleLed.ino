/*
Grove LED Bar - Control Single LED Example
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
  // Simulate police LED lights using setLed method
  for (float i = 0; i < 1.1; i += .125f) {
    bar.setLed(1, i);
    bar.setLed(2, i);
    bar.setLed(3, 1 - i);
    bar.setLed(4, 1 - i);
    delay(50);
  };
  
  for (float i = 0; i < 1.1; i += .125f) {
    bar.setLed(1, 1 - i);
    bar.setLed(2, 1 - i);
    bar.setLed(3, i);
    bar.setLed(4, i);
    delay(50);
  };
}
