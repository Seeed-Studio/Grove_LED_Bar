/*
  LED bar library V1.0
  2010 Copyright (c) Seeed Technology Inc.  All right reserved.
 
  Original Author: LG
  
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
#include "LED_Bar.h"
#include <Arduino.h>

LED_Bar::LED_Bar(void)
{
//  _clk=clk;
//  _dat=dat;
  DDR_Data |= BIT_Data;
  DDR_Clk |= BIT_Clk;
 // pinMode(_clk,OUTPUT);  //Data pin
//  pinMode(_dat,OUTPUT);  //CLK pin
}

void LED_Bar::set_LED_Index(unsigned int index)
//index: range 0b000000000000~0b001111111111, 1 stands light whlie 0 stands off;
{
  unsigned char i;
  send16bitData(CmdMode); 
  for (i=0;i<12;i++)
  {
    if (index&0x0001)
    send16bitData(ON);
    else
    send16bitData(SHUT);
    index= index>>1;
  }
  latchData();
}
void LED_Bar::set_LED_Index(unsigned int index1,unsigned int index2)
//index: range 0b000000000000~0b001111111111, 1 stands light whlie 0 stands off;
{
  unsigned char i;
  for (unsigned char j =0;j<2;j++)
  {
      send16bitData(CmdMode); 
      if (j==0)
      {
      for (i=0;i<12;i++)
        {
          if (index1&0x0001)
          send16bitData(ON);
          else
          send16bitData(SHUT);
         index1= index1>>1;
        }
      }
      if (j==1)
      {
      for (i=0;i<12;i++)
        {
          if (index2&0x0001)
          send16bitData(ON);
          else
          send16bitData(SHUT);
         index2= index2>>1;
        }
      }
  }
      latchData();
}
void LED_Bar::set_LED_Range(unsigned int indexTo)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
   send16bitData(CmdMode); 
  for(i=0;i<12;i++)
  {
    if(i<indexTo)
    {
      send16bitData(ON);
    }
    else 
    {
      send16bitData(SHUT);
    }
     // indexTo=indexTo>>1;
  }
   
  latchData();
}
void LED_Bar::set_LED_Range(unsigned int indexTo1,unsigned int indexTo2)
//indexto : range 1~10.for example: 5, the 1~5 would be light 
{
  unsigned char i;
  
  for (unsigned char j =0;j<2;j++)
  {
    send16bitData(CmdMode); 
   if (j==0)
    {
    for(i=0;i<12;i++)
        {
        if(i<indexTo1)
        {
          send16bitData(ON);
        }
        else 
        {
          send16bitData(SHUT);
         }
        }
    }
    if (j==1)
    {
       for(i=0;i<12;i++)
        {
        if(i<indexTo2)
        {
          send16bitData(ON);
        }
        else 
        {
          send16bitData(SHUT);
         }
        }
    }
   
  }
  latchData();
}
void LED_Bar::send16bitData(unsigned int data)
{
  for(unsigned char i=0;i<16;i++)
    {
        if(data&0x8000)
        {
            PORT_Data |= BIT_Data;
        }
        else
        {
            PORT_Data &=~ BIT_Data;
        }

        PORT_Clk ^= BIT_Clk;
        data <<= 1;
    }
}
void LED_Bar::latchData(void)
{
    PORT_Data &=~ BIT_Data;
    delayMicroseconds(10);
    for(unsigned char i=0;i<8;i++)
    {
        PORT_Data ^= BIT_Data;
    }
}
