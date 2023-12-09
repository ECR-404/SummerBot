#pragma once

#include "pros/motors.hpp"
#include "pros/distance.hpp"
#include "pros/adi.hpp"

static pros::Motor l_fly(20, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Motor r_fly(21, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
static pros::Distance index_distance(3);
static pros::ADIDigitalOut wingR ('F', false);
static pros::Motor elevMotor(8, pros::E_MOTOR_GEAR_100, false, pros::E_MOTOR_ENCODER_DEGREES);


static void setWing(bool state){
    wingR.set_value(state);
}