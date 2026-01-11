#pragma once
#include "JAR-Template/drive.h"
#include "vex.h"

void distanceReset();
void getBotPosition(float xcoordinate, float ycoordinate, float heading); 
void getDesiredDistance(float horizontal, float vertical);
void getDistanceDifference(float desiredHorizontal, float desiredVertical);
void straightline_to_pose(float x, float y, float driveVolt, float headingVolt, int settleError, int settleTime, int Timeout);
void straightline_to_pose(float x, float y, float driveVolt, float headingVolt, int settleError, int settleTime, int Timeout, bool negative);
void straightline_to_pose(float x, float y, float driveVolt);
float get_hypot(float desiredX, float desiredY, float actualX, float actualY);
float get_heading(float desiredX, float desiredY, float actualX, float actualY);
float getYDesired(float vertical);
float getXDesired(float horizontal);
void updateQuadrant(float x, float y);
void updateHeading(float heading);
float getCorrectedX(float backSensorReading, float leftSensorReading);
float getCorrectedY(float backSensorReading, float leftSensorReading);
void resetPositionSkills();
float resetXPositionQuad1(float backSensorReading, float leftSensorReading);
float resetYPositionQuad1(float backSensorReading, float leftSensorReading);
float resetXPositionQuad2(float backSensorReading, float leftSensorReading);
float resetYPositionQuad2(float backSensorReading, float leftSensorReading);
float resetXPositionQuad3(float backSensorReading, float leftSensorReading);
float resetYPositionQuad3(float backSensorReading, float leftSensorReading);
float resetXPositionQuad4(float backSensorReading, float leftSensorReading);
float resetYPositionQuad4(float backSensorReading, float leftSensorReading);
void resetPositionQuad1(float backSensorReading, float leftSensorReading, float Heading);
void resetPositionQuad2(float backSensorReading, float leftSensorReading, float Heading);
void resetPositionQuad3(float backSensorReading, float leftSensorReading, float Heading);
void resetPositionQuad4(float backSensorReading, float leftSensorReading, float Heading);
void autoResetPosition();
void horizontalResetPosition();
void rightHorizontalResetPosition();
void verticalResetPosition();