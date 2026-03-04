#pragma once
#include "vex.h"

extern bool intake_is_running;

//Function declarations

void scoreTopGoal(double speed, const vex::voltageUnits unit);
void scoreTopGoal(double time);
void scoreMiddleGoal(double speed, const vex::voltageUnits unit);
void scoreMiddleGoal (double speedTop, double speedMid, double speedBottom, const vex::voltageUnits unit);
void hoodCloseDelay(int delayTime);

void storeBall(double speed, const vex::voltageUnits unit);
void scoreLowGoal (double speed, const vex::voltageUnits unit);
void scoreLowGoal (double t);

void startDriverTasks();
void startBlueAutonTasks();
void startRedAutonTasks();

void autoAlign();

std::string getColorSortState();

void scoreLowSkills();
void scoreHighSkills();

extern double highVolt;
extern double lowVolt;
extern bool selVolt;