#include <Servo.h>

// Micro Servos
Servo servoLeft;
Servo servoRight;
const int servoLeftPin = 4;
const int servoRightPin = 5;

// RadioMaster Reading
const int inputJoyRX = 2; // Interupt-capable pin
volatile unsigned long pwmRXStart = 0;
volatile unsigned long pwmRXHighTime = 0;
volatile unsigned long pwmRXLowTime = 0;

// ESC Motors
Servo escLeft;
const int escLeftPin = 9;
const int MIN_SIGNAL = 1200; // Minimum throttle (us)
const int MAX_SIGNAL = 1900; // Maximum throttle (us)

void setup() {
  // RadioMaster Reading
  pinMode(inputJoyRX, INPUT);
  attachInterrupt(digitalPinToInterrupt(inputJoyRX), handleJoyRX, CHANGE);

  // ESC Motors
  escLeft.attach(escLeftPin);
  escLeft.writeMicroseconds(MIN_SIGNAL);

  // Micro Servos
  servoLeft.attach(servoLeftPin);
  servoRight.attach(servoRightPin);  // attaches the servo on pin 9 to the servo object

  delay(1000);
}

void handleJoyRX() {
  if (digitalRead(inputJoyRX) == HIGH) {
    pwmRXStart = micros(); // Record the time when the signal goes HIGH
  } else {
    pwmRXHighTime = micros() - pwmRXStart; // Calculate HIGH duration
    pwmRXLowTime = pwmRXStart - micros(); // Calculate LOW duration
  }
}

void loop() {
  // ==========================
  // RadioMaster: read volatile values
  // ==========================
  noInterrupts(); // Needed to read volatile variables safely
  unsigned long highTimeRX = pwmRXHighTime;
  unsigned long lowTimeRX = pwmRXLowTime;
  interrupts();
  
  // ==========================
  // ESC Motors: Convert radio reading + Write
  // ==========================
  highTimeRX = map(highTimeRX, 983, 1998, 0, 100);
  escLeft.writeMicroseconds(map(highTimeRX, 60, 100, MIN_SIGNAL, MAX_SIGNAL));




  // ==========================
  // Micro Servos: Write angle
  // ==========================
  servoLeft.write(180);
  servoRight.write(180);
}

