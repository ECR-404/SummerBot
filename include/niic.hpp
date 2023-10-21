#pragma once

#include "pros/motors.hpp"
#include "pros/distance.hpp"

static pros::Motor l_fly(4, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor r_fly(5, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Distance index_distance(1);
static pros::Motor indexMotor(19, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);