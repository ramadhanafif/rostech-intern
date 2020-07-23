void setup() {
  // put your setup code here, to run once:
  pinMode(PC13,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("adasda");
  digitalWrite(PC13,0);
  delay(1500);
  digitalWrite(PC13,1);
  delay(10);
}
