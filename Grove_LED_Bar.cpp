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

#include"Grove_LED_Bar.h"

enum LedState{
  LED_TURN_OFF,
  LED_FULL_BRIGHTNESS = 0xff,
};

namespace LedSpace{
  uint32_t ledCountOf(LedType type){
    return (uint32_t)type & LED_MASK;
  }
  void latch(uint32_t scl, uint32_t sda){
    digitalWrite(sda, LOW);
    digitalWrite(scl, HIGH);
    digitalWrite(scl, LOW);
    digitalWrite(scl, HIGH);
    digitalWrite(scl, LOW);
    delayMicroseconds(240);
    digitalWrite(sda, HIGH); digitalWrite(sda, LOW);
    digitalWrite(sda, HIGH); digitalWrite(sda, LOW);
    digitalWrite(sda, HIGH); digitalWrite(sda, LOW);
    digitalWrite(sda, HIGH); digitalWrite(sda, LOW);
    delayMicroseconds(1);
    digitalWrite(scl, HIGH);
    digitalWrite(scl, LOW);
  }
  void send(uint32_t scl, uint32_t sda, uint16_t bits){
    //high 8bit
    digitalWrite(sda, bits & 0x8000 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x4000 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x2000 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x1000 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x0800 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0400 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x0200 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0100 ? HIGH : LOW); digitalWrite(scl, 0);
  
    //low 8bit
    digitalWrite(sda, bits & 0x0080 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0040 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x0020 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0010 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x0008 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0004 ? HIGH : LOW); digitalWrite(scl, 0);
    digitalWrite(sda, bits & 0x0002 ? HIGH : LOW); digitalWrite(scl, 1);
    digitalWrite(sda, bits & 0x0001 ? HIGH : LOW); digitalWrite(scl, 0);
  }
  void send(uint32_t scl, uint32_t sda, LedType type, uint8_t led[]){
    send(scl, sda, 0x00); //send cmd (0x00)
    for (uint32_t i = 0; i < 12; i++){
      send(scl, sda, led[i]);
    }

    //because LED_CIRCULAR_24 have two MY9221(IC), so need send data twice
    if (LED_CIRCULAR_24 == type){ 
      send(scl, sda, 0x00); //send cmd (0x00)
      for (uint16_t i = 12; i < 24; i++){
        send(scl, sda, led[i]);
      }
    }
    
    latch(scl, sda);
  }
  void reverse(uint8_t led[], uint32_t count){
    for (uint32_t i = 0; i < count / 2; i++){
      uint8_t t = led[i];
      led[i] = led[count - i - 1];
      led[count - i - 1] = t;
    }
  }
}

Grove_LED_Bar::Grove_LED_Bar(uint32_t pinClock, uint32_t pinData, bool reverseShow, LedType type){
  this->pinClock      = pinClock;
  this->pinData       = pinData;
  this->reverseShow   = reverseShow;
  this->type          = type;
  this->numberOfShows = LedSpace::ledCountOf(type);

  for (uint32_t i = 0; i < LED_MAX_COUNT; i++){
    led[i] = LED_TURN_OFF;
  }

  pinMode(pinData, OUTPUT);
  pinMode(pinClock, OUTPUT);
}
void Grove_LED_Bar::setBits(uint32_t bits){
  uint32_t i = 0;
  
  while (i < numberOfShows){
    led[i] = bits & 1 ? LED_FULL_BRIGHTNESS : LED_TURN_OFF;
    bits >>= 1;
    i++;
  }
  
  while(i <= LedSpace::ledCountOf(type)){
    led[i] = LED_TURN_OFF;
    i++;
  }

  if (reverseShow){
    LedSpace::reverse(led, numberOfShows);
  }

  LedSpace::send(pinClock, pinData, type, led);
}
void Grove_LED_Bar::setLevel(float level){
  uint32_t countOfLedFullBrightness = (uint32_t)level;
  uint32_t lastLedBrightness = 
  uint32_t((level - countOfLedFullBrightness) * LED_FULL_BRIGHTNESS);
  uint32_t i = 0;
  
  while(i < countOfLedFullBrightness){
    led[i] = LED_FULL_BRIGHTNESS;
    i++;
  }

  led[countOfLedFullBrightness] = lastLedBrightness;
  LedSpace::send(pinClock, pinData, type, led);
}
void Grove_LED_Bar::setLed(uint32_t ledNo, float value) {
  uint32_t brightness = uint32_t(value * LED_FULL_BRIGHTNESS);

  if (brightness > LED_FULL_BRIGHTNESS){
    brightness = LED_FULL_BRIGHTNESS;
  }
  if (ledNo >= LedSpace::ledCountOf(type)) { 
    ledNo = LedSpace::ledCountOf(type);
  }
  
  led[ledNo - 1] = brightness;
  LedSpace::send(pinClock, pinData, type, led);
}
void Grove_LED_Bar::setGreenToRed(bool reverseShow) {
  if (this->reverseShow == reverseShow){
    return;
  }

  this->reverseShow = reverseShow;
  LedSpace::reverse(led, numberOfShows);
  LedSpace::send(pinClock, pinData, type, led);
}
void Grove_LED_Bar::setLedNum(uint32_t numberOfShows){
  this->numberOfShows = 
    numberOfShows <= LED_MAX_COUNT ? 
    numberOfShows :
    LED_MAX_COUNT; 
}
void Grove_LED_Bar::toggleLed(uint32_t ledNo){
  if (ledNo >= LedSpace::ledCountOf(type)) { 
    ledNo = LedSpace::ledCountOf(type);
  }
  
  uint32_t i = ledNo - 1;
  led[i] = led[i] ? LED_TURN_OFF : LED_FULL_BRIGHTNESS;
  LedSpace::send(pinClock, pinData, type, led);
}
uint32_t Grove_LED_Bar::getBits(){
  uint32_t result = 0;
  uint32_t i = numberOfShows;

  while(i--){
    result = result << 1 | (led[i] != LED_TURN_OFF);
  }
  
  return result;
}
