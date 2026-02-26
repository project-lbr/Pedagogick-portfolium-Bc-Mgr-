#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
/*
IR Receiver 

BA45FF00 - CH-
B946FF00 - CH
B847FF00 - CH+
BB44FF00 - <=
BF40FF00 - =>
BC43FF00 - PAUSE
F807FF00 - -
EA15FF00 - + 
F609FF00 - EQ
E916FF00 - 0
E619FF00 - FOL-
F20DFF00 - FOL+
F30CFF00 - 1
E718FF00 - 2
A15EFF00 - 3
F708FF00 - 4
E31CFF00 - 5
A55AFF00 - 6
BD42FF00 - 7
AD52FF00 - 8
B54AFF00 - 9
*/

// Define the IR receiver pin
const int IR_PIN = 7;
// Define the IR receiver object
IRrecv IR(IR_PIN);
int i = 0;

#define LED_PIN 3
#define LED_COUNT 8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  IR.enableIRIn();
  strip.begin();
  strip.setBrightness(i);
}

void loop() {
  // Check if the IR receiver has received a signal

  for (int led = 0; led < LED_COUNT; led++) {
    strip.setPixelColor(led, (strip.Color(255, 255, 255)));
    strip.show();
  }

  if (IR.decode()) {
    // Print the HEX value of the button press
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    if (IR.decodedIRData.decodedRawData == 0xEA15FF00) {
      i = i + 63;
      Serial.println(i);
      strip.setBrightness(i);
      strip.show();
      if (i > 253) {
      i = 0;
      strip.setBrightness(i);
      strip.show();
      }
    }
    // Reset the IR receiver for the next signal
    IR.resume();
    delay(100);
  }
}