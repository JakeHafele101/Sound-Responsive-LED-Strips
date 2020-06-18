#define LED_PIN 23

int ledState = LOW;
long previousMillis = 0;
long interval = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(LED_PIN, ledState);
  }
}
