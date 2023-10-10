#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftGroupMotorA = motor(PORT1, ratio18_1, false);
motor leftGroupMotorB = motor(PORT2, ratio18_1, false);
motor_group leftGroup = motor_group(leftGroupMotorA, leftGroupMotorB);
motor rightGroupMotorA = motor(PORT3, ratio18_1, true);
motor rightGroupMotorB = motor(PORT4, ratio18_1, true);
motor_group rightGroup = motor_group(rightGroupMotorA, rightGroupMotorB);
motor flywheelMotorA = motor(PORT5, ratio6_1, false);
motor flywheelMotorB = motor(PORT16, ratio6_1, true);
motor_group flywheel = motor_group(flywheelMotorA, flywheelMotorB);
motor intake = motor(PORT11, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision9__SIG_1 = signature (1, 427, 8287, 4357, -845, 623, -111, 0.7, 0);
signature Vision9__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision9__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision9__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision9__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision9__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision9__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision9 = vision (PORT21, 41, Vision9__SIG_1, Vision9__SIG_2, Vision9__SIG_3, Vision9__SIG_4, Vision9__SIG_5, Vision9__SIG_6, Vision9__SIG_7);
/*vex-vision-config:end*/
digital_out LeftPiston = digital_out(Brain.ThreeWirePort.A);
digital_out RightPiston = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}