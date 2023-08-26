#pragma once

#include <FastLED.h>
#include <fstream>
#include <cstring>
/**
* Developer: Joshua Chadwick
* Description: This class will be used to handle encoded HTTP requests from the Android APP and adjust the LEDs in the lamp
**/
class LEDManager {

    public:
      LEDManager(CRGB led_strip[]) {
        leds = led_strip;

        // DEFAULT VALUES FOR ORIGINAL LAMP! I will make it more dynamic in the future (if anybody will ever want to use this...)
        touchPin = T0;
        val = 0;
        threshold = 74; // Sensetivity value of the touch-wire in the lamp
        counter = 0; // A flag variable to signal whether the LEDs are on or off
      };

      LEDManager() {
        leds = nullptr;

      }

      ~LEDManager() {
        delete leds;
      }

      bool decodeHTTPMessage(String HTTP_REQUEST_CONTENT);

      void animateON();

      void animateOFF();
    
    private:
      //Stuff for TTP223 Touch Sensor
      String touchPin; //GPIO4 A.K.A Touch Pin 0 on ESP32 WROOM
      int val;
      int threshold;
      int counter;
      
      CRGB *leds;

};
