int fotorez = A0; // základní hodnota = 60
int led = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(fotorez, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(fotorez));
  if (analogRead(fotorez) <= 10) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

