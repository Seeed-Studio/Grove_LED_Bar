/*
  LED bar library V2.0
  Copyright (c) 2010 Seeed Technology Inc.

  Original Author: LG

  Modify: Loovee, 2014-2-26
  User can choose which Io to be used.
  
  Modify: Long, 2015-01-07
  User can change the brightness level for each LED segment
  Rename constant to avoid name conflict
  
  The MIT License (MIT)

  Copyright (c) 2013 Seeed Technology Inc.

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/
#ifndef Grove_LED_Bar_H
#define Grove_LED_Bar_H

#include <Arduino.h>

//BE SURE TO DISTINGUISH THEM WITH DIFFERENT ENUM NUMBERS
enum LedType {
    LED_TYPE_SHIFT       = 16,

    //LED_NEW_DEVICE_I & LED_MASK can get the number I
    LED_MASK             = (1 << LED_TYPE_SHIFT) - 1,

    //BE SURE MAX_LED_COUNT DENOTES THE MAX NUMBER OF LED LIGHTS
    LED_MAX_COUNT        = 24,

    //FOR USER--------------------------------------------------------
    //DEVICE-TYPE
    //LED_NEW_DEVICE_N   = ID << LED_TYPE_SHIFT | N,
    //N denotes the number of LED lights
    LED_BAR_10           = 0 << LED_TYPE_SHIFT | 10,
    LED_CIRCULAR_24      = 0 << LED_TYPE_SHIFT | 24,
    //--------------------------------------------------------FOR USER
};

class Grove_LED_Bar{
  LedType  type;
  uint32_t pinClock;
  uint32_t pinData;
  uint32_t numberOfShows;
  bool     reverseShow;
  uint8_t  led[LED_MAX_COUNT];
public:
  Grove_LED_Bar(uint32_t pinClock, uint32_t pinData, bool reverseShow, LedType type);
  void begin(){} //dummy
  void setBits(uint32_t bits);
  void setLevel(float level);
  void setLed(uint32_t ledNo, float value);
  void setGreenToRed(bool reverseShow);
  void setLedNum(uint32_t numberOfShows);
  void toggleLed(uint32_t ledNo);
  uint32_t getBits();
};

#endif
