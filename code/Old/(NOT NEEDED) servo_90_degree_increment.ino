#include <Servo.h>
#define XJOY_PIN A0
#define SERVO_PIN A1

int servo_val;
Servo myservo;

void setup()
{
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
}

void loop() {
 int joystickXVal = analogRead(XJOY_PIN);
 servo_val = map(joystickXVal, 0, 1023, 0, 180);

 if(servo_val == 180){
   myservo.write(87);
 }
 else if (servo_val == 0){
   myservo.write(20);
 }
}

