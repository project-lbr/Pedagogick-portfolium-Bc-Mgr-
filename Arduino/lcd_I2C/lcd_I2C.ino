#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 6 // definuje délku hesla 5

int signalPin = 12; // relé na výstupu 12

char Data[Password_Length]; 
char Master[Password_Length] = "00*00";     // heslo
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char mapaKlaves[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte radky[ROWS] = {9, 8, 7, 6};    // nastavuje piny řádků
byte sloupce[COLS] = {5, 4, 3, 2};  // nastavuje piny sloupců

Keypad customKeypad = Keypad(makeKeymap(mapaKlaves), radky, sloupce, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // (adresa i2c, sloupce, radky)

void setup(){
  lcd.begin(); 
  lcd.backlight();  // nastavuje podsvícení
  pinMode(signalPin, OUTPUT); // nastaví pin 12 na OUTPUT 
}

void loop(){
  
  lcd.setCursor(0,0);
  lcd.print("Zadejte heslo:");

  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){  // porovnává zadané heslo s master heslem
      lcd.print("SPRAVNE");
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW);
      }
    else{
      lcd.print("SPATNE");
      delay(1000);
      }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}

