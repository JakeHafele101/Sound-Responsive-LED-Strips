#include <FastLED.h>

#define LED_STRIP_1 2
#define LED_STRIP_2 3

#define NUM_STRIPS 2
#define NUM_LEDS 60
#define BRIGHTNESS 255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_STRIPS][NUM_LEDS];

#define UPDATES_PER_SECOND 100
#define RAINBOW_PER_SECOND 50

int hue = 1;
boolean isHueIncreasing = true;

int rainbowCount = 0;

void setup() {
  // put your setup code here, to run once:
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_STRIP_1, COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_2, COLOR_ORDER>(leds[1], NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {

  if(millis() % RAINBOW_PER_SECOND == 0){
    rainbowCount++;
  }
  
  if(hue > 255){
    isHueIncreasing = false;
  }
  else if(hue < 0){
    isHueIncreasing = true;
  }
  if(isHueIncreasing){
    hue++;
  }
  else{
    hue--;
  }
  
  setRainbowWithWhite(0, rainbowCount);
  setRainbowWithWhite(1, rainbowCount);
  FastLED.show();
  delay(1000/UPDATES_PER_SECOND);
}

void setWhite(int stripNum){
  for(int j = 0; j < NUM_LEDS; j++){
    leds[stripNum][j] = CRGB::White;
  }
}

void setRainbow(){

  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      leds[i][j].setHue(hue);
    }
  }
}

void setRainbowWithWhite(int stripNum, int numLED){
  setWhite(stripNum);
  for(int i = 0; i < numLED; i++){
    leds[stripNum][i].setHue(hue);
  }
}
