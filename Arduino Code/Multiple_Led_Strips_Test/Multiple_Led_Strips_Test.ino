#include <FastLED.h>

#define LED_STRIP_1 2
#define LED_STRIP_2 3

#define NUM_STRIPS 2
#define NUM_LEDS 60
#define BRIGHTNESS 255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_STRIPS][NUM_LEDS];

#define UPDATES_PER_SECOND 10


void setup() {
  // put your setup code here, to run once:
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_STRIP_1, COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_2, COLOR_ORDER>(leds[1], NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // put your main code here, to run repeatedly:
  setWhite();
  FastLED.show();
  delay(1000/UPDATES_PER_SECOND)
}

void setWhite(){
  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      leds[i][j] = CRGB::White;
    }
  }
}
