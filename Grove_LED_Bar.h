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

// Avoid name conflict
#define GLB_CMDMODE 0x00  // Work on 8-bit mode

//FOR INNER DEVELOPER
//BE SURE TO DISTINGUISH THEM WITH DIFFERENT ENUM NUMBERS
enum LedType
{
    LED_TYPE_SHIFT       = 16,

    //LED_NEW_DEVICE_I & LED_MASK can get the number I
    LED_MASK             = (1 << LED_TYPE_SHIFT) - 1,

    //LED_NEW_DEVICE_I   = ID << LED_TYPE_SHIFT | I,
    //I denotes the number of LED lights
    LED_BAR_10           = 0 << LED_TYPE_SHIFT | 10,
    LED_CIRCULAR_24      = 0 << LED_TYPE_SHIFT | 24,

    //BE SURE MAX_LED_COUNT DENOTES THE MAX NUMBER OF LED LIGHTS
    MAX_LED_COUNT        = 24,
};

class Grove_LED_Bar
{

private:

  uint32_t __pinClock;            // Clock pin
  uint32_t __pinData;             // Data pin
  uint32_t __led_num;
  LedType  __type;
  bool     __greenToRed;          // Orientation (0 = red to green, 1 = green to red)
  uint8_t __state[MAX_LED_COUNT]; // Led state, brightness for each LED

  void sendData(uint32_t data);   // Send a word to led bar
  void latchData(void);           // Load data into the latch register
  void setData(uint8_t bits[]);   // Set data array

public:
  Grove_LED_Bar(uint8_t pinClock, uint8_t pinData, bool greenToRed, LedType type = LED_BAR_10);  // Initialize
  void begin()
  {
      pinMode(__pinClock, OUTPUT); 
      pinMode(__pinData, OUTPUT);
  }
  void setGreenToRed(bool greenToRed);             // (Re)set orientation
  void setLevel(float level);                      // Set level, range from 0 to 10
  void setLed(uint8_t led, float brightness);      // Set brightness for a single led, range from 0 to 1
  void toggleLed(uint8_t led);                     // Toggle a single led
  void setBits(uint32_t bits);                     // Toggle leds to match given bits
  void setLedNum(uint32_t bits);

  uint32_t const getBits();                        // Get the current state
};

#endif
