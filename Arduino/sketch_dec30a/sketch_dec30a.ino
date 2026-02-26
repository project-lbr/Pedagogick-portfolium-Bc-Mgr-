#include <avr/io.h>
#include <avr/interrupt.h>

const int ledPin = 13; // Definice pinu pro LED diodu

void setup() {
  pinMode(ledPin, OUTPUT); // Nastavení pinu pro LED jako výstup
  noInterrupts(); // Vypnutí přerušení

  // Nastavení časovače Timer 1
  TCCR1A = 0; // Nastavení registru řídícího režimu A na 0
  TCCR1B = 0; // Nastavení registru řídícího režimu B na 0
  TCNT1 = 0; // Nastavení počáteční hodnoty časovače na 0

  // Nastavení časovače pro generování přerušení každou sekundu
  OCR1A = 15624; // Nastavení hodnoty pro přerušení každou sekundu (při 16 MHz)
  TCCR1B |= (1 << WGM12); // Nastavení režimu CTC (Clear Timer on Compare Match)
  TCCR1B |= (1 << CS12) | (1 << CS10); // Nastavení předděličky na 1024
  TIMSK1 |= (1 << OCIE1A); // Povolení přerušení pro Timer 1

  interrupts(); // Zapnutí přerušení
}

void loop() {
  // Hlavní smyčka
}

// Obsluha přerušení časovače Timer 1
ISR(TIMER1_COMPA_vect) {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Přepnutí stavu LED diody
}
