
void setup() {
  // put your setup code here, to run once:
  pinMode(SPEAKER,OUTPUT);
  digitalWrite(SPEAKER,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(SPEAKER,HIGH);
delay(20);
digitalWrite(SPEAKER,LOW);
delay(5000);
}
