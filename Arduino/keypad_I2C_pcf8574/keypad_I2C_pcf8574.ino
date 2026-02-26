//
//    FILE: I2Ckeypad_demo01.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/I2CKeyPad
//
//  PCF8574
//    pin p0-p3 rows
//    pin p4-p7 columns
//  4x4 or smaller keypad.
#include <Adafruit_NeoPixel.h>
#include "Wire.h"
#include "I2CKeyPad.h"
#include "Keyboard.h"
#define pinDIN 3
#define pocetLED 8
Adafruit_NeoPixel rgbWS = Adafruit_NeoPixel(pocetLED, pinDIN, NEO_GRB + NEO_KHZ800);
const uint8_t KEYPAD_ADDRESS = 0x20;
int jas = 0;

I2CKeyPad keyPad(KEYPAD_ADDRESS);

bool ledsOn = false;
bool ledsOn2 = false;
unsigned long prevTime = 0;
const long interval = 120000;
unsigned long prevTime2 = 0;
const long interval2 = 120000;

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  Keyboard.begin();
  rgbWS.begin();
  // rgbWS.setBrightness(50);
  Wire.begin();
  Wire.setClock(400000);
  if (keyPad.begin() == false) {
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1)
      ;
  }
}


void loop() {

  unsigned long currentMillis = millis();
  unsigned long currentMillis2 = millis();
  if (currentMillis - prevTime >= interval) {
    prevTime = currentMillis;
    // Zhasneme LED pásky pouze pokud jsou momentálně zapnuty
    if (ledsOn) {
      nastavRGB(0, 0, 0, 1);
      nastavRGB(0, 0, 0, 2);
      // Nastavíme stav LED pásků na vypnutý
      ledsOn = false;
    }
  }
  if (currentMillis2 - prevTime2 >= interval2) {
    prevTime2 = currentMillis2;
    // Zhasneme LED pásky pouze pokud jsou momentálně zapnuty
    if (ledsOn2) {
      nastavRGB(0, 0, 0, 7);
      nastavRGB(0, 0, 0, 8);
      // Nastavíme stav LED pásků na vypnutý
      ledsOn2 = false;
    }
  }

  char keys[] = "123A456B789C*0#DNF";  //  N = NoKey, F = Fail
  uint8_t index = keyPad.getKey();

  if (keys[index] == '1') {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_1);
    Keyboard.releaseAll();
    delay(200);
    if (!ledsOn) {
      // Rozsvítíme LED pásky
      nastavRGB(64, 0, 0, 1);
      nastavRGB(64, 0, 0, 2);
      // Nastavíme stav LED pásků na zapnutý
      ledsOn = true;
    } else {  // Pokud jsou LED pásky momentálně rozsvíceny, zhasneme je
      // Zhasneme LED pásky
      nastavRGB(0, 0, 0, 1);
      nastavRGB(0, 0, 0, 2);
      // Nastavíme stav LED pásků na vypnutý
      ledsOn = false;
    }
  }

  if (keys[index] == '4') {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_0);
    Keyboard.releaseAll();
    delay(200);
    if (!ledsOn) {
      // Rozsvítíme LED pásky
      nastavRGB(64, 0, 0, 7);
      nastavRGB(64, 0, 0, 8);
      // Nastavíme stav LED pásků na zapnutý
      ledsOn = true;
    } else {  // Pokud jsou LED pásky momentálně rozsvíceny, zhasneme je
      // Zhasneme LED pásky
      nastavRGB(0, 0, 0, 7);
      nastavRGB(0, 0, 0, 8);
      // Nastavíme stav LED pásků na vypnutý
      ledsOn = false;
    }
  }

  if (keys[index] == '2') {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_2);
    Keyboard.releaseAll();
    nastavRGB(0, 122, 0, 3);
    nastavRGB(0, 122, 0, 4);
    delay(150);
    nastavRGB(0, 0, 0, 3);
    nastavRGB(0, 0, 0, 4);
  }

  if (keys[index] == '3') {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_3);
    Keyboard.releaseAll();
    nastavRGB(0, 0, 122, 5);
    nastavRGB(0, 0, 122, 6);
    delay(150);
    nastavRGB(0, 0, 0, 5);
    nastavRGB(0, 0, 0, 6);
  }

}  // konec loopu

void nastavRGB(byte r, byte g, byte b, int cislo) {
  // vytvoření proměnné pro ukládání barev
  uint32_t barva;
  // načtení barvy do proměnné
  barva = rgbWS.Color(r, g, b);
  // nastavení barvy pro danou LED diodu,
  // číslo má pořadí od nuly
  rgbWS.setPixelColor(cislo - 1, barva);
  // aktualizace barev na všech modulech
  rgbWS.show();
}
//  -- END OF FILE --
