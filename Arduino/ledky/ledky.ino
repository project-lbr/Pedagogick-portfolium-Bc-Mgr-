// NeoPixel modul s 8 RGB LED WS2812
// navody.dratek.cz

// připojení potřebné knihovny
#include <Adafruit_NeoPixel.h>
// nastavení propojovacího pinu
#define pinDIN 3
// nastavení počtu LED modulů
#define pocetLED 8
// inicializace LED modulu z knihovny
Adafruit_NeoPixel rgbWS = Adafruit_NeoPixel(pocetLED, pinDIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // zahájení komunikace s LED modulem
  rgbWS.begin();
  // nastavení červené barvy na první LED diodu
  nastavRGB(30, 0  , 0  , 1);
  delay(500);
  // nastavení zelené barvy na druhou LED diodu
  nastavRGB(0  , 30, 0  , 2);
  delay(500);
  // nastavení modré barvy na třetí LED diodu
  nastavRGB(0  , 0  , 30, 3);
  delay(500);
  // nastavení černé barvy na první 3 LED diody = vypnutí
  nastavRGB(0  , 0  , 0  , 1);
  nastavRGB(0  , 0  , 0  , 2);
  nastavRGB(0  , 0  , 0  , 3);
  delay(500);
}
void loop() {
  // pomocí funkce nastavRGB vytvoř náhodnou kombinaci barev
  // a pro každý běh smyčky vyber náhodnou LED diodu,
  // funkce random vytvoří náhodné číslo
  // z rozsahu v závorkách random(min, max-1)
  byte cervena = random(0, 256);
  byte zelena  = random(0, 256);
  byte modra   = random(0, 256);
  byte dioda   = random(1, (pocetLED + 1));
  nastavRGB(cervena, zelena, modra, dioda);
  delay(200);
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