#include <Servo.h>
#include <Adafruit_MotorShield.h>

int i;
Servo servo1;

void setup() {
  // put your setup code here, to run once:
  // Attach a servo to pin #10
  servo1.attach(10);
  servo1.write(30);
  delay(1000);
  servo1.write(150);
  delay(1000);
  servo1.write(90);


}

void loop() {
  // put your main code here, to run repeatedly:
//    for (i=60; i<=150; i++) {
//     servo1.write(i);
//     delay(100);
//  }
//    for (i=120; i<=150; i--) {
//     servo1.write(i);
//     delay(100);
//  }

}
