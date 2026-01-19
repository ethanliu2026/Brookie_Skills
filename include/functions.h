#pragma once
#include "vex.h"

extern bool intake_is_running;

//Function declarations

void scoreTopGoal(double time);
void scoreTopGoal (double speed, const vex::voltageUnits unit);
void scoreMiddleGoal(double speed, const vex::voltageUnits unit);
void scoreMiddleGoal (double speedTop, double speedMid, double speedBottom, const vex::voltageUnits unit);

void startDriverTasks();
void startBlueAutonTasks();
void startRedAutonTasks();

std::string getColorSortState();

void scoreLowSkills();
void scoreHighSkills();

extern double highVolt;
extern double lowVolt;
extern bool selVolt;