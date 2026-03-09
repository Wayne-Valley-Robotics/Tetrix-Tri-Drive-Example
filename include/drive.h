#pragma once
#include <Arduino.h>
#include <PRIZM.h>
#include <TELEOP.h>

extern PRIZM prizm;
extern EXPANSION exc;
extern PS4 ps4;

constexpr int DEADZONE = 25;
constexpr int MOTOR_MAX_OUTPUT = 100;
constexpr bool BRAKE_ON_RELEASE = true;

// motor expansion 0 refers to the prizm itself's I2C port
constexpr int MOTOR_FRONT_EXPANSION = 2;
constexpr int MOTOR_FRONT_PORT = 1;

constexpr int MOTOR_LEFT_EXPANSION = 3;
constexpr int MOTOR_LEFT_PORT = 2;

constexpr int MOTOR_RIGHT_EXPANSION = 2;
constexpr int MOTOR_RIGHT_PORT = 2;

constexpr int INVERT_FRONT = 1;
constexpr int INVERT_LEFT = -1;
constexpr int INVERT_RIGHT = 1;

void updateDrive();
