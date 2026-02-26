// NeoPixel modul s 8 RGB LED WS2812
// navody.dratek.cz

// připojení potřebné knihovny
#include <Adafruit_NeoPixel.h>
// nastavení propojovacího pinu
#define pinDIN 6
// nastavení počtu LED modulů
#define pocetLED 8

int potenciometr = A0;
int sensor = 0;
// inicializace LED modulu z knihovny
Adafruit_NeoPixel rgbWS = Adafruit_NeoPixel(pocetLED, pinDIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // zahájení komunikace s LED modulem
  rgbWS.begin();
  Serial.begin(9600);
  nastavRGB(0, 0, 0, 1);
  nastavRGB(0, 0, 0, 2);
  nastavRGB(0, 0, 0, 3);
  nastavRGB(0, 0, 0, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  pinMode(potenciometr, INPUT);
}
void loop() {
  // pomocí funkce nastavRGB vytvoř náhodnou kombinaci barev
  // a pro každý běh smyčky vyber náhodnou LED diodu,
  // funkce random vytvoří náhodné číslo
  // z rozsahu v závorkách random(min, max-1)
  sensor = analogRead(potenciometr);
  Serial.println(sensor);
  if (sensor < 64) {
  nastavRGB(0, 0, 0, 1);
  nastavRGB(0, 0, 0, 2);
  nastavRGB(0, 0, 0, 3);
  nastavRGB(0, 0, 0, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 128) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(0, 0, 0, 2);
  nastavRGB(0, 0, 0, 3);
  nastavRGB(0, 0, 0, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 256) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(0, 0, 0, 3);
  nastavRGB(0, 0, 0, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 384) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(0, 0, 0, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 512) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(64, 64, 64, 4);
  nastavRGB(0, 0, 0, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 640) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(64, 64, 64, 4);
  nastavRGB(64, 64, 64, 5);
  nastavRGB(0, 0, 0, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 768) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(64, 64, 64, 4);
  nastavRGB(64, 64, 64, 5);
  nastavRGB(64, 64, 64, 6);
  nastavRGB(0, 0, 0, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor < 896) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(64, 64, 64, 4);
  nastavRGB(64, 64, 64, 5);
  nastavRGB(64, 64, 64, 6);
  nastavRGB(64, 64, 64, 7);
  nastavRGB(0, 0, 0, 8);
  }
  else if (sensor <= 1024) {
  nastavRGB(64, 64, 64, 1);
  nastavRGB(64, 64, 64, 2);
  nastavRGB(64, 64, 64, 3);
  nastavRGB(64, 64, 64, 4);
  nastavRGB(64, 64, 64, 5);
  nastavRGB(64, 64, 64, 6);
  nastavRGB(64, 64, 64, 7);
  nastavRGB(64, 64, 64, 8);
  }
}
// funkce pro nastavení zadané barvy na zvolenou diodu
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