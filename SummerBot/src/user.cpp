#include "vex.h"
#include "iostream"
using namespace vex; 

static int speen = 0;
static bool flySpeen = false;

static float flySpeed;
static float targetFlywheelSpeed = 600;
//call back thingy for the flywheel
void spinny(){
  if(!flySpeen){
    flySpeen = true;
    flywheel.spin(forward, (100), pct);
  }else{
    flySpeen = false;
    flywheel.stop();
  }
}

//callback for intake - currently toggle
void intakey(){
  if(speen == 0){
    speen = 1;
    intake.spin(forward, (100), pct);
    // wait(0.1, seconds);
  }else if (speen == 1){
    //wait(0.1, seconds);
    speen = 2;
    intake.spin(reverse, 100, pct);
  }else{
    speen = 0;
    intake.stop();
    // wait(0.1, seconds);
  }
}


void user(){
  while(true){
    LeftPiston=false;
    RightPiston=false;
    //chaysis control
    leftGroup.spin(forward, Controller1.Axis3.position(), pct);
    rightGroup.spin(forward, Controller1.Axis2.position(), pct); 

    //flywheel
    Controller1.ButtonA.pressed(spinny);

    //intake
    Controller1.ButtonB.pressed(intakey);
    
    double p = 0.90;
    int targetFlywheelSpeed = 250;
    flySpeed = 0;

    
    if(Vision9.objectCount > 0){
      targetFlywheelSpeed = 10000/Vision9.largestObject.height;
    }else{
      targetFlywheelSpeed = 500;
    }
    std::cout<<flywheel.velocity(rpm);
    Vision9.takeSnapshot(Vision9__SIG_1, 10);
  
    std::cout<<" ";
    //expected - actual
    int error = targetFlywheelSpeed  - flywheel.velocity(rpm);  
    if(error > 20){
      flySpeed = targetFlywheelSpeed - p * (error);
    }else{
      flySpeed = targetFlywheelSpeed + 100 - error/2;
    }
    if(Controller1.ButtonLeft.pressing()) {
        LeftPiston=!LeftPiston;
    }
    else if (Controller1.ButtonRight.pressing()) {
      RightPiston=!RightPiston;
    }
  }
}