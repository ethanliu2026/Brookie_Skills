#include "tasks.h"
#include "vex.h"
#include "vex_global.h"

bool intake_is_running = false;

/*
double highVolt = 3.71;//3
double lowVolt = 4 ;//4.9, 4.58
bool selVolt = false;

void scoreLowSkills() {
  IntakeBottom.spin(reverse, lowVolt, volt);
  IntakeMid.spin(reverse, 8.7, volt);
  IntakeTop.spin(reverse, 7, volt);
}

void scoreHighSkills() {
  IntakeTop.spin(reverse, highVolt, volt); //6
  IntakeMid.spin(forward, 5., volt); //10
  IntakeBottom.spin(forward, 8, volt);
  
}
*/

void scoreTopGoal (double speed, const vex::voltageUnits unit){
  UpperIntakeLift.set(false);
  hood_down = false;
  Hood.set(true);
  IntakeTop.spin(forward, speed, unit);
  IntakeBottom.spin(forward, speed, unit);
  intake_is_running = true;
}

void scoreTopGoal(double time){
  UpperIntakeLift.set(false);
  hood_down = false;
  Hood.set(true);
  IntakeTop.spin(forward, 12.7, volt);
  IntakeBottom.spin(forward, 12.7, volt);
  intake_is_running = true;
  wait(50, msec);
  timer t;
  
  while(t.time(msec) < time){
    if (IntakeBottom.velocity(rpm) < 10) {
      Intake.spin(reverse, 12.7, volt);
      wait(50, msec);
      Intake.spin(forward, 12.7, volt);
      wait(50, msec);
  }   
  wait(10, msec);
  }
  Intake.stop();
}

void scoreMiddleGoal (double speed, const vex::voltageUnits unit){
  UpperIntakeLift.set(true);
  Hood.set(false);
  hood_down = false;
  IntakeTop.spin(forward, speed, unit);
  IntakeBottom.spin(forward, speed, unit);
  intake_is_running = true;
}

void scoreMiddleGoal (double speedTop, double speedMid, double speedBottom, const vex::voltageUnits unit){
  UpperIntakeLift.set(true);
  Hood.set(false);
  hood_down = false;
  IntakeTop.spin(forward, speedTop, unit);
  IntakeBottom.spin(forward, speedBottom, unit);
  intake_is_running = true;
}

void scoreLowGoal (double speed, const vex::voltageUnits unit){
  UpperIntakeLift.set(false);
  hood_down = true;
  intake_lift = true;
  IntakeTop.spin(reverse, speed, unit);
  IntakeBottom.spin(reverse, speed, unit);
  intake_is_running = true;
}

void scoreLowGoal (double t){
  UpperIntakeLift.set(false);
  hood_down = true;
  intake_lift = true;
  IntakeTop.spin(reverse, 7, volt);
  IntakeBottom.spin(reverse, 4.5, volt);
  intake_is_running = true;
  wait(t, msec);
}

void storeBall (double speed, const vex::voltageUnits unit){
  UpperIntakeLift.set(false);
  Hood.set(true);
  hood_down = true;
  left_shoulder_not_pressed = false;
  Intake.spin(forward, 12.7, volt);
  LowerIntakeLift.set(false);
  intake_lift = false;
}

void startDriverTasks() {
  auto_started = false;
  OdomLift.set(true);
  MatchLoader.set(false);
  LeftHook.set(false);
  LowerIntakeLift.set(false);
  UpperIntakeLift.set(false);
  chassis.Gyro.startCalibration();
  while(chassis.Gyro.isCalibrating()) {
  wait(10, msec);
}
  blueSort.suspend();
  redSort.suspend();
  controllerRumble.resume();
  autonControllerDisplay.suspend();
  hoodAuton.suspend();
  matchloaderAuton.suspend();
  intakeLift.suspend();
  anti_jam = false;
  toggle_red_sort = false;
  toggle_blue_sort = false;
  blue_alliance = blue_alliance;
  red_alliance = red_alliance;
}

void startBlueAutonTasks() {
  auto_started = true;
  blueSort.resume();
  redSort.suspend();
  hoodAuton.resume();
  matchloaderAuton.resume();
  intakeLift.resume();
  anti_jam = false;
  toggle_red_sort = false;
  toggle_blue_sort = false;
  blue_alliance = true;
  red_alliance = false;
}

void startRedAutonTasks() {
  auto_started = true;
  blueSort.suspend();
  redSort.resume();
  hoodAuton.resume();
  matchloaderAuton.resume();
  //intakeLift.resume();
  anti_jam = false;
  toggle_red_sort = false;
  toggle_blue_sort = false;
  blue_alliance = false;
  red_alliance = true;
  matchloader_down = false;
  hood_down = false;
}

std::string getColorSortState(){
    if (toggle_blue_sort && !toggle_red_sort) {
        return "BLUE";

    } else if (toggle_red_sort && !toggle_blue_sort) {
        return "RED";

    } else if (!toggle_blue_sort && !toggle_red_sort) {
        return "OFF ";

    } else {
        return "ERROR"; 
    }
}

void hoodCloseDelay(int delayTime){
  wait(delayTime, msec);
  hood_down = true;
}

void autoAlign() {
  chassis.set_coordinates(48, -27, 180);
  //chassis.turn_to_angle(230);
  //chassis.drive_distance(10, chassis.get_absolute_heading(), 5, 0, 1, 60, 700);
  //chassis.set_coordinates(48, -27, 180);
  chassis.turn_to_point(30, 30, 0, 10, 1, 400, 500);
  straightline_to_pose(30, -30, 12, 12, 1, 900, 1000);
  chassis.turn_to_angle(180, 10, 1, 400, 500);
  wait(1000, msec);
}