#include <Servo.h>

// Pin configuration
const int trigPin = A1;
const int echoPin = A0;
const int servoPin = 10;

// Constants
const int thresholdDistance = 20; // Threshold distance in cm
const int scanStep = 15;          // Degrees to move the servo during scanning
const int servoLeft = 30;          // Leftmost position
const int servoRight = 150;       // Rightmost position

Servo servo1;

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
    servo1.attach(servoPin);
    servo1.write(90); // Start at the center position
}

void loop() {
  // put your main code here, to run repeatedly:
  int centerDistance = measureDistance();
  if (centerDistance < thresholdDistance) {
        Serial.println("Object detected! Scanning...");
        int leftDistance = scanSide(servoLeft);
        int rightDistance = scanSide(servoRight);
        if (leftDistance > rightDistance) {
            Serial.println("Move Left");
        } else {
            Serial.println("Move Right");
        }
        servo1.write(90);
        delay(1000);
    } else {
        Serial.println("Move Straight");
    }
  delay(100); // Main loop delay

}
// Function to measure distance using ultrasonic sensor
int measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); // Timeout in microseconds
    int distance = duration * 0.034 / 2;          // Convert to cm

    if (distance == 0 || distance > 400) {
        return 400; // Return max distance if no object detected
    }
    return distance;
}
// Function to scan a side and measure distance
int scanSide(int angle) {
    servo1.write(angle);
    delay(1000); // Wait for servo to reach position
    int distance = measureDistance();
    Serial.print("Distance at ");
    Serial.print(angle);
    Serial.print("°: ");
    Serial.print(distance);
    Serial.println(" cm");
    return distance;
}
