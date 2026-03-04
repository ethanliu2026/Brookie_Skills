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
  //Controller1.Screen.clearScreen();
  while(1){
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("X:");
    Controller1.Screen.setCursor(1,4);
    Controller1.Screen.print(chassis.get_X_position());
    Controller1.Screen.setCursor(1,10);
    Controller1.Screen.print("Y:");
    Controller1.Screen.setCursor(1,13);
    Controller1.Screen.print(chassis.get_Y_position());
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

int driveControllerTask(){
  while(1) {
  /* DRIVE TEMP */
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Drive: ");
    Controller1.Screen.setCursor(1,8);
    Controller1.Screen.print((RF.temperature(celsius)+RM.temperature(celsius)+RB.temperature(celsius)+LF.temperature(celsius)+LM.temperature(celsius)+LB.temperature(celsius))/6);

    /* INTAKE TEMP */
    Controller1.Screen.setCursor(1,14);
    Controller1.Screen.print("Top:");
    Controller1.Screen.setCursor(1, 19);
    Controller1.Screen.print((int)(IntakeTop.temperature(celsius)+0.5));

    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("Btm:");
    Controller1.Screen.setCursor(2,6);
    Controller1.Screen.print((int)(IntakeBottom.temperature(celsius)+0.5));

    /* GYRO */
    Controller1.Screen.setCursor(2,10);
    Controller1.Screen.print("Gyro:");
    Controller1.Screen.setCursor(2,16);
    Controller1.Screen.print(chassis.get_absolute_heading());


    /* AUTON SELECTION */
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Blue SOLO");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("SOLO");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Red SOLO");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RNINE");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Blue LEFT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RFOUR");
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Red LEFT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RSEVEN");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Blue RIGHT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("LNINE");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Red RIGHT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("LSEVEN");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Blue LEFT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("LFOUR");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Red LEFT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RFOUR");
        break;
      case 8:
        Brain.Screen.printAt(5, 140, "Blue RIGHT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("BRE");
        break;
      case 9:
        Brain.Screen.printAt(5, 140, "Red RIGHT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RRE");
        break;
      case 10:
        Brain.Screen.printAt(5, 140, "SKILLS");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("SKILLS");
        break;
      case 11:
        Brain.Screen.printAt(5, 140, "PID");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("PID");
        break;
      case 12:
        Brain.Screen.printAt(5, 140, "ODOM");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("ODOM");
        break;
    }
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
      Hood.set(false);
    } else {
      Hood.set(true);
    }  
  }
}

int liftTask(){
  while(1){
    if(intake_lift) {
      LowerIntakeLift.set(true);
    } else {
      LowerIntakeLift.set(false);
    }  
  }
}

vex::task blueSort(colorBlueSortTask);
vex::task redSort(colorRedSortTask);
vex::task controllerRumble(rumbleTask);
vex::task autonControllerDisplay(autonControllerTask);
vex::task driveControllerDisplay(driveControllerTask);
vex::task matchloaderAuton(matchLoaderTask);
vex::task hoodAuton(hoodTask);
vex::task intakeLift(liftTask);