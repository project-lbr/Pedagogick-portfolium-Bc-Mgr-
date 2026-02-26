

int thx = 2;
int leave = 3;
int led = 13; 

void setup() {
  // put your setup code here, to run once:
  pinMode(thx, INPUT);
  pinMode(leave, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(thx) == HIGH) {
    digitalWrite(led, HIGH);
  }
}
