#include <Adafruit_NeoPixel.h>

#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
//  strip.show();
}

void loop() {
  strip.setBrightness(255);
  // put your main code here, to run repeatedly:
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
    strip.show();
    delay(500);
  }

}
