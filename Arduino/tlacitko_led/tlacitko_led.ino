#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.begin();
  lcd.backlight();
//  lcd.begin();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Ahoj svete!!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("nasrat");
  delay(1000);
}

