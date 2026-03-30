#include <Servo.h>

Servo thruster1;  // Top Left
Servo thruster2;  // Top Right

const int VRxPin = A0;
const int VRyPin = A1;

const int minThrusterValue = 1100;
const int maxThrusterValue = 1900;

void setup() {
  thruster1.attach(9); 
  thruster2.attach(10);
  Serial.begin(9600);
}

void loop() {
  int VRx = analogRead(VRxPin);
  int VRy = analogRead(VRyPin);

  // Center joystick values to be around zero
  int xMapped = map(VRx, 0, 1023, -400, 400);
  int yMapped = map(VRy, 0, 1023, -400, 400);

  // Calculate power for thruster 1 and thruster 2 based on the joystick direction
  int power1 = constrain(map(-xMapped + yMapped, -400, 400, minThrusterValue, maxThrusterValue), minThrusterValue, maxThrusterValue);
  int power2 = constrain(map(xMapped + yMapped, -400, 400, minThrusterValue, maxThrusterValue), minThrusterValue, maxThrusterValue);

  // Set power for thrusters 1 and 2
  thruster1.writeMicroseconds(power1);
  thruster2.writeMicroseconds(power2);

  // Debugging output
  Serial.print("VRx: "); Serial.print(xMapped);
  Serial.print(" VRy: "); Serial.print(yMapped);
  Serial.println("");
  Serial.print(" Thruster1 Power: "); Serial.print(power1);
  Serial.print(" Thruster2 Power: "); Serial.println(power2);

  delay(10);
}
