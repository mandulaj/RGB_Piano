#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 74
#define NUM_KEYS 88
#define UPDATE_INT 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
uint8_t values[NUM_LEDS];
uint8_t hue = 0;
float scale = 0.8;

void setup() { 
	Serial.begin(2000000);
	Serial.println("resetting");
  Serial.setTimeout(1);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(85);

  for(int i = 0; i < NUM_LEDS; i++){
    values[i] = 0;  
  }
}

void fadeall() {
  for(int i = 1; i < NUM_LEDS - 1; i++) {

    if( values[i] == 255) {
      
    } else {
      uint16_t val = ((uint16_t)values[i - 1] + (uint16_t)values[i] + (uint16_t)values[i + 1]) / 3 * scale;
      values[i] = val;
      leds[i] = CHSV(hue, 255, val); 
    }
    
  } 
}



void loop() {
  static uint32_t nextTime = millis() + UPDATE_INT;  
  while(Serial.available() > 0)
  {
    int msg = Serial.read();
    
    switch(msg){
      case 0xFF:
        scale = 1;
        break;
      case 0xFE:
        scale = 0.8;
        break;

      default:
     
        int note = msg & 0x7F;
        int led = map(note, 0,NUM_KEYS - 1, NUM_LEDS - 1,0);
        
      
      
        if(msg & 0x80) {
          leds[led] = CHSV(hue, 255, 255);
          values[led] = 255;
        } else {
          leds[led] = CHSV(0, 0, 0);
          values[led] = 0; 
        }
        hue+=3;

    }
    
  }
  
  if( nextTime < millis()){
    fadeall();
    nextTime += UPDATE_INT;
  }
  
  FastLED.show(); 
}
