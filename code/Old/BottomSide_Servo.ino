#include <Servo.h>

// Pin Definitions
#define SERVO_X_PIN 9
#define SERVO_Y_PIN 10

// Servo Configuration
#define CENTER 87
#define SERVO_MIN 0
#define SERVO_MAX 270

Servo servoX;
Servo servoY;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  servoX.attach(SERVO_X_PIN); // Attach servos
  servoY.attach(SERVO_Y_PIN);

  // Set initial positions
  servoX.write(CENTER);
  servoY.write(CENTER);
}

void loop() {
  // Check if data is available
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read data until newline character
    int commaIndex = input.indexOf(','); // Find the comma separator

    if (commaIndex != -1) {
      // Split the input into X and Y values
      int xValue = input.substring(0, commaIndex).toInt();
      int yValue = input.substring(commaIndex + 1).toInt();

      // Map joystick values to servo ranges
      int servoXPos = map(xValue, 0, 1023, SERVO_MIN, SERVO_MAX);
      int servoYPos = map(yValue, 0, 1023, SERVO_MIN, SERVO_MAX);

      // Write to servos
      servoX.write(servoXPos);
      servoY.write(servoYPos);
    }
  }
}
