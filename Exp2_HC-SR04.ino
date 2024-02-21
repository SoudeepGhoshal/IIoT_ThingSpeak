const int trigPin = 26;
const int echoPin = 27;
const int ledPin = 14;
long duration;
float distance;  // Change the data type to float
int brightness;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor

  brightness = map(distance, 5, 50, 255, 0);
  brightness = constrain(brightness, 0, 255);
  analogWrite(ledPin, brightness);

  /*if (distance<=10){
    digitalWrite(ledPin, HIGH);
    Serial.println("ON");
  }
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("OFF");
  }*/

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000); // Add a delay to make the output readable
}
