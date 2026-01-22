#include "autons.h"
#include "functions.h"
#include "motion.h"
#include "vex.h"
#include "tasks.h"
#include "vex_global.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */


void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  //chassis.set_drive_constants(10, 1.8, 0, 11, 0);
  //chassis.set_drive_constants(10, 1.18, 0.005, 13, 0);
  chassis.set_drive_constants(12, 1, 0.05, 8, 1.5);
  //tiff: chassis.set_drive_constants(12, 1.0, 0.01, 17, 0);
  //chassis.set_drive_constants(10, 2.78, 0.005, 40, 0);
  //chassis.set_drive_constants(10, 1.3, 0, 10.345, 0);
  //chassis.set_drive_constants(10, 1.72, 0, 10.245, 0);
  chassis.set_heading_constants(12, .4, 0, 1, 0);
  //chassis.set_turn_constants(12, .4, .03, 2.86, 15);
  chassis.set_turn_constants(12, .23, 0.01, 1.6, 15);
  //chassis.set_turn_constants(12, .5, 0.021, 3, 15);
  //chassis.set_turn_constants(12, .6, 0.021, 3.05, 15);
  chassis.set_swing_constants(12, .4, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  //chassis.set_drive_exit_conditions(1.5, 500, 3000);
  chassis.set_drive_exit_conditions(3, 500, 2000);
  //chassis.set_drive_exit_conditions(1.5, 500, 3000); //original
  chassis.set_turn_exit_conditions(2, 200, 1500);
  //chassis.set_turn_exit_conditions(1, 500, 3000); //original
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */


void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

void skills() {
  startBlueAutonTasks();
  chassis.set_coordinates(0, -47.2, -180);
  hood_down = true;
  intake_lift = false;
  IntakeLift.set(false);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(14, 180, 5, 10);
  chassis.drive_distance(9, 180, 2, 10, 1, 350, 400);
  //wait(100, msec);
  //chassis.drive_distance(-7, 180, 7, 10, 2, 200, 1000);
  //wait(200, msec);
  chassis.drive_distance(6, 180, 5, 10, 2, 200, 700);
  wait(300, msec);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(-5, 180, 7, 10, 2, 200, 700);//can be deleted
  Intake.spin(reverse, 6, volt);
  wait(100, msec);
  Intake.spin(forward, 12.7, volt);
  wait(100, msec); //can be deleted
  chassis.drive_distance(7, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(300, msec); //can be deleted
  chassis.drive_distance(-30, 180, 10, 10, 2, 200, 800); //previously timeout 1500

  chassis.turn_to_angle(0, 10, 1, 450, 500); //turn to wall
  resetPositionSkills();
  
  //chassis.turn_to_point(21.9, -30, 0, 6, 5, 350, 450); //turn to three pile
  //straightline_to_pose(21.9, -30, 8, 6, 1, 500, 650); //drive to three pile
  chassis.turn_to_point(23.3, -22.5, 0, 10, 3, 350, 450); //turn to three pile
  straightline_to_pose(23.3, -22.5, 8, 3, 0.5, 500, 650);
  //chassis.drive_to_point(22.3, -22., 0, 8, 6, 0.5, 500, 650); //drive to three pile, -27
  chassis.turn_to_point(11.3, -10.3, 0, 5, 0.5, 350, 450); //turn to low goal
  straightline_to_pose(11.3, -10.3, 12, 3, 0.5, 450, 650); //drive to low goal
  intake_lift = true;
  //chassis.drive_distance(1, 0, 3, 0, 0.2, 80, 100);
  IntakeBottom.spin(reverse, 7, volt);
  chassis.drive_distance(-0.5, 0, 5, 0, 1, 320, 380);
  IntakeMid.spin(reverse, 8, volt);
  wait(300, msec); //350
  scoreLowSkills();
  wait(2200, msec); //2680
  Intake.spin(forward, 4, volt);
  wait(300, msec);
  scoreLowSkills();
  wait(400, msec); 
  IntakeBottom.spin(reverse, 2, volt);
  IntakeMid.spin(reverse, 5, volt);
  IntakeTop.spin(reverse, 7, volt);
  wait(1200, msec);
  /*IntakeBottom.spin(reverse, lowVolt, volt);
  IntakeMid.spin(reverse, 9, volt);
  IntakeTop.spin(reverse, 4, volt);
  wait(280, msec); //2680*/
  chassis.drive_distance(-20, 0, 6, 0, 2, 380, 470); //back away from low goal
  Intake.spin(reverse, 12.7, volt);
  intake_lift = false;
  chassis.turn_to_point(46.2, -45.3, 0, 7, 5, 400, 470);
  matchloader_down = true;
  Intake.spin(forward, 12.7, volt);
  straightline_to_pose(46.2, -45.3, 8, 10, 0.1, 550, 600); //drive to matchloader 1
  chassis.turn_to_angle(180, 8, 1, 250, 350); //turn to matchloader 1)
  horizontalResetPosition();
  straightline_to_pose(47.7, -60, 5, 3, 1, 350, 400);
  //chassis.drive_distance(15, 180, 10, 6, 3, 350, 400);

  hood_down = true;
  chassis.drive_distance(10, 180, 3, 6, 3, 1000, 1100); //stay to intake
  chassis.drive_distance(-10, 180, 10, 6, 3, 300, 350);
  matchloader_down = false;
  chassis.drive_to_point(59.8, -30.7, 0, 5, 6, 7, 500, 650); //back to right of goal
  chassis.turn_to_angle(180, 8, 1, 300, 380);
  straightline_to_pose(59.8, 30.7, 10, 0, 1, 800, 920, true);
  //chassis.drive_to_point(45.2, 36, 4, 5, 6, 7, 800, 1000);
  verticalResetPosition();
  horizontalResetPosition();
  chassis.turn_to_point(48, 39, 180, 8, 1, 300, 340); //turn to goal 1 alignment point
  straightline_to_pose(48, 39, 8, 10, 1, 400, 500, true);
  chassis.turn_to_angle(0, 7, 1, 450, 500);
  rightHorizontalResetPosition();
  straightline_to_pose(47.7, 18, 6, 1, 1, 500, 600, true); //approach long goal 1st time
  scoreTopGoal(1600);
  //chassis.set_coordinates(48, 27, chassis.get_absolute_heading());
  matchloader_down = true;
  //chassis.turn_to_angle(0);
  rightHorizontalResetPosition();
  hood_down = true;
  straightline_to_pose(47.7, 56, 7, 6, 1, 400, 500); //drive to first matchloader

  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(14, 1, 3, 6, 3, 670, 1170); //stay to intake, originally 15
  straightline_to_pose(48, 18, 6, 1, 1, 500, 600, true); //approach long goal 2nd time
  chassis.drive_distance(-6, 0, 5, 0, 1, 100, 150); 
  scoreTopGoal(1600);
  matchloader_down = false;
  chassis.drive_distance(6, 0, 10, 0, 1, 200, 300);
  rightHorizontalResetPosition();
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_to_point(-0.5, 35, 0, 8, 6, .1, 1200, 1450); //drive to parking zone 2
  chassis.turn_to_angle(0, 10, 1, 280, 350);
  straightline_to_pose(0, 47.2, 10, 4, 0.1, 400, 500); //700
  //intake_lift = false;
  Intake.spin(forward, 12, volt);
  chassis.drive_distance(30, 0, 5, 10);
  wait(100, msec);
  chassis.drive_distance(-7, 0, 7, 10, 2, 200, 500);
  wait(200, msec);
  chassis.drive_distance(8, 0, 7, 10, 2, 200, 700);//can be deleted
  wait(100, msec); //can be deleted
  chassis.drive_distance(-5, 0, 7, 10, 2, 200, 700);//can be deleted
  wait(100, msec); //can be deleted
  chassis.drive_distance(8, 0, 7, 10, 2, 200, 700);//can be deleted
  wait(100, msec); //can be deleted
  chassis.drive_distance(-30, 0, 10, 10, 2, 200, 800); //previously timeout 1500
  chassis.turn_to_angle(180, 10, 1, 400, 450); //distance reset turn
  resetPositionSkills();
  chassis.turn_to_point(-48, 40, 0, 8, 1, 300, 400); //turn to matchloader 2
  straightline_to_pose(-48, 40, 10, 8, 0.1, 800, 920);
  chassis.turn_to_angle(0, 7, 1, 350, 400);
  horizontalResetPosition();
  //chassis.drive_to_point(-48, 18, 5, 12, 7, 0.1, 450, 550); //approach matchloader 2
  straightline_to_pose(-48, 18, 6, 6, 1, 650, 700, true); //approach 2nd long goal
  matchloader_down = true;
  scoreTopGoal(1600);
  //chassis.set_coordinates(-48, 27, chassis.get_absolute_heading());
  //horizontalResetPosition();
  //chassis.drive_to_point(-49.2, 64, 6, 8, 1, 3, 350, 400);
  straightline_to_pose(-47.7, 56, 7, 6, 0.1, 400, 500); //drive to second matchloader
  //chassis.drive_distance(37, 3, 8, 1, 3, 350, 400);
  
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  
  chassis.drive_distance(14, 1, 3, 6, 3, 690, 1190); //stay to intake, originally 15
  straightline_to_pose(-48, 18, 6, 1, 1, 600, 700, true);
  chassis.drive_distance(-6, 0, 5, 0, 1, 100, 150); //aligning with long goal
  scoreTopGoal(1600);
  matchloader_down = false;
  chassis.drive_distance(20, 0, 10, 0, 1, 300, 350);
  horizontalResetPosition();
  chassis.drive_to_point(-60, 37, 0, 5, 6, 7, 550, 650); //back to right of goal
  chassis.turn_to_angle(0, 7, 1, 300, 350);
  straightline_to_pose(-60., -29, 10, 1, 1, 800, 950, true);
  verticalResetPosition();
  horizontalResetPosition();

  chassis.turn_to_point(-48., -42, 180, 8, 1, 300, 340);
  straightline_to_pose(-48., -42, 8, 8, 1, 400, 500, true); 
  
  
  matchloader_down = true;
  
  chassis.turn_to_angle(180, 7, 1, 300, 500);
  rightHorizontalResetPosition();
  straightline_to_pose(-47.8, -56, 6, 1, 1, 500, 600); //approach matchloader 4
  
  
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(10, 0, 3, 0, 1, 600, 1100); //stay to intake
  straightline_to_pose(-48., -18, 7, 1, 1, 500, 600, true); //approach long goal 1st time
  //chassis.drive_distance(-21.5, 0, 7, 7, 1, 500, 600); //back into goal
  scoreTopGoal(680);
  matchloader_down = false;
  Intake.spin(forward, 12.7, volt);
  //chassis.drive_distance(15, 0, 12, 0, 1, 300, 400);
  chassis.drive_to_point(-20, -59, 12.5, 12.5, 7, 5, 500, 600);
  //straightline_to_pose(0, -67, 11.5, 10, 1, 400, 500);
  chassis.drive_to_point(0, -67, 10.5, 12.5, 6.5, 1, 1000, 1200);

  

  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    Brain.Screen.printAt(5, 140, "Chassis Heading Rotation Reading:");
    Brain.Screen.printAt(5, 160, "%f", IMU.rotation());
    Brain.Screen.printAt(5, 180, "x, y:");
    Brain.Screen.printAt(5, 200, "%f", chassis.get_X_position());
    Brain.Screen.printAt(5, 220, "%f", chassis.get_Y_position());
  }
    
}
/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(24);
  //chassis.drive_distance(12);
  //chassis.drive_distance(18);
  //chassis.drive_distance(-36);
  
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  //chassis.turn_to_point(12, 12);
  //chassis.turn_to_point(12, 12, 90);
  //chassis.drive_to_point(0,0);
  //chassis.turn_to_angle(0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    Brain.Screen.printAt(5,120, "Heading: %f", IMU.rotation());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  //chassis.drive_distance(16, 90, 10, 6, 3, 680, 680);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}


void straightline_test(){
  startBlueAutonTasks();
  //toggle_blue_sort = true;
  //chassis.set_coordinates(0, 0, -90);
  chassis.drive_distance(48);
  /*chassis.turn_to_point(20, -10, 0, 12, 5, 400, 600);
  straightline_to_pose(20, -10, 5, 5, 1, 1500, 3000);*/
  //Intake.spin(forward, 12.7, volt);

}


