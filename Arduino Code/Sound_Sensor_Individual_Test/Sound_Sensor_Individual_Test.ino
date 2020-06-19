#define SOUND_ANALOG 23 //A0
#define LED_PIN 2

#define SENSITIVITY 136

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SOUND_ANALOG, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorAnalog = analogRead(SOUND_ANALOG);
  int ledState = LOW;

  Serial.print(sensorAnalog);
  Serial.print("\n");
  if(sensorAnalog > SENSITIVITY + 10){
    Serial.print(sensorAnalog);
    Serial.print("\n");
  }

    if(sensorAnalog > SENSITIVITY + 1 || sensorAnalog < SENSITIVITY - 1 && ledState != HIGH){
      ledState = HIGH;
      digitalWrite(LED_PIN, ledState);
    }
    else{
      ledState = LOW;
      digitalWrite(LED_PIN, ledState);
    }

    delay(100);
}
