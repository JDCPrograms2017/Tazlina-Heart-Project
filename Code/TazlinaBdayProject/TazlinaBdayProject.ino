#include <FastLED.h>
#include <WiFi.h>

//Stuff for TTP223 Touch Sensor
int touchPin = T0; //GPIO4 A.K.A Touch Pin 0 on ESP32 WROOM
int val = 0;
int threshold = 75;
int counter = 0;

//Stuff for FastLED
#define NUM_LEDS 60
#define DATAPIN 22
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//WiFi Stuff
char ssid[] = "randomSSID";
char password[] = "password";

void setup() {
  Serial.begin(9600);
  pinMode(touchPin, INPUT);

  delay(1000);

  //WiFi Stuff
  Serial.print("Connecting to...");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //Begins to attempt connecting to specified WiFi network

  while (WiFi.status() != WL_CONNECTED) { //Waits until connection is successfully established
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP()); //Displays local IP of ESP32

  server.begin();
  
  //FastLED Stuff

  FastLED.addLeds<LED_TYPE, DATAPIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); //Establishing our LED Strip

  FastLED.setBrightness(50); //Set our initial brightness
}

void loop() {
  // put your main code here, to run repeatedly:
  val = touchRead(touchPin);
  Serial.println(val);
  if (val < threshold) { //Checks to see if there's a touch
    delay(500); //Helps with debounce (ensures it wasn't a false activation/touch)
    val = touchRead(touchPin); //Checks the value again to see if we are actually touching it
    if (val < threshold) {
      Serial.print("Touched, value: ");
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
