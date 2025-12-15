#include "vex.h"
#include "vex_global.h"

bool intake_is_running = false;

double highVolt = 3.8;//3
double lowVolt = 4.90;//4.58
bool selVolt = false;

void scoreTopGoal (double speed, const vex::voltageUnits unit){
  IntakeTop.spin(forward, speed, unit);
  IntakeMid.spin(forward, speed, unit);
  IntakeBottom.spin(forward, speed, unit);
  intake_is_running = true;
}

void scoreMiddleGoal (double speed, const vex::voltageUnits unit){
  IntakeTop.spin(reverse, speed, unit);
  IntakeMid.spin(forward, speed, unit);
  IntakeBottom.spin(forward, speed, unit);
  intake_is_running = true;
}

void scoreMiddleGoal (double speedTop, double speedMid, double speedBottom, const vex::voltageUnits unit){
  IntakeTop.spin(reverse, speedTop, unit);
  IntakeMid.spin(forward, speedMid, unit);
  IntakeBottom.spin(forward, speedBottom, unit);
  intake_is_running = true;
}

void storeBall (double speed, const vex::voltageUnits unit){
  hood_down = true;
  IntakeTop.spin(forward, speed, unit);
  IntakeMid.spin(reverse, speed, unit);
  IntakeBottom.spin(reverse, speed, unit);
}

void scoreLowSkills() {
  IntakeBottom.spin(reverse, lowVolt, volt);
  IntakeMid.spin(reverse, 9, volt);
  IntakeTop.spin(reverse, 9, volt);
}

void scoreHighSkills() {
  IntakeTop.spin(reverse, highVolt, volt); //6
  IntakeMid.spin(forward, 5., volt); //10
  IntakeBottom.spin(forward, 8, volt);
  
}

void startDriverTasks() {
  auto_started = false;
  antiJam.suspend();
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
  antiJam.resume();
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
  antiJam.suspend();
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
  //intake_lift = false;
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