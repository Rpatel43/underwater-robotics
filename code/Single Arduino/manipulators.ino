#include <Servo.h>

// Pins
#define XJOY_PIN A0
#define YJOY_PIN A1
#define CLAW_SERVO_PIN A2
#define ROTATE_SERVO_PIN A3

// Servo Config
#define CENTER 87
#define SERVO_MIN 0
#define SERVO_MAX 180
#define THRESHOLD 80
#define MOVEMENT_STEP 1
#define LOOP_DELAY 8

Servo clawServo;
Servo rotateServo;
int claw_servo_position = CENTER;  
int rotate_servo_position = CENTER; 

void setup() 
{
  Serial.begin(9600);

  clawServo.attach(CLAW_SERVO_PIN);
  rotateServo.attach(ROTATE_SERVO_PIN);
  
  clawServo.write(CENTER);  
  rotateServo.write(CENTER);
}

void loop() 
{
  // Read and map joystick value
  int joystickValueX = map(analogRead(XJOY_PIN), 0, 1023, SERVO_MIN, SERVO_MAX);
  int joystickValueY = map(analogRead(YJOY_PIN), 0, 1023, SERVO_MIN, SERVO_MAX);

  // Adjust servo position based on joystick input
  if (joystickValueX > CENTER + THRESHOLD) 
  {
    claw_servo_position -= MOVEMENT_STEP;  // Positive X is open claw
  }
  else if (joystickValueX < CENTER - THRESHOLD) 
  {
    claw_servo_position += MOVEMENT_STEP;  // Negative X is close claw
  }


  if (joystickValueY > CENTER + THRESHOLD) 
  {
    rotate_servo_position += MOVEMENT_STEP;  // Positive Y is CW claw rotation
  }
  else if (joystickValueY < CENTER - THRESHOLD) 
  {
    rotate_servo_position -= MOVEMENT_STEP;  // Negative Y is CCW claw rotation
  }

  // Constrain servo position to valid range
  claw_servo_position = constrain(claw_servo_position, SERVO_MIN, SERVO_MAX);
  rotate_servo_position = constrain(rotate_servo_position, SERVO_MIN, SERVO_MAX);

  clawServo.write(claw_servo_position);
  rotate_servo_position.write(rotate_servo_position);

  delay(LOOP_DELAY); 
}
