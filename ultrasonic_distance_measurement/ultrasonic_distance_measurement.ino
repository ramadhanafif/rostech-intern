#define trig PA6
#define echo PA5


void setup() {
  // put your setup code here, to run once:
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int range = read_dist();

  if ((range > 400) | (range < 2))
    Serial.println("Measurement Error");
    else
      Serial.println(range);
      delay(1500);
    }

// function read distance from HC-SR04
int read_dist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Get echo SRF04
  int distance = pulseIn(echoPin, HIGH);
  // Distance calibration to centimeter
  distance = distance / 58;
  return distance;
}
