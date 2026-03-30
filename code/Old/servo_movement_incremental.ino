#include <Servo.h>

// Pin Definitions
#define XJOY_PIN A0
#define SERVO_PIN A1

// Servo Configuration
#define CENTER 87
#define SERVO_MIN 0
#define SERVO_MAX 180
#define THRESHOLD 80
#define MOVEMENT_STEP 1
#define LOOP_DELAY

Servo myservo;
int servo_position = CENTER;  // Initial servo position

void setup() 
{
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  myservo.write(CENTER);  
}

void loop() 
{
  // Read and map joystick value
  int joystickValue = map(analogRead(XJOY_PIN), 0, 1023, SERVO_MIN, SERVO_MAX);

  // Adjust servo position based on joystick input
  if (joystickValue > CENTER + THRESHOLD) 
  {
    servo_position += MOVEMENT_STEP;  // Move right
  }
  else if (joystickValue < CENTER - THRESHOLD) 
  {
    servo_position -= MOVEMENT_STEP;  // Move left
  }

  // Constrain servo position to valid range
  servo_position = constrain(servo_position, SERVO_MIN, SERVO_MAX);
  myservo.write(servo_position);

  delay(LOOP_DELAY); 
}
