#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#include "WS2812FX.h"
/*
IR Receiver datasheet
  // předělat celý na ws2812fx ✅
  // může se lišit podle ovladače apod.
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

const int IR_PIN = 12;
IRrecv IR(IR_PIN);
int speed = 100;
int effectBrightness = 0;

#define LED_PIN 2
#define LED_COUNT 60

//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
WS2812FX ws2812fx(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //strip setup
  Serial.begin(9600);
  IR.enableIRIn();
  //  strip.begin();
  //  strip.setBrightness(brightness);
  //ws2812fx setup
  ws2812fx.init();
  ws2812fx.setBrightness(effectBrightness);
  ws2812fx.setColor(WHITE);
}

void loop() {
  receiveIR();
  if (IR.isIdle()) {
      ws2812fx.service();
  }

}

void receiveIR() {
  if (IR.decode()) {

    unsigned long decodedIRData = IR.decodedIRData.decodedRawData;  // zjednodušení čitelnosti
    Serial.println(decodedIRData, HEX);
    if (decodedIRData == 0xBA45FF00) {  // CH- vypnutí LED pásku
      ws2812fx.stop();
      ws2812fx.setBrightness(0);
    }

    if (decodedIRData == 0xEA15FF00) {  // + zvýšení jasu efektu
      effectBrightness = effectBrightness + 63;
      Serial.println(effectBrightness);
      ws2812fx.setBrightness(effectBrightness);
      if (effectBrightness > 253) {
        effectBrightness = 253;
        Serial.println("Effekt:" + effectBrightness);
        ws2812fx.setBrightness(effectBrightness);
      }

    }  // end +  zvyšování jasu

    if (decodedIRData == 0xBF40FF00) {  // + zvýšení rychlosti (speed)
      speed = speed + 100;
      Serial.println(speed);
      ws2812fx.setSpeed(speed);
      if (speed > 1000) {
        speed = 1000;
        Serial.println("Effekt:" + speed);
        ws2812fx.setSpeed(speed);
      }

    }  // end +  zvyšování rycjlosti

    if (decodedIRData == 0xBB44FF00) {  // + zvýšení rychlosti (speed)
      speed = speed - 100;
      Serial.println(speed);
      ws2812fx.setSpeed(speed);
      if (speed < 100) {
        speed = 101;
        Serial.println("Effekt:" + speed);
        ws2812fx.setSpeed(speed);
      }
    }

    if (decodedIRData == 0xF807FF00) {  // - snížení jasu efektu
      effectBrightness = effectBrightness - 63;
      Serial.println(effectBrightness);
      ws2812fx.setBrightness(effectBrightness);
      if (effectBrightness < 63) {
        effectBrightness = 64;
        Serial.println("Effekt: " + effectBrightness);
        ws2812fx.setBrightness(effectBrightness);
      }
    }
/*
    if (decodedIRData == 0xEA15FF00) {  // + zvýšení jasu norm. barvy
      brightness = brightness + 63;
      Serial.println(brightness);
      strip.setBrightness(brightness);
      strip.show();
      if (brightness > 253) {
        brightness = 253;
        Serial.println(brightness);
        strip.setBrightness(brightness);
        strip.show();
      }

    }  // end +  zvyšování jasu

    if (decodedIRData == 0xF807FF00) {  // - snížení jasu norm. barvy
      brightness = brightness - 63;
      Serial.println(brightness);
      strip.setBrightness(brightness);
      strip.show();
      if (brightness < 63) {
        brightness = 64;
        Serial.println(brightness);
        strip.setBrightness(brightness);
        strip.show();
      }

    }  // end - snižování jasu
*/
    // funguje STATIC ch
    if (decodedIRData == 0xB946FF00) {  // CH
      effectBrightness = 64;
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setMode(FX_MODE_STATIC);
      ws2812fx.start();
    }  //
    // COMET ch+
    if (decodedIRData == 0xB847FF00) {  // CH+
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setSpeed(speed);
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setMode(FX_MODE_COMET);
      ws2812fx.start();
    }
    //FIREWORKS PAUSE
    if (decodedIRData == 0xBC43FF00) {  // PAUSE
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setSpeed(speed);
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setMode(FX_MODE_FIREWORKS);
      ws2812fx.start();
    }
    //FADE EQ
    if (decodedIRData == 0xF609FF00) {  // EQ
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setSpeed(speed);
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setMode(FX_MODE_FADE);
      ws2812fx.start();
    }
    //COLORWIPE FOL+
    if (decodedIRData == 0xF20DFF00) {  // FOL+
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setSpeed(speed);
      ws2812fx.setMode(FX_MODE_COLOR_WIPE_INV);
      ws2812fx.start();
    }
    //LARSONN SCANNER FOL-
    if (decodedIRData == 0xE619FF00) {  // FOL-
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setSpeed(speed);
      ws2812fx.setMode(FX_MODE_LARSON_SCANNER);
      ws2812fx.start();
    }
    //TWINKLE 0
    if (decodedIRData == 0xE916FF00) {  // 0
      effectBrightness = 64;
      speed = 100;
      ws2812fx.setBrightness(effectBrightness);
      ws2812fx.setSpeed(speed);
      ws2812fx.setMode(FX_MODE_THEATER_CHASE);
      ws2812fx.start();
    }

    if (decodedIRData == 0xF30CFF00) {  // 1
      ws2812fx.setColor(WHITE);
      ws2812fx.start();
    }

    if (decodedIRData == 0xE718FF00) {  // 2
      ws2812fx.setColor(RED);
      ws2812fx.start();
    }

    if (decodedIRData == 0xA15EFF00) {  // 3
      ws2812fx.setColor(GREEN);
      ws2812fx.start();
    }

    if (decodedIRData == 0xF708FF00) {  // 4
      ws2812fx.setColor(BLUE);
      ws2812fx.start();
    }

    if (decodedIRData == 0xE31CFF00) {  // 5
      ws2812fx.setColor(ORANGE);
      ws2812fx.start();
    }

    if (decodedIRData == 0xA55AFF00) {  // 6
      ws2812fx.setColor(YELLOW);
      ws2812fx.start();
    }

    if (decodedIRData == 0xBD42FF00) {  // 7
      ws2812fx.setColor(CYAN);
      ws2812fx.start();
    }

    if (decodedIRData == 0xAD52FF00) {  // 8
      ws2812fx.setColor(PURPLE);
      ws2812fx.start();
    }

    if (decodedIRData == 0xB54AFF00) {  // 9
      ws2812fx.setColor(MAGENTA);
      ws2812fx.start();
    }

    IR.resume();
    delay(20);
  }
}
