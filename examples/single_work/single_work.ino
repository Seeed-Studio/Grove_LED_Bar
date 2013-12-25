/* Grove - LED Bar demo v1
/  by http://www.seeedstudio.com/
/   
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
  myLED.set_LED_Index(0b000001101010101);
  delay(3000);
}
void loop()
{ 
  for (int i=0;i<=10;i++)
  // set the light range ; 0 means no LED will light, 
// "3" means the first 3 LED will be light.
  {
    myLED.set_LED_Range(i);
    delay(1000);
  }
  
}
