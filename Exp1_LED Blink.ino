const int ledPin=19;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin,HIGH);
  Serial.println("ON");
  delay(1000);
  digitalWrite(ledPin,LOW);
  Serial.println("OFF");
  delay(1000);
}
