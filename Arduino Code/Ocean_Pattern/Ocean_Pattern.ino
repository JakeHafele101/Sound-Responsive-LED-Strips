#include <FastLED.h>
  
#define LED_STRIP_1 2
#define LED_STRIP_2 3
#define LED_STRIP_3 4
#define LED_STRIP_4 5
#define LED_STRIP_5 6
#define LED_STRIP_6 7
#define LED_STRIP_7 8
#define LED_STRIP_8 9
#define LED_STRIP_9 10

#define NUM_STRIPS 9
#define NUM_LEDS 10
#define BRIGHTNESS 50
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_STRIPS][NUM_LEDS];

#define RAIN_WAIT 100
#define RAIN_FALL 100
#define RAIN_SPREAD 25

int oceanStart = 3;

int raindropY;
int raindropX;
boolean raindropFalling = false;

int spreadY;
int spreadXLeft;
int spreadXRight;
boolean raindropSpreadingLeft = false;
boolean raindropSpreadingRight = false;


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

  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {

  setBackground();
  
  if(!raindropFalling && !raindropSpreadingLeft && !raindropSpreadingRight){
    setRaindrop();
    raindropSpreadShow();
  }

  if(raindropFalling){
    showRaindrop();
    raindropFall();
  }

  if(raindropSpreadingLeft || raindropSpreadingRight){
    raindropSpread();
  }

  if(raindropY <= oceanStart && raindropFalling){
    raindropFalling = false;
    raindropSpreadSet();
  }

  raindropSpreadShow();

  FastLED.show();
  delay(100);
}

void setBackground(){
  for(int i = 0; i < NUM_STRIPS; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      if(j <= oceanStart){
        leds[i][j].setRGB(22, 0, 148); //Ocean Colors
      }
      else {
        leds[i][j].setRGB(142, 220, 246); //Sky Colors
      }
    }
  }

  leds[0][NUM_LEDS - 1].setRGB(248, 232, 0); //Sun colors
  leds[0][NUM_LEDS - 2].setRGB(248, 232, 0);
  leds[1][NUM_LEDS - 1].setRGB(248, 232, 0);
  leds[1][NUM_LEDS - 2].setRGB(248, 232, 0);
  
}

void setRaindrop(){
  raindropY = NUM_LEDS - 1;
  raindropX = random(NUM_STRIPS);
  raindropFalling = true;
}

void showRaindrop(){
  leds[raindropX][raindropY].setRGB(22, 0, 148); //Ocean color
}

void raindropFall(){
  raindropY--;
}

void raindropSpreadSet(){
  spreadY = oceanStart + 1;
  spreadXLeft = raindropX + 1;
  spreadXRight = raindropX - 1;
  
  if(spreadXLeft <= NUM_STRIPS - 1){
    raindropSpreadingLeft = true;
  }
  if(spreadXRight >= 0){
    raindropSpreadingRight = true;
  }
}

void raindropSpread(){
  if(raindropSpreadingLeft){
    spreadXLeft++;
  }
  if(raindropSpreadingRight){
    spreadXRight--;
  }
  if(spreadXLeft > NUM_STRIPS){
    raindropSpreadingLeft = false;
  }
  if(spreadXRight < 0){
    raindropSpreadingRight = false;
  }
}

void raindropSpreadShow(){
  if(raindropSpreadingLeft){
    leds[spreadXLeft][spreadY].setRGB(22, 0, 148); //Ocean color
  }
  if(raindropSpreadingRight){
    leds[spreadXRight][spreadY].setRGB(22, 0, 148); //Ocean color
  }
}
