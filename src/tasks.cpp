#include "vex.h"
#include "tasks.h"
#include <queue>

bool anti_jam = false;

bool toggle_blue_sort = false;
bool toggle_red_sort = false;
bool fling = false;

bool blue_alliance = false;
bool red_alliance = false;
bool intake_running = false;

int BLUE_VALUE = 220;
int RED_VALUE = 345;
int COLOR_TOL = 10;

double color_data = SortOptical.hue(); 
double distance_data = (SortDist.value());

bool matchloader_down = false;
bool hood_down = false;
bool intake_lift = false;

int rumbleTask(){
  while(1) {
    if (Controller1.ButtonUp.pressing()) {
      Controller1.rumble(".");
      vexDelay(500);
    }
  }
}

/* STORING */
int antiJamTask(){
  while(1) {
    if (IntakeTop.torque() > 0.6 && anti_jam){
      IntakeTop.stop(coast);
      wait(600, msec);
      IntakeTop.spin(reverse, 100, volt);
      wait(600, msec);
      IntakeTop.stop(coast);
    }
    
     if (IntakeMid.torque() > 0.6 && anti_jam){
      IntakeMid.stop(coast);
      wait(600, msec);
      IntakeMid.spin(reverse, 100, volt);
      wait(600, msec);
      IntakeMid.stop(coast);
     }
    }
}

/* COLOR SORT */

int colorBlueSortTask(){
  while(1){
    SortOptical.setLight(vex::ledState::on);
    double color_data = SortOptical.hue(); 
    double distance_data = (SortDist.value()); 
    SortOptical.integrationTime(5);

    if ((color_data > RED_VALUE - COLOR_TOL) && (color_data < RED_VALUE + COLOR_TOL)) { //if ring is red, send signal to fling
        fling = true;
      }
    if(fling && distance_data < 30 && toggle_blue_sort){ //if ring is sensed by distance, fling
      scoreMiddleGoal(30, volt);
      vexDelay(40);
      fling = false;
    }
  }
}

int colorRedSortTask(){
  while(1){
    SortOptical.setLight(vex::ledState::on);

    if ((color_data > BLUE_VALUE - COLOR_TOL) && (color_data < BLUE_VALUE + COLOR_TOL)) { //if ring is red, send signal to fling
        fling = true;
      }

    if(distance_data < 30 && toggle_red_sort && fling){ //if ring is sensed by distance, fling
      scoreMiddleGoal(30, volt);
      vexDelay(40);
      fling = false;
    }
    }
  }

int autonControllerTask(){
  while(1){
    Controller1.Screen.setCursor(1,1);
    
    Controller1.Screen.print("X:");
    Controller1.Screen.setCursor(1,4);
    Controller1.Screen.print(chassis.get_X_position());
    Controller1.Screen.setCursor(1,10);
    Controller1.Screen.print("Y:");
    Controller1.Screen.setCursor(1,13);
    Controller1.Screen.print((chassis.get_Y_position()));
    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("Sort:");
    Controller1.Screen.setCursor(2,6);
    Controller1.Screen.print(getColorSortState().c_str());
    Controller1.Screen.setCursor(2,10);
    Controller1.Screen.print("Theta:");
    Controller1.Screen.setCursor(2,16);
    Controller1.Screen.print(chassis.get_absolute_heading());
    Controller1.Screen.setCursor(3,1);
    Controller1.Screen.print("Battery: ");
    Controller1.Screen.setCursor(3,10);
    Controller1.Screen.print(Brain.Battery.capacity());
    task::sleep(20);

  } 
}

int matchLoaderTask(){
  while(1){
    if(matchloader_down) {
      MatchLoader.set(true);
    } else {
      MatchLoader.set(false);
    }  
  }
}

int hoodTask(){
  while(1){
    if(hood_down) {
      Hood.set(true);
    } else {
      Hood.set(false);
    }  
  }
}

int liftTask(){
  while(1){
    if(intake_lift) {
      IntakeLift.set(true);
    } else {
      IntakeLift.set(false);
    }  
  }
}

vex::task antiJam(antiJamTask);
vex::task blueSort(colorBlueSortTask);
vex::task redSort(colorRedSortTask);
vex::task controllerRumble(rumbleTask);
vex::task autonControllerDisplay(autonControllerTask);
vex::task matchloaderAuton(matchLoaderTask);
vex::task hoodAuton(hoodTask);
vex::task intakeLift(liftTask);