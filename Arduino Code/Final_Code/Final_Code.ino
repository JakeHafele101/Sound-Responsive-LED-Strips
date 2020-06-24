#include <FastLED.h>
  
#define SOUND_GATE 13
#define LED_STRIP_1 2
#define LED_STRIP_2 3
#define LED_STRIP_3 4
#define LED_STRIP_4 5
#define LED_STRIP_5 6
#define LED_STRIP_6 7
#define LED_STRIP_7 8
#define LED_STRIP_8 9
#define LED_STRIP_9 10

#define THRESHHOLD 25

#define NUM_STRIPS 9
#define NUM_LEDS 10
#define BRIGHTNESS 50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_STRIPS][NUM_LEDS];

#define LED_WAIT 25
#define HUE_WAIT 5

int hue = 1;
boolean isHueIncreasing = true;

int hasChangedCount = 0;
boolean hasChanged = false;

int rainbowNum[NUM_STRIPS];

void setup() {
  delay(3000); // power-up safety delay
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_STRIP_1, COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_2, COLOR_ORDER>(leds[1], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_3, COLOR_ORDER>(leds[2], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_4, COLOR_ORDER>(leds[3], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_5, COLOR_ORDER>(leds[4], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_6, COLOR_ORDER>(leds[5], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_7, COLOR_ORDER>(leds[6], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_8, COLOR_ORDER>(leds[7], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, LED_STRIP_9, COLOR_ORDER>(leds[8], NUM_LEDS);
  pinMode(SOUND_GATE, INPUT);

  FastLED.setBrightness(BRIGHTNESS);

  for(int i = 0; i < NUM_STRIPS; i++){ //Sets rainbow LED to 1 for first loop of strip
    rainbowNum[i] = 1;
  }
}

void loop() {
  int gate = digitalRead(SOUND_GATE);

  Serial.print(gate);
  Serial.print("\n");

  if(millis() % HUE_WAIT == 0){
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
  }

  if(!hasChanged){
    if(gate){
      for(int i = 0; i < NUM_STRIPS; i++){
        rainbowNum[i] = rainbowNum[i] + 2;
      }
    }
    else{
      for(int i = 0; i < NUM_STRIPS; i++){
        rainbowNum[i]--;
      }
    }
    hasChanged = true;
    hasChangedCount = 0;
  }

  for(int i = 0; i < NUM_STRIPS; i++){
    if(rainbowNum[i] < 1){
      rainbowNum[i] = 1;
    }
    if(rainbowNum[i] > NUM_LEDS){
      rainbowNum[i] = NUM_LEDS;
    }
    setRainbowWithWhite(i, rainbowNum[i]);
  }

  if(hasChanged){
    hasChangedCount++;
  }
  if(hasChangedCount > LED_WAIT){
    hasChangedCount = 0;
    hasChanged = false;
  }

  FastLED.show();
  
}

void setWhite(int stripNum){
  for(int j = 0; j < NUM_LEDS; j++){
    leds[stripNum][j] = CRGB::White;
  }
}

void setRainbowWithWhite(int stripNum, int numLED){
  setWhite(stripNum);
  for(int i = 0; i < numLED; i++){
    leds[stripNum][i].setHue(hue);
  }
}
