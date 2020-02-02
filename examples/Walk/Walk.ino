/*
    Grove LED Bar - Walk Example
    This example will show you how to use setBits() function of this library.
    Set any combination of LEDs using 10 bits.
    This example walks through all 1024 (2^10) possible combinations.
*/

#include <Grove_LED_Bar.h>

//BE SURE USE CORRESPONDING DEVICE
//Grove_LED_Bar bar(6, 7, 0, LED_CIRCULAR_24);
//FOR LED_BAR_10
Grove_LED_Bar bar(7, 6, 0, LED_BAR_10); // Clock pin, Data pin, Orientation

void setup() {
    // nothing to initialize
    bar.begin();
}

void loop() {
    // 0 = 0x0 = all 10 LEDs turned off
    // 1023 = 0x3FF = all 10 LEDs lit up
    for (int i = 0; i <= 1023; i++) {
        bar.setBits(i);
        delay(50);
    }
}
