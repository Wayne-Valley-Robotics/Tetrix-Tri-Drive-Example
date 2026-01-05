#include <Arduino.h>
#include <PRIZM.h>
#include <TELEOP.h>
PRIZM prizm;
EXPANSION exc;
PS4 ps4;

const int DEADZONE = 10;        // joystick deadzone range
const int MOTOR_MAX_SPEED = 50; // motor power level (0-100)

const int MOTOR_FRONT_EXPANSION = 1; // front motor expansion address
const int MOTOR_FRONT_PORT = 1;      // front motor port

const int MOTOR_LEFT_EXPANSION = 1; // left motor expansion address
const int MOTOR_LEFT_PORT = 2;       // left motor port

const int MOTOR_RIGHT_EXPANSION = 1; // right motor expansion address
const int MOTOR_RIGHT_PORT = 2;      // right motor port
// Initialize motor powers
int powerFront = 0;
int powerLeft = 0;
int powerRight = 0;

void setup()
{
  prizm.PrizmBegin();
}

void loop()
{
  int motorSpeed = 0;
  // store joystick values to avoid streneuously calling this stupid library
  int joyLY = ps4.Stick(LY);
  int joyLX = ps4.Stick(LX);
  int joyRX = ps4.Stick(RX);

  // ps4.Stick(); returns -255 to 255
  // ps4.Motor(); returns -100 to 100 for use with motors

  // get joy values and apply deadzone
  int btnUp = (joyLY * (joyLY > DEADZONE));    // forward
  int btnDown = (joyLY * (joyLY < -DEADZONE)); // backward
  int btnLeft = (joyLX * (joyLX < -DEADZONE)); // strafe left
  int btnRight = (joyLX * (joyLX > DEADZONE)); // strafe right
  int btnRotL = (joyRX * (joyRX < -DEADZONE)); // rotate left
  int btnRotR = (joyRX * (joyRX > DEADZONE));  // rotate right

  // Forward/back
  if (btnUp > 0)
  {
    motorSpeed = map(btnUp, 0, 255, 0, MOTOR_MAX_SPEED);
    powerFront += motorSpeed;
    powerLeft += motorSpeed;
    powerRight += motorSpeed;
  }
  if (abs(btnDown) > 0)
  {
    motorSpeed = map(abs(btnDown), 0, 255, 0, MOTOR_MAX_SPEED);
    powerFront -= motorSpeed;
    powerLeft -= motorSpeed;
    powerRight -= motorSpeed;
  }

  // Strafe left/right (triangle drive math)
  if (abs(btnLeft) > 0)
  {
    motorSpeed = map(abs(btnLeft), 0, 255, 0, MOTOR_MAX_SPEED);
    powerLeft += motorSpeed;
    powerRight -= motorSpeed;
  }
  if (abs(btnRight) > 0)
  {
    motorSpeed = map(abs(btnRight), 0, 255, 0, MOTOR_MAX_SPEED);
    powerLeft -= motorSpeed;
    powerRight += motorSpeed;
  }

  // Rotate
  if (abs(btnRotL) > 0)
  {
    motorSpeed = map(abs(btnRotL), 0, 255, 0, MOTOR_MAX_SPEED);
    powerFront -= motorSpeed;
    powerLeft += motorSpeed;
    powerRight -= motorSpeed;
  }
  if (abs(btnRotR) > 0)
  {
    motorSpeed = map(abs(btnRotR), 0, 255, 0, MOTOR_MAX_SPEED);
    powerFront += motorSpeed;
    powerLeft -= motorSpeed;
    powerRight += motorSpeed;
  }

  // Set motor powers
  exc.setMotorPower(MOTOR_FRONT_EXPANSION, MOTOR_FRONT_PORT, powerFront);
  exc.setMotorPower(MOTOR_LEFT_EXPANSION, MOTOR_LEFT_PORT, powerLeft);
  exc.setMotorPower(MOTOR_RIGHT_EXPANSION, MOTOR_RIGHT_PORT, powerRight);
}