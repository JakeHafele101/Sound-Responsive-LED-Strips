#include <FastLED.h>

#define NUM_LEDS 60
#define LED_PIN 2
#define BRIGHTNESS 255
#define SATURATION 255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
#define RAINBOW_PER_SECOND 50

int hue = 1;
int rainbowCount = 0;
boolean isHueIncreasing = true;

void setup() {
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  Serial.print(hue);
  Serial.print("\n");
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
  setRainbowWithWhite(1);
  FastLED.show();
  delay(1000/UPDATES_PER_SECOND);
}

void setWhite(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
  }
}

void setRainbow(){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i].setHue(hue);
  }
}

void setRainbowWithWhite(int numLED){
  setWhite();
  for(int i = 0; i < numLED; i++){
    leds[i].setHue(hue);
  }
}
