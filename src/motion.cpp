#include "autons.h"
#include "vex.h"

bool in_quad_1 = false;
bool in_quad_2 = false;
bool in_quad_3 = false;
bool in_quad_4 = false;

bool facing_red = false;
bool facing_blue = false;
bool facing_right = false;
bool facing_left = false;

float CLOSE_DIST = 36;
float FAR_DIST = 70.4; //previously 72

float XCoord;
float YCoord;
float Heading;
float horizontalDesiredDist;
float verticalDesiredDist;
float horizontalDifference;
float verticalDifference;


/* DISTANCE RESET */

float sideDistPos = 2.9; //previously 3.7
float backDistPos = 3.3; //previously 3.0

void updateQuadrant(float x, float y) {
  if (x > 0 && y > 0) {
    in_quad_1 = true;
    in_quad_2 = false;
    in_quad_3 = false;
    in_quad_4 = false;
  } else if (x < 0 && y > 0) {
    in_quad_1 = false;
    in_quad_2 = true;
    in_quad_3 = false;
    in_quad_4 = false;
  } else if (x < 0 && y < 0) {
    in_quad_1 = false;
    in_quad_2 = false;
    in_quad_3 = true;
    in_quad_4 = false;
  } else {
    in_quad_1 = false;
    in_quad_2 = false;
    in_quad_3 = false;
    in_quad_4 = true;
  }
}

void updateHeading(float heading) {
  while (heading<0) heading += 360;
  while (heading>=360) heading -= 360;
  // Reset all
  facing_red = false;
  facing_blue = false;
  facing_right = false;
  facing_left = false;
  //direction update
  if (heading > 350 || heading < 10) {
    // Facing BLUE (0°)
    facing_red = false;
    facing_blue = true;
    facing_right = false;
    facing_left = false;
  } else if (heading > 80 && heading < 100) {
    // Facing RIGHT (90°)
    facing_red = false;
    facing_blue = false;
    facing_right = true;
    facing_left = false;
  } else if (heading > 170 && heading < 190) {
    // Facing RED (180°)
    facing_red = true;
    facing_blue = false;
    facing_right = false;
    facing_left = false;
  } else if (heading > 260 && heading < 280) {
    // Facing LEFT (270°)
    facing_red = false;
    facing_blue = false;
    facing_right = false;
    facing_left = true;
  }
}

float getCorrectedX(float backSensorReading, float leftSensorReading) {
  if(facing_blue) {
      return (leftSensorReading + sideDistPos) - FAR_DIST;
  }
  else if(facing_right) {
      return (backSensorReading + backDistPos) - FAR_DIST;
  }
  else if(facing_red) {
      return FAR_DIST - (leftSensorReading + sideDistPos); 
  }
  else if(facing_left) {
      return FAR_DIST - (backSensorReading + backDistPos);
  }
  return XCoord;
}

float getCorrectedY(float backSensorReading, float leftSensorReading) {
  if(facing_blue) {
      return (backSensorReading + backDistPos) - FAR_DIST;
  }
  else if(facing_right) {
      return FAR_DIST - (leftSensorReading + sideDistPos);
  }
  else if(facing_red) {
      return FAR_DIST - (backSensorReading + backDistPos);
  }
  else if(facing_left) {
      return (leftSensorReading + sideDistPos) - FAR_DIST;
  }
  return YCoord;
}

//resets position, but not accurate due to limited range of distance sensor
void resetPositionSkills() {
  // Get current odometry position
  XCoord = chassis.get_X_position();
  YCoord = chassis.get_Y_position();
  Heading = chassis.get_absolute_heading();
  
  // Update quadrant and heading flags
  updateQuadrant(XCoord, YCoord);
  updateHeading(Heading);
  
  // Read actual sensor values (in inches)
  float backActual = BackDist.value() / 25.4;
  float leftActual = LeftDist.value() / 25.4;
  
  // Calculate corrected position using actual sensor readings
  float correctedX = getCorrectedX(backActual, leftActual);
  float correctedY = getCorrectedY(backActual, leftActual);
  
  // Update chassis with corrected position
  chassis.set_coordinates(correctedX, correctedY, Heading);
}

//reset position by quadrant, since only left and back sensor, find the correct corner for closest walls
float resetXPositionQuad1 (float backSensorReading, float leftSensorReading) {
  return FAR_DIST - (leftSensorReading + sideDistPos);
}

float resetYPositionQuad1 (float backSensorReading, float leftSensorReading) {
  return FAR_DIST - (backSensorReading + backDistPos);
}

void resetPositionQuad1 (float backSensorReading, float leftSensorReading, float Heading) {
  float correctX = resetXPositionQuad1(backSensorReading, leftSensorReading);
  float correctY = resetYPositionQuad1(backSensorReading, leftSensorReading);
  chassis.set_coordinates(correctX, correctY, Heading);
}

float resetXPositionQuad2 (float backSensorReading, float leftSensorReading) {
  return (backSensorReading + backDistPos) - FAR_DIST;
}

float resetYPositionQuad2 (float backSensorReading, float leftSensorReading) {
  return FAR_DIST - (leftSensorReading + sideDistPos);
}

void resetPositionQuad2 (float backSensorReading, float leftSensorReading, float Heading) {
  float correctX = resetXPositionQuad2(backSensorReading, leftSensorReading);
  float correctY = resetYPositionQuad2(backSensorReading, leftSensorReading);
  chassis.set_coordinates(correctX, correctY, Heading);
}

float resetXPositionQuad3 (float backSensorReading, float leftSensorReading) {
  return (leftSensorReading + sideDistPos) - FAR_DIST;
}

float resetYPositionQuad3 (float backSensorReading, float leftSensorReading) {
  return (backSensorReading + backDistPos) - FAR_DIST;
}

void resetPositionQuad3 (float backSensorReading, float leftSensorReading, float Heading) {
  float correctX = resetXPositionQuad3(backSensorReading, leftSensorReading);
  float correctY = resetYPositionQuad3(backSensorReading, leftSensorReading);
  chassis.set_coordinates(correctX, correctY, Heading);
}

float resetXPositionQuad4 (float backSensorReading, float leftSensorReading) {
  return FAR_DIST - (backSensorReading + backDistPos);
}

float resetYPositionQuad4 (float backSensorReading, float leftSensorReading) {
  return (leftSensorReading + sideDistPos) - FAR_DIST;
}

void resetPositionQuad4 (float backSensorReading, float leftSensorReading, float Heading) {
  float correctX = resetXPositionQuad4(backSensorReading, leftSensorReading);
  float correctY = resetYPositionQuad4(backSensorReading, leftSensorReading);
  chassis.set_coordinates(correctX, correctY, Heading);
}

//automatically turns to the angle needed and resets the position
void autoResetPosition() {
  XCoord = chassis.get_X_position();
  YCoord = chassis.get_Y_position();
  Heading = chassis.get_absolute_heading();
  updateQuadrant(XCoord, YCoord);
  updateHeading(Heading);

  if (in_quad_1) {
    chassis.turn_to_angle(180);
    wait (100, msec);
    float backActual = BackDist.value() / 25.4;
    float leftActual = LeftDist.value() / 25.4;
    resetPositionQuad1(backActual, leftActual, 180);
  }
  else if (in_quad_2) {
    chassis.turn_to_angle(90);
    wait (100, msec);
    float backActual = BackDist.value() / 25.4;
    float leftActual = LeftDist.value() / 25.4;
    resetPositionQuad2(backActual, leftActual, 90);
  }
  else if (in_quad_3) {
    chassis.turn_to_angle(0);
    wait (100, msec);
    float backActual = BackDist.value() / 25.4;
    float leftActual = LeftDist.value() / 25.4;
    resetPositionQuad3(backActual, leftActual, 0);
  }
  else if (in_quad_4) {
    chassis.turn_to_angle(270);
    wait (100, msec);
    float backActual = BackDist.value() / 25.4;
    float leftActual = LeftDist.value() / 25.4;
    resetPositionQuad4(backActual, leftActual, 270);
  }
}

void horizontalResetPosition() {
  XCoord = chassis.get_X_position();
  YCoord = chassis.get_Y_position();
  Heading = chassis.get_absolute_heading();


  float backActual = BackDist.value() / 25.4;
  float leftActual = LeftDist.value() / 25.4;
  
  if (Heading > 350 && Heading < 10) {
    float correctedX = (-72) + (leftActual + sideDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else if (Heading > 170 && Heading < 190) {
    float correctedX = 72 - (leftActual + sideDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else {
    float correctedX = XCoord;
    chassis.set_coordinates(correctedX, YCoord, Heading);
  }
}


/* ODOM MOTIONS */

void straightline_to_pose(float x, float y, float driveVolt, float headingVolt, int settleError, int settleTime, int Timeout, bool negative) {
    float actualX = chassis.get_X_position();
    float actualY = chassis.get_Y_position();
    if (negative) {
      chassis.drive_distance(-get_hypot(x, y, actualX, actualY), get_heading(x, y, actualX, actualY)+180, driveVolt, headingVolt, settleError, settleTime, Timeout);
    } else {
      chassis.drive_distance(get_hypot(x, y, actualX, actualY), get_heading(x, y, actualX, actualY), driveVolt, headingVolt, settleError, settleTime, Timeout);
    }
}

void straightline_to_pose(float x, float y, float driveVolt, float headingVolt, int settleError, int settleTime, int Timeout) {
    float actualX = chassis.get_X_position();
    float actualY = chassis.get_Y_position();
    chassis.drive_distance(get_hypot(x, y, actualX, actualY), get_heading(x, y, actualX, actualY), driveVolt, headingVolt, settleError, settleTime, Timeout);

}

void straightline_to_pose(float x, float y, float driveVolt) {
    float actualX = chassis.get_X_position();
    float actualY = chassis.get_Y_position();
    chassis.drive_distance(get_hypot(x, y, actualX, actualY), get_heading(x, y, actualX, actualY), driveVolt, 0);

}


float get_hypot(float desiredX, float desiredY, float actualX, float actualY) {
    float differenceX = desiredX - actualX;
    float differenceY = desiredY - actualY;
    float hypotDist = sqrt(pow((differenceX), 2) + pow((differenceY), 2));
    return hypotDist;
}

float get_heading(float desiredX, float desiredY, float actualX, float actualY) {
    float differenceX = desiredX - actualX;
    float differenceY = desiredY - actualY;

    if (differenceX == 0) {
      differenceX = 0.00001; //to avoid undef
    }

    float headingCorrection = atan2(differenceY, differenceX) * 180.0 / M_PI;

    if (differenceX >= 0 && differenceY >= 0) {
      return (90 - headingCorrection); //quad 1
    } else if (differenceX <= 0 && differenceY >= 0) {
      return (90 - headingCorrection); //quad 2
    } else if (differenceX <= 0 && differenceY <= 0) {
      return (270 - headingCorrection + 180); //quad 3
    } else if (differenceX >= 0 && differenceY <= 0) {
      return (360 - headingCorrection + 90); //quad 4
    }

    if (headingCorrection < 0) {
      headingCorrection += 360;
    }

    return headingCorrection; //for edge cases
}
