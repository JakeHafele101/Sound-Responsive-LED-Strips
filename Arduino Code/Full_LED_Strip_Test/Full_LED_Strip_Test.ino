#include <FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 2
#define BRIGHTNESS 255
#define SATURATION 255;
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

int hue = 1;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
}

void loop() {
  // put your main code here, to run repeatedly:
  setRainbow();
  FastLED.show();
  delay(1000/UPDATES_PER_SECOND);
}

void setWhite(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
  }
}

void setRainbow(){
  hue++;
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].setHue(hue % 255);
  }
}
