#pragma once
#include "JAR-Template/drive.h"
#include "vex.h"

// Boolean declarations
extern bool anti_jam;
extern bool toggle_blue_sort;
extern bool toggle_red_sort;
extern bool fling;

extern bool right_shoulder_not_pressed;
extern bool left_shoulder_not_pressed;

extern bool blue_alliance;
extern bool red_alliance;

extern bool auto_started;
extern bool intake_running;

extern bool matchloader_down;
extern bool hood_down;
extern bool intake_lift;

extern int RED_VALUE;
extern int BLUE_VALUE;
extern int COLOR_TOL;

// Task declarations
int antiJamTask();
int colorBlueSortTask();
int colorRedSortTask();
int rumbleTask();
int autonControllerTask();
int matchLoaderTask();
int hoodTask();


extern vex::task antiJam;
extern vex::task blueSort;
extern vex::task redSort;
extern vex::task controllerRumble;
extern vex::task autonControllerDisplay;
extern vex::task matchloaderAuton;
extern vex::task hoodAuton;
extern vex::task intakeLift;