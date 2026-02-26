int led = 13;
int count = 0;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {

  if (count == 0) {
  digitalWrite(led, LOW);
  delay(200);
  }

  count = count + 1;

  if (count == 2) {
  count = 0;
  digitalWrite(led, HIGH);
  delay(200);
  }
}
