/*
  LED bar library V1.0
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

#include <Arduino.h>

#include "LED_Bar.h"

LED_Bar::LED_Bar(int pinClk, int pinDta)
{
    __pinClk = pinClk;
    __pinDta = pinDta;

    __led_state = 0x00;
    
    pinMode(__pinClk, OUTPUT);
    pinMode(__pinDta, OUTPUT);
}

void LED_Bar::latchData()
{
    digitalWrite(__pinDta, LOW);
    delayMicroseconds(10);

    for(int i=0; i<4; i++)
    {
        digitalWrite(__pinDta, HIGH);
        digitalWrite(__pinDta, LOW);
    }

}

void LED_Bar::send16bitData(unsigned int data)
{
    for(int i=0; i<16; i++)
    {
        unsigned int state = data&0x8000 ? HIGH : LOW;
        digitalWrite(__pinDta, state);

        state = digitalRead(__pinClk) ? LOW : HIGH;
        digitalWrite(__pinClk, state);

        data <<= 1;
    }
}

// set led single bit, a bit contrl a led
// such as, index_bits = 0x05, then led 0  and led 3 will on, the others will off
void LED_Bar::ledIndexBit(unsigned int index_bits)
{

    send16bitData(CMDMODE);

    for (int i=0;i<12;i++)
    {
        unsigned int state = (index_bits&0x0001) ? ON : SHUT;
        send16bitData(state);

        index_bits = index_bits>>1;
    }

    latchData();
}

// set level, there level 0-10
// level 0 means all leds off while level 5 means 5led on and the other will off
void LED_Bar::setLevel(int level)
{

    if(level>10)return;

    send16bitData(CMDMODE);

    for(int i=0;i<12;i++)
    {
        unsigned int state1 = (i<level) ? ON : SHUT;
        
        send16bitData(state1);
    }

    latchData();
}

// set level in the opposite direction (green to red)
void LED_Bar::setLevelReverse(int level)
{
    if(level>10)return;

    send16bitData(CMDMODE);

    for(int i=0;i<12;i++)
    {
        unsigned int state1 = (i>=(10-level)) ? ON : SHUT;
        
        send16bitData(state1);
    }

    latchData();
}

// control a single led
// num - which led
// st - 1: on   0: off
void LED_Bar::setSingleLed(int num, int st)
{
    if(num>10)return;
    __led_state = st ? (__led_state | (0x01<<num)) : (__led_state & ~(0x01<<num));
    ledIndexBit(__led_state);

}