/*
  LED bar library V2.0
  2010 Copyright (c) Seeed Technology Inc.  All right reserved.

  Original Author: LG

  Modify: Loovee, 2014-2-26
  User can choose which Io to be used.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Grove_LED_Bar.h"

Grove_LED_Bar::Grove_LED_Bar(unsigned char pinClock, unsigned char pinData, bool greenToRed)
{
  __pinClock = pinClock;
  __pinData = pinData;
  __greenToRed = greenToRed;  // ascending or decending

  for (byte i = 0; i < 10; i++)
    __state[i] = 0x00;  // persist state so individual leds can be toggled

  pinMode(__pinClock, OUTPUT);
  pinMode(__pinData, OUTPUT);
}


// Send the latch command
void Grove_LED_Bar::latchData()
{
  digitalWrite(__pinData, LOW);
  delayMicroseconds(10);

  for (unsigned char i = 0; i < 4; i++)
  {
    digitalWrite(__pinData, HIGH);
    digitalWrite(__pinData, LOW);
  }
}


// Send 16 bits of data
void Grove_LED_Bar::sendData(unsigned int data)
{
  for (unsigned char i = 0; i < 16; i++)
  {
    unsigned int state = (data & 0x8000) ? HIGH : LOW;
    digitalWrite(__pinData, state);

    state = digitalRead(__pinClock) ? LOW : HIGH;
    digitalWrite(__pinClock, state);

    data <<= 1;
  }
}


// Change the orientation
// Green to red, or red to green
void Grove_LED_Bar::setGreenToRed(bool greenToRed)
{
  __greenToRed = greenToRed;

  setData(__state);
}


// Set level (0-10)
// Level 0 means all leds off
// Level 10 means all leds on
// Level 4.5 means 4 LEDs on and the 5th LED's half on
void Grove_LED_Bar::setLevel(float level)
{
  level = max(0, min(10, level));
  level *= 8; // there are 8 (noticable) levels of brightness on each segment
  
  // Place number of 'level' of 1-bits on __state
  for (byte i = 0; i < 10; i++) {
    __state[i] = (level > 8) ? ~0 :
                 (level > 0) ? ~(~0 << byte(level)) : 0;
               
    level -= 8;
  };

  setData(__state);
}


// Set a single led
// led (1-10)
// brightness (0-1)
void Grove_LED_Bar::setLed(unsigned char led, float brightness)
{
  led = max(1, min(10, led));
  brightness = max(0, min(brightness, 1));

  // Zero based index 0-9 for bitwise operations
  led--;

  // 8 (noticable) levels of brightness
  // 00000000 darkest
  // 00000011 brighter
  // ........
  // 11111111 brightest
  __state[led] = ~(~0 << (unsigned char) (brightness*8));

  setData(__state);
}


// Toggle a single led
// led (1-10)
void Grove_LED_Bar::toggleLed(unsigned char led)
{
  led = max(1, min(10, led));

  // Zero based index 0-9 for bitwise operations
  led--;

  __state[led] = __state[led] ? 0 : ~0;

  setData(__state);
}

// each element in the state will hold the brightness level
// 00000000 darkest
// 00000011 brighter
// ........
// 11111111 brightest
void Grove_LED_Bar::setData(unsigned char __state[])
{

  sendData(GLB_CMDMODE);

  for (unsigned char i = 0; i < 10; i++)
  {
    if (__greenToRed)
    {
	  // Go backward on __state
      sendData(__state[10-i-1]);
    }
    else
    {
	  // Go forward on __state
      sendData(__state[i]);
    }
  }

  // Two extra empty bits for padding the command to the correct length
  sendData(0x00);
  sendData(0x00);

  latchData();
}

void Grove_LED_Bar::setBits(unsigned int bits)
{

  for (unsigned char i = 0; i < 10; i++)
  {

    if ((bits % 2) == 1)
      __state[i] = 0xFF;
    else
      __state[i] = 0x00;
    bits /= 2;
  }

  setData(__state);
}


// Return the current bits
unsigned int const Grove_LED_Bar::getBits()
{
  unsigned int __bits = 0x00;
  for (unsigned char i = 0; i < 10; i++)
  {
    if (__state[i] != 0x0)
        __bits |= (0x1 << i);
  }
  return __bits;
}
