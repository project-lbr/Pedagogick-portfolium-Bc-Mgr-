int pin_led = 13;


void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 14; i++) {  // nastaví piny 2 - 13 na výstup (OUTPUT)
  pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_led, HIGH);    // blikání LED, nastavuje po intervalu 500ms ON/OFF
  delay(500);
  digitalWrite(pin_led, LOW);
  delay(500);
}
