int i = 2;

void setup() {
  // put your setup code here, to run once:
  for(int pin = 2; pin <=6; pin++){
    pinMode(pin,OUTPUT);            // tohle, dá piny na output mode
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 2; i <= 6; i = i+1){
      digitalWrite(i, HIGH);
      delay(100);                   // ledky <-
      digitalWrite(i, LOW);
  }
  for(int i = 6; i >= 2; i = i-1){
      digitalWrite(i, HIGH);
      delay(100);                   // ledky ->
      digitalWrite(i, LOW);
  }
}
