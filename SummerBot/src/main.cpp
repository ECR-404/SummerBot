/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\ecrro                                            */
/*    Created:      Tue Jun 06 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// leftGroup            motor_group   1, 2            
// rightGroup           motor_group   3, 4            
// flywheel             motor_group   5, 16           
// intake               motor         11              
// Vision9              vision        21              
// LeftPiston           digital_out   A               
// RightPiston          digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
competition Comp;
void user();
void auton();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Comp.autonomous(auton);
  Comp.drivercontrol(user);
  user();
  while(true){
    wait(100, msec);
  }
}
