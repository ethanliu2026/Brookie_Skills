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

float leftDistPos = 3;//previously 3.7
float backDistPos = 4.54724409; //previously 3.0
float rightDistPos = 2.3; //previously 3.5

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
      return (leftSensorReading + leftDistPos) - FAR_DIST;
  }
  else if(facing_right) {
      return (backSensorReading + backDistPos) - FAR_DIST;
  }
  else if(facing_red) {
      return FAR_DIST - (leftSensorReading + leftDistPos); 
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
      return FAR_DIST - (leftSensorReading + leftDistPos);
  }
  else if(facing_red) {
      return FAR_DIST - (backSensorReading + backDistPos);
  }
  else if(facing_left) {
      return (leftSensorReading + leftDistPos) - FAR_DIST;
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
  return FAR_DIST - (leftSensorReading + leftDistPos);
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
  return FAR_DIST - (leftSensorReading + leftDistPos);
}

void resetPositionQuad2 (float backSensorReading, float leftSensorReading, float Heading) {
  float correctX = resetXPositionQuad2(backSensorReading, leftSensorReading);
  float correctY = resetYPositionQuad2(backSensorReading, leftSensorReading);
  chassis.set_coordinates(correctX, correctY, Heading);
}

float resetXPositionQuad3 (float backSensorReading, float leftSensorReading) {
  return (leftSensorReading + leftDistPos) - FAR_DIST;
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
  return (leftSensorReading + leftDistPos) - FAR_DIST;
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

void resetPositionSolo(){
  Heading = chassis.get_absolute_heading();


  float backActual = BackDist.value() / 25.4;
  float rightActual = rightDist.value() / 25.4;
      float correctedY = (-71) + (rightActual + rightDistPos);
      float correctedX = (-71) + (backActual + backDistPos);
      chassis.set_coordinates(correctedX, correctedY, Heading);


}

void horizontalResetPosition() {
  XCoord = chassis.get_X_position();
  YCoord = chassis.get_Y_position();
  Heading = chassis.get_absolute_heading();


  float backActual = BackDist.value() / 25.4;
  float leftActual = LeftDist.value() / 25.4;
  
  if (Heading > 350 && Heading < 370 || Heading > -10 && Heading < 10) {
    float correctedX = (-71) + (leftActual + leftDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else if (Heading > 170 && Heading < 190) {
    float correctedX = 71 - (leftActual + leftDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else {
    float correctedX = XCoord;
    chassis.set_coordinates(correctedX, YCoord, Heading);
  }
}

void backLeftResetPosition() {
  Heading = chassis.get_absolute_heading();
  float backActual = BackDist.value() / 25.4;
  float leftActual = LeftDist.value() / 25.4;
  float correctedX = FAR_DIST - (leftActual + leftDistPos);
  float correctedY = FAR_DIST - (backActual + backDistPos);
  chassis.set_coordinates(correctedX, correctedY, Heading);
}

void backRightResetPosition() {
  Heading = chassis.get_absolute_heading();
  float backActual = BackDist.value() / 25.4;
  float leftActual = rightDist.value() / 25.4;
  float correctedX = - FAR_DIST + (leftActual + rightDistPos);
  float correctedY = FAR_DIST - (backActual + backDistPos);
  chassis.set_coordinates(correctedX, correctedY, Heading);
}

void rightHorizontalResetPosition() {
  XCoord = chassis.get_X_position();
  YCoord = chassis.get_Y_position();
  Heading = chassis.get_absolute_heading();
  chassis.drive_stop(brake);

  float rightActual = rightDist.value() / 25.4;

  if (Heading > -10 && Heading < 10 || Heading > 350 && Heading < 370) {
    float correctedX = (71) - (rightActual + rightDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else if (Heading > 170 && Heading < 190) {
    float correctedX = (-71) + (rightActual + rightDistPos);
    chassis.set_coordinates(correctedX, YCoord, Heading);
  } else {
    float correctedY = YCoord;
    chassis.set_coordinates(XCoord, correctedY, Heading);
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

void swing_to_pose(float x, float y, float swingVolt, int settleError, int settleTime, int Timeout, int direction) {
    float actualX = chassis.get_X_position();
    float actualY = chassis.get_Y_position();

    if (direction == 1) {
      chassis.left_swing_to_angle(get_heading(x, y, actualX, actualY), swingVolt, settleError, settleTime, Timeout, 0.37, 0.01, 2, 15);
    } else if (direction == 0) {
      chassis.right_swing_to_angle(get_heading(x, y, actualX, actualY), swingVolt, settleError, settleTime, Timeout, 0.37, 0.01, 2, 15);
    }
}

float angle_difference(float target, float current) {
        float diff = target - current;
        while (diff > 180) diff -= 360;
        while (diff < -180) diff += 360;
        return diff;
    }

void auto_straightline_to_pose(float x, float y, float driveVolt, float headingVolt, int settleError, int settleTime, int Timeout) {
    float actualX = chassis.get_X_position();
    float actualY = chassis.get_Y_position();
    float botHeading = chassis.get_absolute_heading();
    float headingToPoint = get_heading(x, y, actualX, actualY);
    float angleTol = 20;

    
   if (headingToPoint <= botHeading + angleTol && headingToPoint >= botHeading - angleTol) {
        // Move forwards
        chassis.drive_distance(get_hypot(x, y, actualX, actualY), headingToPoint, driveVolt, headingVolt, settleError, settleTime, Timeout);
    } else if (headingToPoint >= botHeading + 180 - angleTol && headingToPoint <= botHeading + 180 + angleTol) {
        // Move backwards
        chassis.drive_distance(-get_hypot(x, y, actualX, actualY), headingToPoint + 180, driveVolt, headingVolt, settleError, settleTime, Timeout);
    } else {
        // Do not move
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


// Drives straight for a set time at a given voltage, with IMU heading correction
void drive_time(float voltage, int timeMs) {
    float targetHeading = chassis.get_absolute_heading();
    float kP = 0.05; // heading correction gain, tune as needed
    int elapsed = 0;
    int dt = 10; // ms per loop

    while (elapsed < timeMs) {
        float headingError = targetHeading - chassis.get_absolute_heading();
        while (headingError > 180)  headingError -= 360;
        while (headingError < -180) headingError += 360;

        float correction = kP * headingError;
        LF.spin(forward, voltage + correction, volt);
        LM.spin(forward, voltage + correction, volt);
        LB.spin(forward, voltage + correction, volt);
        RF.spin(forward, voltage - correction, volt);
        RM.spin(forward, voltage - correction, volt);
        RB.spin(forward, voltage - correction, volt);

        wait(dt, msec);
        elapsed += dt;
    }

    LF.stop(brake); LM.stop(brake); LB.stop(brake);
    RF.stop(brake); RM.stop(brake); RB.stop(brake);
}

// Spins one side of the drivetrain at a given voltage for a set time
// side: 0 = left, 1 = right
void drive_side(int side, float voltage, int timeMs) {
    if (side == 0) {
        LF.spin(forward, voltage, volt);
        LM.spin(forward, voltage, volt);
        LB.spin(forward, voltage, volt);
        wait(timeMs, msec);
    } else if (side == 1) {
        RF.spin(forward, voltage, volt);
        RM.spin(forward, voltage, volt);
        RB.spin(forward, voltage, volt);
        wait(timeMs, msec);
    }

    chassis.drive_stop(brake);
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
