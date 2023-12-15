#include "main.h"
#include "iostream"
#include "niic.hpp"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {4, 5, 16}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{-2, -3, -19}

  // Inertial Port
  ,14

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder      
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

void set_fly(int input) {
  l_fly= input;
  r_fly = input;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  // ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!

  l_fly.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  l_fly.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("left side", left_auton),
    Auton("right side", right_auton),
    // Auton("drive forward (near side)", drive_fwd),
    Auton("ONLY RUN FOR SKILLS", skills),
    // Auton("Example Turn\n\nTurn 3 times.", turn_example),
    // Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    // Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    // Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    // Auton("Combine all 3 movements", combining_movements),
    // Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
    // Auton("red side", red_side)
  });
  

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();

  //multithreading potential, idk if it's needed yet
  // Task drive(chassis.tank);
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
  l_fly.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  l_fly.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  elevMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  stop.set_value(true);
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  elevMotor.tare_position();
  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}







/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

bool up, down = false;

void opcontrol() {

  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  bool toggle { false }; //This variable will keep state between loops or function calls

  stop.set_value(true);

  //to draw a 404 logo during a match
  pros::screen::set_eraser(COLOR_BLACK);
  pros::screen::erase();
  pros::screen::set_pen(COLOR_CADET_BLUE);
  pros::screen::fill_rect(0, 0, 480, 20);
  pros::screen::print(pros::E_TEXT_LARGE_CENTER, 6, "404Z!");

  elevMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  double t = 0;
  bool stopped = true;

  while (true) {
    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    if(master.get_digital_new_press(DIGITAL_R1)){
      if(!toggle){
        elevMotor.move_absolute(-750, 100);
        set_fly(400);
      }else{
        set_fly(0);
      }
      toggle = !toggle;
    }
    
    if(master.get_digital_new_press(DIGITAL_L1)){
      up = true;
      elevMotor.move_absolute(-1600, 100);
    }
    if(up && master.get_digital(DIGITAL_L1)){
      elevMotor.move_velocity(-100);
    }else{
      up = false;
    }

    if(master.get_digital_new_press(DIGITAL_L2)){
      down =true;
      elevMotor.move_absolute(-100, 100);
    }
    if(down && master.get_digital(DIGITAL_L2)){
      elevMotor.move_velocity(100);
    }else{
      down = false;
    }

    if(!master.get_digital(DIGITAL_L2) && !master.get_digital(DIGITAL_L1) && !toggle){
      elevMotor.brake();
    }
    
    

    // if(master.get_digital_new_press(DIGITAL_L2) || !master.get_digital(DIGITAL_L2)){
    //   t=0;
    // }
    // while(master.get_digital(DIGITAL_L2)){
    //   t+= ez::util::DELAY_TIME;
    // }
    // if(t >= 0.5){
    //   stop.set_value(true);
    //   stopped = true;
    // }
    // if(stopped && master.get_digital_new_press(DIGITAL_L2)){
    //   stop.set_value(true);
    //   stopped = false;
    // }

    if(master.get_digital_new_press(DIGITAL_UP)){
      stop.set_value(!stopped);
      stopped = !stopped;
    }
    
    if(master.get_digital_new_press(DIGITAL_R2)) {
      setWing(!toggle);    //When false go to true and in reverse
      toggle = !toggle;    //Flip the toggle to match piston state
    } 
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
