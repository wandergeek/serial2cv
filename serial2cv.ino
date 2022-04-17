#include <FastLED.h>
//#include "flasher.ino"

int outputs[] = {A2,A1,A0};

#define NUM_LEDS 1
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB::Red, CRGB::Yellow, CRGB::Blue};
int blinkMillis = 500; //time to stay on for
int blinkState = LOW;
int startBlinkMillis; //track time that blink started



void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  startUpBlink();
  Serial.print("serial2cv init complete");
}

void loop() {
    while (Serial.available() > 0) {
      byte outputID = Serial.parseInt();
      triggerGate(outputID);
      blinkLED(outputID);
  }
   updateLED();
}

void triggerGate(int outputID) {
  analogWrite(outputs[outputID], 255);
  delay(1);
  analogWrite(outputs[outputID], 0);
}

void blinkLED(int outputID) {
    startBlinkMillis = millis();
    blinkState = HIGH;
    leds[0] = colors[outputID];
    FastLED.show();
}

void updateLED() {
  if (blinkState == LOW) {
    return;
  }

  if(millis() - startBlinkMillis >= blinkMillis) {
    leds[0] = CRGB::Black;
    FastLED.show();
  }
}

void startUpBlink() {
  for(int i=0;i<3; i++) {
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(100);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(100);
  }
} 

