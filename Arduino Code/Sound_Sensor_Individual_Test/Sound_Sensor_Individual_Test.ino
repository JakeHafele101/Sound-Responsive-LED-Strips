                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     #include <FastLED.h>

#define SOUND_ANALOG 23 //A0
#define LED_STRIP_1 2

#define THRESHHOLD 65
#define LED_WAIT 100

#define NUM_LEDS 10
#define BRIGHTNESS 200
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

int hue = 1;
boolean isHueIncreasing = true;

int hasChangedCount = 0;
boolean hasChanged = false;

int rainbowNum = 1;

void setup() {
  delay(3000); // power-up safety delay
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_STRIP_1, COLOR_ORDER>(leds, NUM_LEDS);
  pinMode(SOUND_ANALOG, INPUT);
  FastLED.setBrightness(BRIGHTNESS);

}

void loop() {
  int sound = analogRead(SOUND_ANALOG);
  Serial.print(sound);
  Serial.print("\n");

//  if(sound >= 130 && sound <= 139){
//    Serial.print(sound);
//    Serial.print("\n");
//  }

  
}
