
#include <Servo.h>
Servo myservo;
int potpinx = 0;
int potpiny = 1;
int valx;
int valy;
int ThrusterSpeed = 200;
int moveindirection = 0;
const int threshold = 100;
int serialsend=0;
int rotatepin = 2;
int verticalpin = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  // Read analog values from joystick
  int xValue = analogRead(potpinx);
  int yValue = analogRead(potpiny);
  int rotateValue = analogRead(rotatepin);
  int verticalValue = analogRead(verticalpin);
  //Serial.println(xValue);
  //Serial.println(yValue);
  // Check for joystick direction and then send value based on that
  serialsend = 300;
  if (yValue < 512 - threshold) {
    //Serial.print("N");
    serialsend=1;
  } else if (yValue > 512 + threshold) {
    //Serial.print("S");
    serialsend=5;
  } else {
    //Serial.print(""); // No significant Y direction
  }

  if (xValue < 512 - threshold) {
    //Serial.print("W");
    serialsend=3;
  } else if (xValue > 512 + threshold) {
    //Serial.print("E");
    serialsend=7;
  } else {
    //Serial.print(""); // No significant X direction
  }

  if (xValue < 512 - threshold && yValue < 512 - threshold) {
    //Serial.print("NW");
    serialsend=2;
  } else if (xValue < 512 - threshold && yValue > 512 + threshold) {
    //Serial.print("SW");
    serialsend=4;
  } else if (xValue > 512 + threshold && yValue < 512 - threshold) {
    //Serial.print("NE");
    serialsend=8;
  } else if (xValue > 512 + threshold && yValue > 512 + threshold) {
    //Serial.print("SE");
    serialsend=6;
  }
//  if (((xValue < 512+ threshold) && (xValue > 512- threshold)) && ((yValue < 512+ threshold) && (yValue > 512- threshold))) {
//    serialsend=0;
//  }
  //rotate right
  if (rotateValue > 542) {
    serialsend = 9;
  }
  //rotate left
  if (rotateValue < 482) {
    serialsend = 10;
  }
  //go up
  if (verticalValue > 542) {
    serialsend = 11;
  }
  //go down
  if (verticalValue < 482) {
    serialsend = 12;
  }  

  Serial.println(serialsend);  // Print new line
  delay(100);  // Delay for stability
}
