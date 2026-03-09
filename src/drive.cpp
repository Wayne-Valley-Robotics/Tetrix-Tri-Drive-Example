#include "drive.h"

PRIZM prizm;
EXPANSION exc;
PS4 ps4;

void updateDrive()
{
    // Reinitialize variables each loop
    int outputFront = 0;
    int outputLeft = 0;
    int outputRight = 0;
    int motorSpeed = 0;
    // Store joystick values to avoid streneuously polling the motor expansions
    int joyLY = ps4.Stick(LY) - 128; // set center to 0
    int joyLX = ps4.Stick(LX) - 128;
    int joyRX = ps4.Stick(RX) - 128;
    constexpr int joyMin = -128;
    constexpr int joyMax = 127;

    // ps4.Stick(); returns 0 to 255
    // by subtracting 128, we get a range of -128 to 127, where the centered stick is now 0

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
        if (abs(btnUp) > 0)
        {
            motorSpeed = map(btnUp, joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputFront += motorSpeed;
            outputLeft += motorSpeed;
            outputRight += motorSpeed;
        }
        if (abs(btnDown) > 0)
        {
            motorSpeed = map(abs(btnDown), joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputFront -= motorSpeed;
            outputLeft -= motorSpeed;
            outputRight -= motorSpeed;
        }

        // Strafe left/right input processing (triangle drive logic)
        if (abs(btnLeft) > 0)
        {
            motorSpeed = map(abs(btnLeft), joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputLeft += motorSpeed;
            outputRight -= motorSpeed;
        }
        if (abs(btnRight) > 0)
        {
            motorSpeed = map(abs(btnRight), joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputLeft -= motorSpeed;
            outputRight += motorSpeed;
        }

        // Rotation input processing
        if (abs(btnRotL) > 0)
        {
            motorSpeed = map(abs(btnRotL), joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputFront -= motorSpeed;
            outputLeft += motorSpeed;
            outputRight -= motorSpeed;
        }
        if (abs(btnRotR) > 0)
        {
            motorSpeed = map(abs(btnRotR), joyMin, joyMax, -MOTOR_MAX_OUTPUT, MOTOR_MAX_OUTPUT);
            outputFront += motorSpeed;
            outputLeft -= motorSpeed;
            outputRight += motorSpeed;
        }
    }
    else
    {
        // Continuation of brake logic, at this point we know we need to brake
        // brake == 125, coast == 0
        int brakePower = BRAKE_ON_RELEASE * 125;
        outputFront = brakePower;
        outputLeft = brakePower;
        outputRight = brakePower;
    }

    // Apply inversion settings
    outputFront = outputFront * INVERT_FRONT;
    outputLeft = outputLeft * INVERT_LEFT;
    outputRight = outputRight * INVERT_RIGHT;

    Serial.print("Joy: ");
    Serial.print(joyLY);
    Serial.print("\t");
    Serial.print(joyLX);
    Serial.print("\t");
    Serial.print(joyRX);
    Serial.print("\tPowers: ");
    Serial.print(outputFront);
    Serial.print("\t");
    Serial.print(outputLeft);
    Serial.print("\t");
    Serial.print(outputRight);
    Serial.println();

    // Set motor powers
    exc.setMotorPower(MOTOR_FRONT_EXPANSION, MOTOR_FRONT_PORT, outputFront);
    exc.setMotorPower(MOTOR_LEFT_EXPANSION, MOTOR_LEFT_PORT, outputLeft);
    exc.setMotorPower(MOTOR_RIGHT_EXPANSION, MOTOR_RIGHT_PORT, outputRight);
}
