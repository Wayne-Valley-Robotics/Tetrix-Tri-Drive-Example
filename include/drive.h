#pragma once
#include <Arduino.h>
#include <PRIZM.h>
#include <TELEOP.h>

// Shared hardware objects (defined in src/robot.cpp)
extern PRIZM prizm;
extern EXPANSION exc;
extern PS4 ps4;

// Configuration constants (constexpr to keep header-safe)
constexpr int DEADZONE = 25;
constexpr int MOTOR_MAX_SPEED = 100;
constexpr bool BRAKE_ON_RELEASE = true;

constexpr int MOTOR_FRONT_EXPANSION = 2;
constexpr int MOTOR_FRONT_PORT = 1;

constexpr int MOTOR_LEFT_EXPANSION = 3;
constexpr int MOTOR_LEFT_PORT = 2;

constexpr int MOTOR_RIGHT_EXPANSION = 2;
constexpr int MOTOR_RIGHT_PORT = 2;

constexpr int INVERT_FRONT = 1;
constexpr int INVERT_LEFT = 1;
constexpr int INVERT_RIGHT = 1;


void updateDrive();
