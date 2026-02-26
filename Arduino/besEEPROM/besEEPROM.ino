#include <LiquidCrystal.h>

const int Pin_Rele = A4;
const int rs = 12, en = 11, d7 = 5, d6 = 4, d5 = 3, d4 = 2;
const int pocetRadku = 4;
const int pocetSloupcu = 4;
const int debounceTime = 20;
const int Cteni_Klaves = 0;
const int Kod_OK = 1;
const int Kod_Error = 2;
const long Cas_Upozorneni = 3000;

const char mapaKlaves[pocetRadku][pocetSloupcu] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const int pinyRadku[pocetRadku] = { A3, A2, A1, A0 };
const int pinySloupcu[pocetSloupcu] = { 7, 8, 9, 10 };

int program_status = Cteni_Klaves;
const byte spravnyKod[4] = { '1', '2', '3', '4' }; // Zde je vaše heslo

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte kod[4] = { 20, 20, 20, 20 };
unsigned int poradiCislice = 0;
long cas1;

void setup() {
  for (int radek = 0; radek < pocetRadku; radek++) {
    pinMode(pinyRadku[radek], INPUT);
    digitalWrite(pinyRadku[radek], HIGH);
  }
  for (int sloupec = 0; sloupec < pocetSloupcu; sloupec++) {
    pinMode(pinySloupcu[sloupec], OUTPUT);
    digitalWrite(pinySloupcu[sloupec], HIGH);
  }
  pinMode(Pin_Rele, OUTPUT);
  lcd.begin(16, 2);
  vynulovatKod();
  Serial.begin(9600);
}

void loop() {
  if (program_status == Cteni_Klaves) {
    char klavesa = stisknutaKlavesa();
    if (klavesa != 0) {
      if (poradiCislice <= 3 && ((klavesa >= '0' && klavesa <= '9'))) {
        lcd.setCursor(12 + poradiCislice, 0);
        lcd.print(klavesa);
        kod[poradiCislice] = (byte)klavesa;
        poradiCislice++;
      } else if (klavesa == '#') {
        if (porovnatKod()) {
          hlaseni1("     Kod OK");
          program_status = Kod_OK;
          digitalWrite(Pin_Rele, HIGH);
          cas1 = millis();
        } else {
          hlaseni2("Chyba, opakujte", "  zadani kodu!");
          program_status = Kod_Error;
          cas1 = millis();
        }
      } else if (klavesa == '*') {
        vynulovatKod();
      }
    }
  } else if (program_status == Kod_OK || program_status == Kod_Error) {
    if (millis() - cas1 >= Cas_Upozorneni) {
      digitalWrite(Pin_Rele, LOW);
      vynulovatKod();
      program_status = Cteni_Klaves;
    }
  }
}

char stisknutaKlavesa() {
  char key = 0;
  for (int sloupec = 0; sloupec < pocetSloupcu; sloupec++) {
    digitalWrite(pinySloupcu[sloupec], LOW);
    for (int radek = 0; radek < pocetRadku; radek++) {
      if (digitalRead(pinyRadku[radek]) == LOW) {
        delay(debounceTime);
        while (digitalRead(pinyRadku[radek]) == LOW);
        key = mapaKlaves[radek][sloupec];
        // Kontrola, zda je klávesa číslice nebo písmeno A, B, C, D
        if (!((key >= '0' && key <= '9') || (key >= 'A' && key <= 'D'))) {
          key = 0; // Pokud klávesa není číslice ani písmeno A, B, C, D, nastaví se na 0
        }
      }
    }
    digitalWrite(pinySloupcu[sloupec], HIGH);
  }
  return key;
}


void hlaseni(int sloupec, int radek, String zprava, bool mazat_display) {
  if (mazat_display) {
    lcd.clear();
  }
  lcd.setCursor(sloupec, radek);
  lcd.print(zprava);
  lcd.noCursor();
}

void hlaseni1(String zprava) {
  hlaseni(0, 0, zprava, true);
}

void hlaseni2(String zprava1, String zprava2) {
  hlaseni(0, 0, zprava1, true);
  hlaseni(0, 1, zprava2, false);
}

void vynulovatKod() {
  poradiCislice = 0;
  for (int i = 0; i <= 3; i++) {
    kod[i] = 'n';
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zadejte kod:");
  lcd.setCursor(0, 1);
  lcd.print("# Enter  * Clear");
  lcd.setCursor(12 + poradiCislice, 0);
  lcd.cursor();
}

bool porovnatKod() {
  for (int i = 0; i < 4; i++) {
    if (spravnyKod[i] != kod[i]) {
      return false;
    }
  }
  return true;
}
