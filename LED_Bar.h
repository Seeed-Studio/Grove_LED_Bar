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
#ifndef LED_Bar_H
#define LED_Bar_H
#include <Arduino.h>

#define DDR_Data  DDRB
#define DDR_Clk   DDRB
#define PORT_Data PORTB
#define PORT_Clk  PORTB

#define BIT_Data  0x01
#define BIT_Clk   0x02

#define CmdMode 0x0000  //Work on 8-bit mode
#define ON 0x00ff   //8-bit 1 data
#define SHUT 0x0000   //8-bit 0 data
class LED_Bar
{
  public:
  LED_Bar(void);
  void set_LED_Index(unsigned int index);
  void set_LED_Index(unsigned int index1,unsigned int index2);
  void set_LED_Range(unsigned int indexTo);
  void set_LED_Range(unsigned int indexTo1,unsigned int indexTo2);
  
  private:
  void send16bitData(unsigned int data);
  void latchData(void);
  int _clk;
  int _dat;
};
#endif;
