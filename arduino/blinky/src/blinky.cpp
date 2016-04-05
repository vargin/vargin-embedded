#include "Arduino.h"

// Most Arduino boards already have a LED attached to pin 13 on the board itself
#define LED_PIN 13

struct DelayType {
  uint32_t high;
  uint32_t low;
};

DelayType ledDelay;

void setup() {
  ledDelay.high = 1000;
  ledDelay.low = 1000;
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(ledDelay.high);
  digitalWrite(LED_PIN, LOW);
  delay(ledDelay.low);
}