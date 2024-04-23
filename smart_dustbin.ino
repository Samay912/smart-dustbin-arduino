// Pin definitions
const int gasSensorPin = A0;    // Analog pin for gas sensor
const int flameSensorPin = 2;   // Digital pin for flame sensor
const int ultrasonicTrigPin = 3; // Digital pin for ultrasonic sensor's trigger
const int ultrasonicEchoPin = 4; // Digital pin for ultrasonic sensor's echo
const int gasLedPin = 5;        // Digital pin for gas sensor LED
const int flameLedPin = 6;      // Digital pin for flame sensor LED
const int ultrasonicLedPin = 7; // Digital pin for ultrasonic sensor LED

// Constants
const int ultrasonicThreshold = 4; // Threshold distance for ultrasonic sensor in cm

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(flameSensorPin, INPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(gasLedPin, OUTPUT);
  pinMode(flameLedPin, OUTPUT);
  pinMode(ultrasonicLedPin, OUTPUT);
}

void loop() {
  // Read sensor values
  int gasValue = analogRead(gasSensorPin);
  int flameValue = digitalRead(flameSensorPin);
  int ultrasonicDistance = measureDistance();

  // Check gas sensor
  if (gasValue > 35) { // Adjust this threshold as per your sensor's sensitivity
    digitalWrite(gasLedPin, HIGH);
  } else {
    digitalWrite(gasLedPin, LOW);
  }

  // Check flame sensor
  if (flameValue >= 1) {
    digitalWrite(flameLedPin, HIGH);
  } else {
    digitalWrite(flameLedPin, LOW);
  }

  // Check ultrasonic sensor
  if (ultrasonicDistance < ultrasonicThreshold) {
    digitalWrite(ultrasonicLedPin, HIGH);
  } else {
    digitalWrite(ultrasonicLedPin, LOW);
  }

  // Print sensor values for debugging
  Serial.print("Gas Value: ");
  Serial.println(gasValue);
  Serial.print("Flame Value: ");
  Serial.println(flameValue);
  Serial.print("Ultrasonic Distance: ");
  Serial.print(ultrasonicDistance);
  Serial.println(" cm");

  // Delay for stability
  delay(1000);
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  int distance = duration * 0.034 / 2; // Calculate distance in cm
  return distance;
}
