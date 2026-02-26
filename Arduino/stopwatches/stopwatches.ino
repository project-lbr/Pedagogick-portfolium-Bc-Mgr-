#include <virtuabotixRTC.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

int reset = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2);
//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8

virtuabotixRTC myRTC(6, 7, 8); //If you change the wiring change the pins here also


void setup() {

  lcd.begin (16,2); //Initialize the LCD
  lcd.setBacklight(HIGH);
  myRTC.setDS1302Time(15, 31, 15, 5, 12, 1, 2018);
  pinMode(reset, INPUT);
 
}

void loop() {
 lcd.clear(); //Here after clearing the LCD we take the time from the module and print it on the screen with usual LCD functions
 myRTC.updateTime();
 lcd.setCursor(0,0);
 lcd.print(myRTC.dayofmonth);
 lcd.print("/");
 lcd.print(myRTC.month);
 lcd.print("/");
 lcd.print(myRTC.year);
 lcd.setCursor(0,1);
 lcd.print(myRTC.hours);
 lcd.print(":");
 lcd.print(myRTC.minutes);
 lcd.print(":");
 lcd.print(myRTC.seconds);
 delay(1000);

  if (digitalRead(reset) == 0) {
   myRTC.setDS1302Time(0, 0, 0, 7, 25, 2, 2024);
  }

}
