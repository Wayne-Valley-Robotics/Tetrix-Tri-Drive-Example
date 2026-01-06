#include "robot.h"

PRIZM prizm;
EXPANSION exc;
PS4 ps4;

void updateDrive()
{
    // Reinitialize variables each loop
    int powerFront = 0;
    int powerLeft = 0;
    int powerRight = 0;
    int motorSpeed = 0;
    // Store joystick values to avoid streneuously calling this stupid library (these three alone should take more than 100ms alone)
    int joyLY = ps4.Stick(LY);
    int joyLX = ps4.Stick(LX);
    int joyRX = ps4.Stick(RX);

    // ps4.Stick(); returns -255 to 255
    // ps4.Motor(); returns -100 to 100 for use with motors

    // Get joy values and apply deadzone
    int btnUp = (joyLY * (joyLY > DEADZONE));    // forward
    int btnDown = (joyLY * (joyLY < -DEADZONE)); // backward
    int btnLeft = (joyLX * (joyLX < -DEADZONE)); // strafe left
    int btnRight = (joyLX * (joyLX > DEADZONE)); // strafe right
    int btnRotL = (joyRX * (joyRX < -DEADZONE)); // rotate left
    int btnRotR = (joyRX * (joyRX > DEADZONE));  // rotate right

    // Input logic

    // Brake on release logic
    if ((abs(btnUp) + abs(btnDown) + abs(btnLeft) + abs(btnRight) + abs(btnRotL) + abs(btnRotR)) > 0)
    {
        // Forward/back input processing
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

        // Strafe left/right input processing (triangle drive logic)
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

        // Rotation input processing
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
    }
    else
    {
        // Continuation of brake logic, we know we need to brake
        // brake == 125, coast == 0
        int brakePower = BRAKE_ON_RELEASE * 125;
        powerFront = brakePower;
        powerLeft = brakePower;
        powerRight = brakePower;
    }

    // Apply inversion settings
    powerFront = powerFront * INVERT_FRONT;
    powerLeft = powerLeft * INVERT_LEFT;
    powerRight = powerRight * INVERT_RIGHT;

    // Set motor powers
    exc.setMotorPower(MOTOR_FRONT_EXPANSION, MOTOR_FRONT_PORT, powerFront);
    exc.setMotorPower(MOTOR_LEFT_EXPANSION, MOTOR_LEFT_PORT, powerLeft);
    exc.setMotorPower(MOTOR_RIGHT_EXPANSION, MOTOR_RIGHT_PORT, powerRight);
}
