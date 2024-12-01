#include <Servo.h>
#include <Adafruit_MotorShield.h>

// Pin configuration
const int trigPin = A1;
const int echoPin = A0;
const int servoPin = 10;

// Constants
const int thresholdDistance = 20; // Threshold distance in cm
const int scanStep = 15;          // Degrees to move the servo during scanning
const int servoLeft = 30;          // Leftmost position
const int servoRight = 150;       // Rightmost position

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *left = AFMS.getMotor(4);   //Left Motor
Adafruit_DCMotor *right = AFMS.getMotor(2);  //Right Motor

Servo servo1;

void setup() {
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  servo1.attach(servoPin);
  servo1.write(90); // Start at the center position
  left->setSpeed(100);
  left->run(RELEASE);
  right->setSpeed(105);
  right->run(RELEASE);
}

void loop() {

  int centerDistance = measureDistance();
  if (centerDistance < thresholdDistance) {
    Serial.println("Object detected! Scanning...");
    stop();
    delay(500);
    int leftDistance = scanSide(servoLeft);
    int rightDistance = scanSide(servoRight);
    servo1.write(90);
    moveBackward();
    delay(500);
    stop();
    delay(500);
    if (leftDistance > rightDistance) {
      moveLeft();
      delay(100);
      stop();
      delay(500);
      Serial.println("Move Left");
    } 
    else {
      moveRight();
      delay(100);
      stop();
      delay(500);
      Serial.println("Move Right");
    }
    
    delay(1000);
  } else {
      moveForward();
      Serial.println("Move Straight");
  }
delay(100); 
}

//Move Forward
void moveForward(){
  left->run(FORWARD);
  right->run(FORWARD);
}

//Stop
void stop(){
  left->run(RELEASE);
  right->run(RELEASE);
}

//Move Backward
void moveBackward(){
  left->run(BACKWARD);
  right->run(BACKWARD);
}

//Move Left
void moveLeft(){
  left->run(BACKWARD);
  right->run(FORWARD);
}

//Move Right
void moveRight(){
  left->run(FORWARD);
  right->run(BACKWARD);
}
// Measure distance using ultrasonic sensor
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

//Scan a side and measure distance
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
