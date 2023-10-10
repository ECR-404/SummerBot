using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor_group leftGroup;
extern motor_group rightGroup;
extern motor_group flywheel;
extern motor intake;
extern signature Vision9__SIG_1;
extern signature Vision9__SIG_2;
extern signature Vision9__SIG_3;
extern signature Vision9__SIG_4;
extern signature Vision9__SIG_5;
extern signature Vision9__SIG_6;
extern signature Vision9__SIG_7;
extern vision Vision9;
extern digital_out LeftPiston;
extern digital_out RightPiston;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );