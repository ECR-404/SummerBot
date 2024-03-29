#include "main.h"
#include "niic.hpp"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 127 ; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

// pros::Motor l_fly(4, pros::E_MOTOR_GEAR_600, false, pros::E_MOTOR_ENCODER_DEGREES);
// pros::Motor r_fly(5, pros::E_MOTOR_GEAR_600, true, pros::E_MOTOR_ENCODER_DEGREES);
// pros::Distance index_distance(1);
// pros::Motor indexMotor (19, pros::E_MOTOR_GEAR_200, true, pros::E_MOTOR_ENCODER_DEGREES);


///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void moveElevation(float degrees, float time, int speed){
  //determine normal voltage output
  //if voltage output is higher than normal, cancel the movement; 
  elevMotor.move_absolute(degrees, speed);
  float timer = 0;
  while(timer < time){
    if((degrees < 0 && elevMotor.get_current_draw() > 1500)){
      elevMotor.brake();
      elevMotor.move_absolute(-550, 100);
      break;
    }
    
    pros::delay(ez::util::DELAY_TIME);
    timer += ez::util::DELAY_TIME;
  }
}

///
// Drive Example
///
void leftElims_auton() {
  setWing(true);
  pros::delay(200);
  setWing(false);
  // chassis.set_drive_pid(22, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-5, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(7, DRIVE_SPEED);
  // chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(75-60, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(15-60, TURN_SPEED);
  chassis.wait_drive();
  elevMotor.move_absolute(-150, 100);
  pros::delay(200);
  chassis.set_drive_pid(17, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(105-60, DRIVE_SPEED);
  chassis.wait_drive();
  setWing(true);
  chassis.set_drive_pid(35, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(200-60, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(105-60, TURN_SPEED);
  chassis.wait_drive();
  setWing(false);
}
void left_auton() {
//   // The first parameter is target inches
//   // The second parameter is max speed the robot will drive at
//   // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
//   // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  elevMotor.move_absolute(0, 100);
  pros::delay(100);
  std::cout<<elevMotor.get_current_draw();
  //normally 24 but scaled down for lancer comp
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  //same as above

  
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(7, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-18, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-23, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(7,TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  moveElevation(-1400, 3000, 100);
  /*while(timer < 3200){
    if(timer > 2000 && elevMotor.get_actual_velocity() < 75){
      elevMotor.brake();
      break;
    }
    pros::delay(ez::util::DELAY_TIME);
    timer += ez::util::DELAY_TIME;
  }*/
  
  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();
  elevMotor.move_absolute(0, 100);
  
  pros::delay(2000);
  chassis.set_turn_pid(155, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(100, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(15, DRIVE_SPEED);
  chassis.wait_drive();
  // pros::delay(500);
  // chassis.set_turn_pid(-10, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(22, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(-10, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-60, TURN_SPEED);
  // chassis.set_drive_pid(35, DRIVE_SPEED);
  // chassis.wait_drive();
  // setWing(true);
  // chassis.set_turn_pid(-40,TURN_SPEED);
  // chassis.set_drive_pid(20, DRIVE_SPEED);
  // chassis.wait_drive();


  //   chassis.set_drive_pid(5, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(10, DRIVE_SPEED);
  // chassis.wait_drive();
}

void skills(){
  elevMotor.move_absolute(-200, 100);
  pros::delay(200);
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();
  pros::delay(200);
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  if(chassis.interfered){
    chassis.set_drive_pid(0, DRIVE_SPEED);
  }  
  elevMotor.move_absolute(-700, 100);
  pros::delay(1000); 
  l_fly.move_velocity(420);
  pros::delay(3000);
  l_fly.brake();
  chassis.set_turn_pid(165, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(110, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(42, DRIVE_SPEED);
  chassis.wait_drive();
  elevMotor.move_absolute(-700, 100);
  pros::delay(1000);
  chassis.set_drive_pid(9, DRIVE_SPEED);
  chassis.wait_drive();
  elevMotor.move_absolute(0, 100);
  pros::delay(2000);
  stop.set_value(true);

  // while(1){
  //   while( index_distance.get() > 12){
  //     indexMotor.move_velocity(200);
  //     pros::delay(2);
  //   }
  //   pros::delay(500);
  // }
}

void right_auton(){
  // chassis.set_drive_pid(7, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(-45, TURN_SPEED);
  // chassis.wait_drive();

  elevMotor.move_absolute(0, 100);
  chassis.set_drive_pid(22, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(15, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-17, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-70, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5.5, DRIVE_SPEED);
  chassis.wait_drive();
  // chassis.set_drive_pid(0.5,DRIVE_SPEED);
  // chassis.wait_drive();
  
  float timer = 0;
  moveElevation(-1200, 3000, 100);
  chassis.set_drive_pid(6, DRIVE_SPEED);
  // elevMotor.move_relative(500, 100);
  chassis.wait_drive();
  elevMotor.move_absolute(-100, 100);
  pros::delay(2000);
  chassis.set_turn_pid(-150, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-110, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(18, DRIVE_SPEED);
  chassis.wait_drive();

}

// void drive_fwd(){
//   chassis.set_drive_pid(30, DRIVE_SPEED);
//   chassis.wait_drive();
// }



///
// Turn Example
///
// void turn_example() {
//   // The first parameter is target degrees
//   // The second parameter is max speed the robot will drive at


//   chassis.set_turn_pid(90, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();
// }



// ///
// // Combining Turn + Drive
// ///
// void drive_and_turn() {
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_drive();
// }



// ///
// // Wait Until and Changing Max Speed
// ///
// void wait_until_change_speed() {
//   // wait_until will wait until the robot gets to a desired position


//   // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_until(6);
//   chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(-45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_until(-6);
//   chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
//   chassis.wait_drive();
// }



// ///
// // Swing Example
// ///
// void swing_example() {
//   // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
//   // The second parameter is target degrees
//   // The third parameter is speed of the moving side of the drive


//   chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_until(12);

//   chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
//   chassis.wait_drive();
// }



// ///
// // Auto that tests everything
// ///
// void combining_movements() {
//   chassis.set_drive_pid(24, DRIVE_SPEED, true);
//   chassis.wait_drive();

//   chassis.set_turn_pid(45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_turn_pid(0, TURN_SPEED);
//   chassis.wait_drive();

//   chassis.set_drive_pid(-24, DRIVE_SPEED, true);
//   chassis.wait_drive();
// }



// ///
// // Interference example
// ///
// void tug (int attempts) {
//   for (int i=0; i<attempts-1; i++) {
//     // Attempt to drive backwards
//     printf("i - %i", i);
//     chassis.set_drive_pid(-12, 127);
//     chassis.wait_drive();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.reset_drive_sensor();
//       chassis.set_drive_pid(-2, 20);
//       pros::delay(1000);
//     }
//     // If robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// // If there is no interference, robot will drive forward and turn 90 degrees. 
// // If interfered, robot will drive forward and then attempt to drive backwards. 
// void interfered_example() {
//  chassis.set_drive_pid(24, DRIVE_SPEED, true);
//  chassis.wait_drive();

//  if (chassis.interfered) {
//    tug(3);
//    return;
//  }

//  chassis.set_turn_pid(90, TURN_SPEED);
//  chassis.wait_drive();
// }



// . . .
// Make your own autonomous functions here!
// . . .


