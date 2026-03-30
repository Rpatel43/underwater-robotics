#include <Servo.h>

// Constants
#define MIN_THRUSTER_VALUE = 1100;
#define MAX_THRUSTER_VALUE = 1900;
#define JOYSTICK_CENTER_THRESHOLD_LOW = 500;
#define JOYSTICK_CENTER_THRESHOLD_HIGH = 522;

// Servo objects
Servo thruster1;
Servo thruster2;
Servo thruster3;
Servo thruster4;
Servo thruster5;
Servo thruster6;

// Function to map joystick input to thruster values
int mapJoystickToThruster(int joystickValue, int minInput, int maxInput) {
  return constrain(map(joystickValue, minInput, maxInput, MIN_THRUSTER_VALUE, MAX_THRUSTER_VALUE), MIN_THRUSTER_VALUE, MAX_THRUSTER_VALUE);
}

// Function to control the thrusters
void controlThrusters(int xInput, int yInput) {
  int xMapped = map(xInput, 0, 1023, -400, 400);
  int yMapped = map(yInput, 0, 1023, -400, 400);

  int power1 = mapJoystickToThruster(-xMapped + yMapped, -400, 400);
  int power2 = mapJoystickToThruster(xMapped + yMapped, -400, 400);

  thruster1.writeMicroseconds(power1);
  thruster2.writeMicroseconds(power2);
  thruster3.writeMicroseconds(power1);
  thruster4.writeMicroseconds(power2);
}

// Function to handle vertical movement (Z-axis)
void controlVerticalMovement(int zInput) {
  int zPower = mapJoystickToThruster(zInput, 0, 1023);
  thruster5.writeMicroseconds(zPower);
  thruster6.writeMicroseconds(zPower);
}

// Function to handle yaw control
void controlYaw(int xInput, int yInput) {
  int yawPower1 = mapJoystickToThruster(xInput, 0, 1023);
  int yawPower2 = mapJoystickToThruster(yInput, 0, 1023);

  thruster1.writeMicroseconds(yawPower1);
  thruster2.writeMicroseconds(yawPower2);
  thruster3.writeMicroseconds(yawPower1);
  thruster4.writeMicroseconds(yawPower2);
}

void setup() {
  // Attach thrusters to their respective pins
  thruster1.attach(9);
  thruster2.attach(10);
  thruster3.attach(11);
  thruster4.attach(6);
  thruster5.attach(7);
  thruster6.attach(8);

  // Initialize Serial communication
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

    // Bottom-left joystick movement (x1, y1)
    if (joy2X > JOYSTICK_CENTER_THRESHOLD_LOW && joy2X < JOYSTICK_CENTER_THRESHOLD_HIGH) {
      controlThrusters(joy1X, joy1Y);
      controlVerticalMovement(joy2Y);
    }

    // Yaw control (x2, y2)
    controlYaw(joy2X, joy2Y);
  }
}
