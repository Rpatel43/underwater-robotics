#include <Servo.h>

const int minThrusterValue = 1100;
const int maxThrusterValue = 1900;

Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;
void setup() {
  // Initialize motor pins
  thruster1.attach(9);
  thruster2.attach(10);
  thruster3.attach(11);
  thruster4.attach(6);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    // Read joystick values (expecting 6 values: x1, y1, x2, y2, x3, y3)
    int joy1X = Serial.parseInt();
    int joy1Y = Serial.parseInt();
    int joy2X = Serial.parseInt();
    int joy2Y = Serial.parseInt();
    int joy3X = Serial.parseInt();
    int joy3Y = Serial.parseInt();
    // bottom left joystick movement
    if ((joy2X > 500) && (joy2X < 522)) {

      int xMapped = map(joy1X, 0, 1023, -400, 400);
      int yMapped = map(joy1Y, 0, 1023, -400, 400);

      int power1 = constrain(map(-xMapped + yMapped, -400, 400, minThrusterValue, maxThrusterValue), minThrusterValue, maxThrusterValue);
      int power2 = constrain(map(xMapped + yMapped, -400, 400, minThrusterValue, maxThrusterValue), minThrusterValue, maxThrusterValue);
    
      thruster1.writeMicroseconds(power1);
      thruster2.writeMicroseconds(power2);
      thruster3.writeMicroseconds(power1);
      thruster4.writeMicroseconds(power2);

      delay(10);

      // Z direction Movement
      int joy2yMapped = map(joy2Y, 0, 1023, minThrusterValue, maxThrusterValue);

      thruster5.writeMicroseconds(joy2yMapped);
      thruster6.writeMicroseconds(joy2yMapped);
      }
    int YawPower1 = map(joy2X, 0, 1023, minThrusterValue, maxThrusterValue); // thruster values for one and four yaw
    int YawPower2 = map(joy2Y, 0, 1023, maxThrusterValue, minThrusterValue); // thruster values for two and three yaw
    
    thruster1.writeMicroseconds(YawPower1);
    thruster2.writeMicroseconds(YawPower2);
    thruster3.writeMicroseconds(YawPower1);
    thruster4.writeMicroseconds(YawPower2);
    }


}
