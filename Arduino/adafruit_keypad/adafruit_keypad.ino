#include <Adafruit_NeoPixel.h>
#include "Adafruit_Keypad.h"
#include "Keyboard.h"
bool ledsOn = false;
bool ledsOn2 = false;
#define pinDIN 3
#define pocetLED 8
Adafruit_NeoPixel rgbWS = Adafruit_NeoPixel(pocetLED, pinDIN, NEO_GRB + NEO_KHZ800);
unsigned long prevTime = 0;
const long interval = 120000;
unsigned long prevTime2 = 0;
const long interval2 = 120000;


const byte ROWS = 4; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},  
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 10, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  customKeypad.begin();
  Keyboard.begin();
  rgbWS.begin();
}
  
void loop() {
  // put your main code here, to run repeatedly:
  customKeypad.tick();

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


  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
   // Serial.print((char)e.bit.KEY);
  if ((char)e.bit.KEY == '1') {
  if(e.bit.EVENT == KEY_JUST_PRESSED){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_1);
    Keyboard.releaseAll();
 if (!ledsOn) {
          // Rozsvítíme LED pásky
          nastavRGB(64, 0, 0, 1);
          nastavRGB(64, 0, 0, 2);
          // Nastavíme stav LED pásků na zapnutý
          ledsOn = true;
        } else { // Pokud jsou LED pásky momentálně rozsvíceny, zhasneme je
          // Zhasneme LED pásky
          nastavRGB(0, 0, 0, 1);
          nastavRGB(0, 0, 0, 2);
          // Nastavíme stav LED pásků na vypnutý
          ledsOn = false;
        }
      }
  }


if ((char)e.bit.KEY == '2') {
  if(e.bit.EVENT == KEY_JUST_PRESSED) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_2);
    Keyboard.releaseAll();
    nastavRGB(0, 122, 0, 3);
    nastavRGB(0, 122, 0, 4);
    delay(50);
    nastavRGB(0, 0, 0, 3);
    nastavRGB(0, 0, 0, 4);   
  }

}
if ((char)e.bit.KEY == '3') {
  if(e.bit.EVENT == KEY_JUST_PRESSED) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_3);
    Keyboard.releaseAll();
    nastavRGB(0, 0, 122, 5);
    nastavRGB(0, 0, 122, 6);
    delay(50);
    nastavRGB(0, 0, 0, 5);
    nastavRGB(0, 0, 0, 6); 
  }
}
  if ((char)e.bit.KEY == '4') {
  if(e.bit.EVENT == KEY_JUST_PRESSED){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_KP_0);
    Keyboard.releaseAll();
 if (!ledsOn2) {
          // Rozsvítíme LED pásky
          nastavRGB(64, 0, 0, 7);
          nastavRGB(64, 0, 0, 8);
          // Nastavíme stav LED pásků na zapnutý
          ledsOn2 = true;
        } else { // Pokud jsou LED pásky momentálně rozsvíceny, zhasneme je
          // Zhasneme LED pásky
          nastavRGB(0, 0, 0, 7);
          nastavRGB(0, 0, 0, 8);
          // Nastavíme stav LED pásků na vypnutý
          ledsOn2 = false;
        }
      }
  }
  }
  delay(50);
}

void nastavRGB (byte r, byte g, byte b, int cislo) {
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
