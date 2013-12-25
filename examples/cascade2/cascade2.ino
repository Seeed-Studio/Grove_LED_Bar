/* Grove - LED Bar demo v1
/  by http://www.seeedstudio.com/
/   cascade  2 LED bar as the picture in 
/   http://www.seeedstudio.com/depot/images/product/bar_02.jpg
*/
#include "LED_Bar.h"
LED_Bar myLED;
void setup()
{
  // the set_LED_Index set the indivial LED state.
  //for example:the 0b000001101010101, the "1101010101" means:
  //LED10------ON;
  //LED9------ON;
  //LED8------OFF;
  //LED7------ON;
  //LED6------OFF; 
  //LED5------ON;
  //LED4------0FF;
  //LED3------ON;
  //LED2------OFF;
  //LED1------ON;
  // while the first "00000" is reserved.
  
  myLED.set_LED_Index(0b000001101010101,0b0000000010101010);
 // myLED.set_LED_Index(0b0000000010101010);
  delay(3000);
}

void loop()
{
for (int i =0;i<=10;i++)
// set the light range ; 0 means no LED will light, 
// "3" means the first 3 LED will be light.
  {
  myLED.set_LED_Range(i,i-2);// the further one fron the grove connector is the 
  //first one ;
  delay(1000);
  }
}

