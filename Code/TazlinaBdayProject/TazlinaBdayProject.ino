#include <FastLED.h>

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <WiFiManager.h>
#include "LEDManager.h"

//Stuff for TTP223 Touch Sensor
int touchPin = T0; //GPIO4 A.K.A Touch Pin 0 on ESP32 WROOM
int val = 0;
int threshold = 74; // Modify this to adjust the sensitivity of the hand-proximity detector
int counter = 0;

//Stuff for FastLED
#define NUM_LEDS 60
#define DATAPIN 22
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//----------
//WiFi Stuff - TODO: Add feature to connect locally to ESP32 (via Bluetooth or something) if WiFi networks are unavailable
//----------


void setup() {
  
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  
  WiFiManager wm; // The use of WiFiManager simplifies the process of connecting our ESP32 to a WiFi network.
  
  wm.resetSettings(); //Removes all stored WiFi credentials every time the ESP32 is turned on. Might want to remove and later replace with 
                      //an On-Demand switch in the APP when we want to connect to a new WiFi network.

  bool res;
  res = wm.autoConnect("TazlinaHeartLamp", "dancewithme"); // Initiates a process to turn the ESP32 into an Access Point, feed an HTML page to the user to setup a WiFi network, and then restarts the ESP32 in server mode
  if (!res) {
    Serial.println("Failed to connect");
  } else { // Now that we are connected to the open Internet, we will connect the ESP32 to a local mobile device via Bluetooth to broadcast the IP address to the Android App.
    //initBLEConnection();
    Serial.println("Connect to BLE next");
  }

  delay(1000);
  
  //FastLED Stuff
  FastLED.addLeds<LED_TYPE, DATAPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); //Establishing our LED Strip

  FastLED.setBrightness(50); //Set our initial brightness

}

void loop() {


  
  /*
  THIS SECTION IS FOR NON-WiFi RELATED FUNCTIONS
  ----------------------------------------------
  */
  val = touchRead(touchPin);
  Serial.println(val);
  if (val < threshold) { //Checks to see if there's a touch
    delay(500); //Helps with debounce (ensures it wasn't a false activation/touch)
    val = touchRead(touchPin); //Checks the value again to see if we are actually touching it
    if (val < threshold) {
      Serial.print("Hand detected! Value: ");
      Serial.print(val);
      Serial.println();
      delay(1000);

      if (counter == 0) { //Counter acts as an on/off switch for the heart. It should only ever have a value of 0 or 1

        counter++;
        //FastLED Stuff - Turns on heart with a simple animation
        for(int i = 0; i < NUM_LEDS; i++) { //Fades the LEDs into bright red
          leds[i] = CRGB::Red;
          FastLED.show();
          delay(50);
        }
        delay(1000);
      }

      else {

        counter = 0;
        for(int i = 0; i < NUM_LEDS; i++) { //Fades the LEDs out to off
          leds[i] = CRGB::Black;
          FastLED.show();
          delay(50);
        }
      }

      FastLED.show();
    }
  }
}
