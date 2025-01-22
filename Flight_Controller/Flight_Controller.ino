#include <Servo.h>

// Micro Servos
Servo servoLeft;
Servo servoRight;
int pinServoLeft = 2;
int pinServoRight = 3;

// Flight Motors
// pinMotorLeft = D6;

void setup() {
  // PWM
  // pinMode(pinMotorLeft, OUTPUT);

  // Servos
  servoLeft.attach(pinServoLeft);
  servoRight.attach(pinServoRight);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // Motor Right: Write
  // analogWrite(pinMotorLeft, 20);

  // Left Servo: Write
  servoLeft.write(180);                  // sets the servo position according to the scaled value
  servoRight.write(180);
  delay(10000);                           // waits for the servo to get there
  servoLeft.write(0);                  // sets the servo position according to the scaled value
  servoRight.write(0);
  delay(10000);  
}