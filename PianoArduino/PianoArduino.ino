#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 74

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
	Serial.begin(2000000);
	Serial.println("resetting");
  Serial.setTimeout(1);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(85);
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }


void loop() {
  static uint8_t hue = 0;
  while(Serial.available() > 0)
  {
    int msg = Serial.read();

//    Serial.println(buffer);
    int note = msg & 0x7F;
    int led = map(note, 0,87, 73,0);
    
    if(msg & 0x80) {
      leds[led] = CHSV(hue++, 255, 255);
        hue+=2;
//      Serial.print(led);
//      Serial.println(" On");
    } else {
      leds[led] = CHSV(0, 0, 0);
//      Serial.print(led);
//      Serial.println(" Off");   
    }

   
    
  }
//  fadeall();
  FastLED.show(); 
}
