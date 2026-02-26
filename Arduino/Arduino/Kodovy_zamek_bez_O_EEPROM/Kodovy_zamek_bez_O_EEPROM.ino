// kod jsou pouze cislice !!

#include <LiquidCrystal.h>
#include <EEPROM.h>

const int Pin_Rele=A4;
const int rs = 12, en = 11, d7 = 5, d6 = 4, d5 = 3, d4 = 2;
const int pocetRadku = 4; 
const int pocetSloupcu = 4;
const int debounceTime = 20;
const int Cteni_Klaves=0;     // konstanty stavu programu
const int Kod_OK=1;
const int Kod_Error=2;
const int Uloz_kod=3;
const int Potvrzeni_ulozeni=4;
const long Cas_Upozorneni=3000; // cas hlaseni v ms

const char mapaKlaves[pocetRadku][pocetSloupcu] = {
                                            { '1', '2', '3', 'A' } ,
                                            { '4', '5', '6', 'B' } ,
                                            { '7', '8', '9','C' } ,
                                            { '*', '0', '#','D' }
                                            };

const int pinyRadku[pocetRadku] = {  A3, A2, A1, A0 }; 
const int pinySloupcu[pocetSloupcu] = { 7, 8, 9, 10 };

int program_status=Cteni_Klaves;
byte spravnyKod[4]={0, 0, 0, 0};
byte kod[4]={20, 20, 20, 20};
unsigned int poradiCislice=0;
long cas1; // pocatecni cas hlaseni


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// heslo v EEPROM na adresach 0,1,2,3
// jestli je zadane heslo je na adrese 4=1
int adresaHeslo=4;
byte zadaneHeslo=1;  


void setup() {
  for (int radek = 0; radek < pocetRadku; radek++)
    {
        pinMode(pinyRadku[radek], INPUT); // Set row pins as input
        digitalWrite(pinyRadku[radek], HIGH); // turn on Pull-ups
      }
  for (int sloupec = 0; sloupec < pocetSloupcu; sloupec++)
      {
        pinMode(pinySloupcu[sloupec], OUTPUT); // Set column pins as outputs for writing
        digitalWrite(pinySloupcu[sloupec], HIGH); // Make all columns inactive
    }
    pinMode(Pin_Rele, OUTPUT);
  // nastaveni poctu radku a sloupcu
  lcd.begin(16, 2);
  vynulovatKod();
  byte jeHeslo=EEPROM.read(adresaHeslo); // jestli je ulozene heslo v EEPROM
  if (jeHeslo==zadaneHeslo){
      nactiHesloEeprom();
  }
  Serial.begin(9600);
}

void nactiHesloEeprom(){
    for (int i=0;i<4;i++){
            spravnyKod[i]=EEPROM.read(i);
    }
}

void ulozHesloEeprom(){
  for (int i=0;i<4;i++){
            EEPROM.update(i, kod[i]);
  }
  EEPROM.update(adresaHeslo, zadaneHeslo);
}

void loop() {
  if (program_status==Cteni_Klaves){
      char klavesa = stisknutaKlavesa();
      if ( klavesa != 0) { // if the character is not 0 then it's a valid klavesa press
        if (poradiCislice<=3 && ((klavesa>='0' && klavesa<='9') )){
          lcd.setCursor(12+poradiCislice, 0);
          lcd.print(klavesa);
          kod[poradiCislice]=(byte)klavesa-48;
          poradiCislice++;
        }
        else if (klavesa=='D'){ //uloz novy kod
          program_status=Uloz_kod;          
        }
        else if (klavesa=='*'){
          vynulovatKod();
        }
        else if (klavesa=='#'){
          if (porovnatKod()){
            hlaseni1("     Kod OK");
            program_status=Kod_OK;
            digitalWrite(Pin_Rele, HIGH);
            cas1=millis();
          }
          else{ // chybny kod
            hlaseni2("Chyba, opakujte", "  zadani kodu!");
            program_status=Kod_Error;
            cas1=millis();
          }
        }
      }
   }
   else if (program_status==Kod_OK || program_status==Kod_Error){
    if (millis()-cas1>=Cas_Upozorneni){
      digitalWrite(Pin_Rele, LOW);
      vynulovatKod();
      program_status=Cteni_Klaves;
    }
   }
  else if (program_status==Uloz_kod){
    hlaseni2("  Ulozit kod?","   Stiskni >A<");
    program_status=Potvrzeni_ulozeni;
  }
  else if (program_status==Potvrzeni_ulozeni){
    char klavesa = stisknutaKlavesa();
      if ( klavesa != 0){
        if (klavesa=='A'){
          ulozHesloEeprom();
           for (int i=0;i<4;i++){
            spravnyKod[i]=kod[i];
          }
        }
        program_status=Cteni_Klaves;
        vynulovatKod();
      }
  }
}

char stisknutaKlavesa() {
    char key = 0; // 0 indicates no key pressed
    for (int sloupec = 0; sloupec < pocetSloupcu; sloupec++)  {
      digitalWrite(pinySloupcu[sloupec], LOW); // na sloupci se nastaví 0
      for (int radek = 0; radek < pocetRadku; radek++) // prochazi se radky a hleda se 0
      {
        if (digitalRead(pinyRadku[radek]) == LOW) // 0 se nasla
        {
          delay(debounceTime); // debounce
          while (digitalRead(pinyRadku[radek]) == LOW); // ceka dokud je klavesa stisknuta
          key = mapaKlaves[radek][sloupec]; // ulozi se znak klavesy
        }
      }
      digitalWrite(pinySloupcu[sloupec], HIGH); // na sloupci se nastavi 1
    }
    return key; // vraci znak nebo 0, kdyz neni nic stisknuto
}

void hlaseni(int sloupec, int radek, String zprava, bool mazat_display){
  if (mazat_display){
    lcd.clear();
  }
  lcd.setCursor(sloupec, radek);
  lcd.print(zprava);
  lcd.noCursor();
}

void hlaseni1(String zprava){
  hlaseni(0, 0, zprava, true);
}

void hlaseni2(String zprava1, String zprava2){
  hlaseni(0, 0, zprava1, true);
  hlaseni(0, 1, zprava2, false);
}

void vynulovatKod(){
  poradiCislice=0;
  for (int i=0;i<=3;i++){
    kod[i]='n';
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zadejte kod:");
  lcd.setCursor(0, 1);
  lcd.print("# Enter  * Clear");
  lcd.setCursor(12+poradiCislice, 0);
  lcd.cursor();
}

 bool porovnatKod(){
  if ( spravnyKod[0]==kod[0] && spravnyKod[1]==kod[1] && spravnyKod[2]==kod[2] &&spravnyKod[3]==kod[3]){
    return true;
  }
  else{
    return false;
  }
 }
