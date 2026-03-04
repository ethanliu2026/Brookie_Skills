#include "vex.h"
#include "tasks.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);
motor LF = motor(PORT13, ratio6_1, true);
motor LM = motor(PORT14, ratio6_1, true);
motor LB = motor(PORT15, ratio6_1, true);
motor RF = motor(PORT18, ratio6_1, false);
motor RM = motor(PORT19, ratio6_1, false);
motor RB = motor(PORT20, ratio6_1, false);
motor IntakeTop = motor(PORT11, ratio6_1, false);
motor IntakeBottom = motor(PORT12, ratio6_1, true);
motor_group Intake = motor_group(IntakeTop, IntakeBottom);
controller Controller1 = controller(primary);
digital_out Hood = digital_out(Brain.ThreeWirePort.A);
digital_out UpperIntakeLift = digital_out(Brain.ThreeWirePort.B);
digital_out LowerIntakeLift = digital_out(Brain.ThreeWirePort.C);
digital_out LeftHook = digital_out(Brain.ThreeWirePort.E);
digital_out MatchLoader = digital_out(Brain.ThreeWirePort.D);
digital_out OdomLift = digital_out(Brain.ThreeWirePort.F);

rotation HorizOdom = rotation(PORT10);
rotation VertOdom = rotation(PORT21);
distance SortDist = distance(PORT12);
distance LeftDist = distance(PORT16);
distance BackDist = distance(PORT9);
distance rightDist = distance(PORT8);
optical SortOptical = optical(PORT10);

bool MogoClamp = false;
bool LdoinkClamp = false;

bool RdoinkClamp = false;
bool IntakeLiftClamp = false;
bool right_shoulder_not_pressed = true;
bool left_shoulder_not_pressed = true;
bool RemoteControlCodeEnabled = true;

//Add your devices below, and don't forget to do the same in robot-config.h:
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  startDriverTasks();
  Controller1.Screen.clearScreen();
  //toggle_red_sort = true;
  while(true) {
    SortOptical.integrationTime(5);
    SortOptical.setLight(vex::ledState::on);
    double color_data = SortOptical.hue(); 
    double distance_data = SortDist.value(); 

    if(RemoteControlCodeEnabled) {
      //IntakeLift.set(false);
      
        if (Controller1.ButtonL2.pressing()){
        UpperIntakeLift.set(false);
        Hood.set(false);
        hood_down = false;
        left_shoulder_not_pressed = false;
        Intake.spin(forward, 12.7, volt);
        //scoreMiddleGoal(40, volt);
        anti_jam = false;
        LowerIntakeLift.set(false);
        intake_lift = false;

        } else if (Controller1.ButtonL1.pressing()) {
          left_shoulder_not_pressed = false;
          Intake.spin(reverse, 12.7, volt);
          anti_jam = false;         
          LowerIntakeLift.set(false);
          intake_lift = false;
         } else {
            left_shoulder_not_pressed = true;
          }
        
      if (Controller1.ButtonR1.pressing()) {
          right_shoulder_not_pressed = false;
          LowerIntakeLift.set(false);
          scoreMiddleGoal(12.7, 12.7, 12.7, volt); 
          intake_lift = false;    
          } else if (Controller1.ButtonR2.pressing()) {
            right_shoulder_not_pressed = false;
            scoreTopGoal(12.7, volt);  
            intake_lift = false;
          } else {
            right_shoulder_not_pressed = true;
          }


         if (right_shoulder_not_pressed && left_shoulder_not_pressed && !auto_started){
          Intake.stop();
          //Hood.set(false);
          //intake_is_running = false;
         }

        if (Controller1.ButtonX.pressing()){
          MatchLoader.set(!(MatchLoader.value()));
          matchloader_down = !matchloader_down;
          vexDelay(250);
          }
        
        if (Controller1.ButtonUp.pressing()){
          toggle_red_sort = !toggle_red_sort;
          /*if (blue_alliance) { 
            toggle_red_sort = false;
            toggle_blue_sort = !toggle_blue_sort;
          } else if (red_alliance) {
            toggle_red_sort = !toggle_red_sort;
            toggle_blue_sort = false;
          } else {
            toggle_blue_sort = false;
            toggle_red_sort = false;
          }*/
           vexDelay(500);
          }
      
      if(Controller1.ButtonA.pressing()) {
        Hood.set(!(Hood.value()));
        hood_down = !hood_down;
        vexDelay(250);
      }
      IntakeLiftClamp = Controller1.ButtonA.pressing();

      if(Controller1.ButtonB.pressing()) {
        LowerIntakeLift.set(!LowerIntakeLift.value());
        vexDelay(250);
      }
      if(Controller1.ButtonDown.pressing()) {
        //autoResetPosition();
        LeftHook.set(!(LeftHook.value()));
        vexDelay(250);
      }
      
      //Controller1.ButtonLeft.pressed(autoAlign); 

     }
    wait(20, msec);
  }
  return 0;
  }

void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  // nothing to initialize
}

void drivecodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}