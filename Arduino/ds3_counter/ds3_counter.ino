#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int emberCount = 0;
int medalCount = 0;
int pin = 2;
int emberPin = 7;
int medalPin = 4;
int resetPin = 3;

unsigned long previousMillis = 0;  // Proměnná pro ukládání času posledního čtení tlačítka
const long interval = 500;         // Interval pro kontrolu tlačítek (v milisekundách)

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  for (pin; pin <= 12; pin++) {
    pinMode(pin, INPUT);
  }
  pinMode(emberPin, INPUT);
  pinMode(medalPin, INPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Embers:");
  lcd.setCursor(8, 0);
  lcd.print(emberCount);
  lcd.setCursor(0, 1);
  lcd.print("Covenant:");
  lcd.setCursor(10, 1);
  lcd.print(medalCount);
  unsigned long currentMillis = millis();  // Získání aktuálního času
  // čte medalCount
  if (digitalRead(medalPin) == HIGH && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    medalCount = medalCount + 1;
  }
  // čte embery
  if (digitalRead(emberPin) == HIGH && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    emberCount = emberCount + 1;
  }
  // smaže displej a nastaví hodnoty na 0
  if (digitalRead(resetPin) == HIGH && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    lcd.clear();
    medalCount = 0;
    
    emberCount = 0;
  }
}
