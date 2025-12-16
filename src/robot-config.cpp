#include "motion.h"
#include "vex.h"
#include "tasks.h"
#include "functions.h"
#include "vex_global.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);
motor LF = motor(PORT13, ratio6_1, true);
motor LM = motor(PORT1, ratio6_1, true);
motor LB = motor(PORT2, ratio6_1, true);
motor RF = motor(PORT11, ratio6_1, false);
motor RM = motor(PORT16, ratio6_1, false);
motor RB = motor(PORT3, ratio6_1, false);
motor IntakeTop = motor(PORT5, ratio6_1, false);
motor IntakeMid = motor(PORT19, ratio6_1, false);
motor IntakeBottom = motor(PORT7, ratio6_1, false);
motor_group Intake = motor_group(IntakeTop, IntakeMid, IntakeBottom);
controller Controller1 = controller(primary);
digital_out Hood = digital_out(Brain.ThreeWirePort.A);
digital_out IntakeLift = digital_out(Brain.ThreeWirePort.E);
digital_out LeftHook = digital_out(Brain.ThreeWirePort.B);
digital_out MatchLoader = digital_out(Brain.ThreeWirePort.C);
distance SortDist = distance(PORT12);
distance LeftDist = distance(PORT6);
distance BackDist = distance(PORT10);
optical SortOptical = optical(PORT8);
inertial IMU = inertial(PORT4);
bool sort = false;



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
  LeftHook.set(true);
  while(true) {
    SortOptical.integrationTime(5);
    SortOptical.setLight(vex::ledState::on);
    double color_data = SortOptical.hue(); 
    double distance_data = SortDist.value(); 

    if(RemoteControlCodeEnabled) {


      if (Controller1.ButtonR1.pressing()){

         if ((color_data > RED_VALUE - COLOR_TOL) 
          && (color_data < RED_VALUE + COLOR_TOL)) { //if ring is red, send signal to fling
          sort = true;
        } else {
          sort = false;
        }

        if (sort && distance_data < 30) {
          IntakeTop.spin(reverse,highVolt, volt);
          IntakeMid.spin(reverse, 12.7, volt);
          IntakeBottom.spin(reverse, 12.7, volt);
          wait(400, msec);
        } else {
          scoreHighSkills();
        }


      }

      if (toggle_blue_sort) {
        if ((color_data > RED_VALUE - COLOR_TOL) 
          && (color_data < RED_VALUE + COLOR_TOL)) { //if ring is red, send signal to fling
          fling = true;
        } else {
          fling = false;
        }

        if (Controller1.ButtonL2.pressing() && fling && distance_data < 30 && toggle_blue_sort){
        right_shoulder_not_pressed = false;
        scoreMiddleGoal(40, volt);
        vexDelay(40);
        fling = false;

        } else if (Controller1.ButtonL2.pressing() && !fling){
          left_shoulder_not_pressed = false;
          Hood.set(true);
          Intake.spin(forward, 127, volt);
          anti_jam = false;
          } else {
            left_shoulder_not_pressed = true;
          }


        if (Controller1.ButtonR2.pressing() && fling && distance_data < 30 && toggle_blue_sort){
        Hood.set(false);
        right_shoulder_not_pressed = false;
        scoreMiddleGoal(40, volt);
        vexDelay(40);
        fling = false;

        } else if (Controller1.ButtonR2.pressing() && !fling){
          right_shoulder_not_pressed = false;
          Hood.set(false);
          hood_down = false;
          scoreTopGoal(12.7, volt);

        } else if (!Controller1.ButtonR2.pressing()){
          right_shoulder_not_pressed = true;
        }
      } else {
        if (Controller1.ButtonR2.pressing()){
          right_shoulder_not_pressed = false;
          Hood.set(false);
          hood_down = false;
          scoreTopGoal(12.7, volt);
           } else {
          right_shoulder_not_pressed = true;
         } 

         if (Controller1.ButtonL2.pressing()){
          left_shoulder_not_pressed = false;
          Hood.set(true);
          hood_down = true;
          Intake.spin(forward, 127, volt);
          anti_jam = false;
          } else {
          left_shoulder_not_pressed = true;
         }
         
      }

      if (toggle_red_sort) {
        if ((color_data > BLUE_VALUE - COLOR_TOL) 
          && (color_data < BLUE_VALUE + COLOR_TOL)) { //if ring is red, send signal to fling
          fling = true;
        } else {
          fling = false;
        }
        if (Controller1.ButtonR2.pressing() && fling && distance_data < 30 && toggle_red_sort){
        Hood.set(false);
        hood_down = false;
        right_shoulder_not_pressed = false;
        scoreMiddleGoal(40, volt);
        vexDelay(40);
        fling = false;

        } else if (Controller1.ButtonR2.pressing() && !fling){
          right_shoulder_not_pressed = false;
          Hood.set(false);
          hood_down = false;
          scoreTopGoal(12.7, volt);

        } else if (!Controller1.ButtonR2.pressing()){
          right_shoulder_not_pressed = true;
        }
      } else {
        if (Controller1.ButtonR2.pressing()){
          right_shoulder_not_pressed = false;
          Hood.set(false);
          hood_down = false;
          scoreTopGoal(12.7, volt);
           } else {
          right_shoulder_not_pressed = true;
         } 

         if (Controller1.ButtonL2.pressing()){
          left_shoulder_not_pressed = false;
          Hood.set(true);
          hood_down = true;
          Intake.spin(forward, 127, volt);
          anti_jam = false;
          } else {
          left_shoulder_not_pressed = true;
         }
         
      }

      /*if (Controller1.ButtonR1.pressing()) {
            if((color_data > BLUE_VALUE - COLOR_TOL) && (color_data < BLUE_VALUE + COLOR_TOL)) {
              scoreHighSkills();    
            }
            else if ((color_data > RED_VALUE - COLOR_TOL) && (color_data < RED_VALUE + COLOR_TOL)) {
              Intake.spin(forward, 12, volt);
            }
          }*/

      if (Controller1.ButtonL1.pressing()) {
          left_shoulder_not_pressed = false;
          Hood.set(false);
          hood_down = false;
          Intake.spin(reverse, 127, volt);
          anti_jam = false;         
         }

      /*if (Controller1.ButtonR2.pressing()){
          right_shoulder_not_pressed = false;
          Hood.set(false);
          scoreTopGoal(127, volt);
          }
       else if (Controller1.ButtonR1.pressing()) {
          right_shoulder_not_pressed = false;
          scoreMiddleGoal(127, volt);      
         } else {
          right_shoulder_not_pressed = true;
         }*/


         if (right_shoulder_not_pressed && left_shoulder_not_pressed && !auto_started){
          Intake.stop();
          intake_is_running = false;
         }

         /*
        if (Controller1.ButtonX.pressing()){
          MatchLoader.set(!(MatchLoader.value()));
          matchloader_down = !matchloader_down;
          vexDelay(250);
          }
        */
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
        MatchLoader.set(!(MatchLoader.value()));
        matchloader_down = !matchloader_down;
        vexDelay(250);
      }
      if(Controller1.ButtonDown.pressing()) {
        IntakeLift.set(true);
        scoreLowSkills();
        /*
        IntakeLift.set(!(IntakeLift.value()));
        vexDelay(250);
        */
      }
      else {
        //IntakeLift.set(false);
      }
      
      if (Controller1.ButtonX.pressing() && Controller1.ButtonY.pressing()) {
        selVolt = !selVolt;
      }
      else if (Controller1.ButtonX.pressing()) {
        if(selVolt) {
          lowVolt += 0.01;
        }
        else {
          highVolt += 0.01;
        }
      }
      else if (Controller1.ButtonY.pressing()) {
        if (selVolt) {
          lowVolt -= 0.01;
        }
        else {
          highVolt -= 0.01;
        }
      }

      if (Controller1.ButtonR1.pressing()) {
          scoreHighSkills();     
          }

      if(Controller1.ButtonLeft.pressing()) {
        IntakeLift.set(!(IntakeLift.value()));
        vexDelay(250);
        //scoreHighSkills();
      }
      
      if(Controller1.ButtonRight.pressing()) {
        Hood.set(!(Hood.value()));
        vexDelay(250);
      }
    
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