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
  chassis.set_drive_constants(12, 1, 0.1, 8, 1.5);
  //tiff: chassis.set_drive_constants(12, 1.0, 0.01, 17, 0);
  //chassis.set_drive_constants(10, 2.78, 0.005, 40, 0);
  //chassis.set_drive_constants(10, 1.3, 0, 10.345, 0);
  //chassis.set_drive_constants(10, 1.72, 0, 10.245, 0);
  chassis.set_heading_constants(12, .4, 0, 1, 0);
  //chassis.set_turn_constants(12, .4, .03, 2.86, 15);
  chassis.set_turn_constants(12, .3, 0.01, 1.6, 15);
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

void skillsAuto() {
  
}

void skills() {
  chassis.set_coordinates(0, -47.2, -180);
  Hood.set(true);
  IntakeLift.set(false);
  Intake.spin(forward, 12, volt);
  chassis.drive_distance(30, 180, 5, 10);
  wait(100, msec);
  chassis.drive_distance(-7, 180, 7, 10, 2, 200, 1000);
  wait(200, msec);
  chassis.drive_distance(15, 180, 5, 10, 2, 200, 700);
  wait(500, msec);
  chassis.drive_distance(-5, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(200, msec); //can be deleted
  chassis.drive_distance(8, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(300, msec); //can be deleted
  chassis.drive_distance(-30, 180, 10, 10, 2, 200, 800); //previously timeout 1500

  chassis.turn_to_angle(0, 7, 1, 700, 1000);
  resetPositionSkills();
  //autoResetPosition();
  wait(300, msec);
  chassis.turn_to_point(20, -25, 0, 6, 5, 450, 600);
  straightline_to_pose(20, -25, 8, 6, 1, 550, 700); //58 degrees, 20.88, -31.30
  //chassis.drive_to_point(20, -25, 6, 8, 7, 1, 550, 700);
  
  wait(300, msec);
  Intake.stop();
 //chassis.turn_to_angle(316);
 // chassis.drive_distance(11.8, 316, 8, 10, 1.5, 300, 800);
  chassis.turn_to_point(11.5, -15, 0, 5, 2, 400, 600);
  straightline_to_pose(11.5, -15, 10, 6, 0.5, 700, 1500);
  chassis.drive_distance(-2);

  Intake.spin(forward, 12, volt);
  wait(100, msec);
  IntakeLift.set(true);
  LF.stop(hold);
  LM.stop(hold);
  LB.stop(hold);
  RF.stop(hold);
  RM.stop(hold);
  RB.stop(hold);
  scoreLowSkills();
  wait(3500, msec);
  Intake.stop();
  
  chassis.drive_distance(-10);
  IntakeLift.set(false);
  //chassis.turn_to_point(48, -48, 0, 5, 4, 500, 600);

  //straightline_to_pose(48, -48, 12, 6, 1, 550, 800);
  //MatchLoader.set(true);
  //Intake.spin(forward);
  //chassis.turn_to_point(48, -72, 0, 5, 4, 400, 600);
  
  //wait(3000, msec);


  //straightline_to_pose(0, 0, 12);
  //chassis.turn_to_angle(270);
  //MatchLoader.set(false);
  //straightline_to_pose(0, 0, 12);
  //autoResetPosition();
  //chassis.turn_to_angle(180);
  //straightline_to_pose(0, 0, 12);
  //autoResetPosition(); //can be deleted
  //chassis.turn_to_angle(90);
  //straightline_to_pose(0, 0, 12);
  //chassis.turn_to_angle(0);
  //straightline_to_pose(0, 0, 12);
  //Hood.set(false);
  //Intake.spin(forward, 12, volt);
  //wait(4000, msec);
  //MatchLoader.set(true);
  //straightline_to_pose(0, 0, 12);
  //Hood.set(true);
  //wait(4000, msec);
  //straightline_to_pose(0, 0, 12);
  //Hood.set(false);
  //wait(4000, msec);

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

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */


void blue_solo(){
  startBlueAutonTasks();
  /*chassis.set_coordinates(0, 0, -90); //calibrating start pos
  chassis.drive_distance(32, -90, 12.7, 10, 0.5, 450, 500);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 300);
  chassis.drive_distance(12, 180, 10, 6, 3, 350, 400); //drive to matchloader
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(12, 180, 3, 6, 3, 280, 300); //stay to intake
  chassis.drive_distance(-30, 184, 10, 6, 1, 460, 480);
  chassis.drive_distance(-6, 180, 5, 6, 1, 100, 150); //aligning with long goal
  hood_down = false;
  Intake.spin(forward, 12.7, volt); //scoring long goal
  toggle_blue_sort = true;
  wait(1100, msec); 
  matchloader_down = false;
  Intake.stop();
  chassis.drive_distance(15, 180, 12, 6, 1, 350, 450); 
  hood_down = true;
  toggle_blue_sort = false;
  chassis.turn_to_angle(63, 8, 1, 300, 350); //turn to three pile
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(24, 63, 10, 0, 1, 400, 410);
  matchloader_down = true;
  chassis.drive_distance(10.2, 63, 5, 0, 1, 200, 250); //slow down to not push balls
  wait(600, msec);
  Intake.stop();
  chassis.turn_to_angle(-147, 6, 1, 300, 350); //turn to middle goal
  chassis.drive_distance(-12, -147, 7, 10, 1, 300, 350);
  chassis.drive_stop(brake);
  scoreMiddleGoal(8.5, volt); 
  wait(1100, msec);
  chassis.drive_distance(16.4, 0, 10, 0, 1, 400, 450); //drive forward
  matchloader_down = false;
  chassis.turn_to_angle(93, 10, 1, 250, 300); //turn to low goal three pile
  chassis.drive_distance(35, 92, 10, 10, 1, 450, 500);
  scoreTopGoal(12.7, volt);
  matchloader_down = true;
  chassis.drive_distance(10, 96, 6, 5, 6, 300, 320); //slow down to not push balls x2
  wait(250, msec);
  matchloader_down = false;
  chassis.turn_to_angle(-35, 8, 1, 350, 400); //turn to low goal
  Intake.stop();
  chassis.drive_distance(12.5, -35, 6, 5, 6, 320, 340); //drive to low goal
  Intake.spin(reverse, 9.5, volt);
  chassis.drive_stop(brake);*/



  /*chassis.set_coordinates(0, 0, -90); //calibrating start pos
  chassis.drive_distance(32, -90, 12.7, 10, 0.5, 450, 500);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 300);
  chassis.drive_distance(12, 180, 10, 6, 3, 350, 400); //drive to matchloader
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(12, 180, 3, 6, 3, 250, 270); //stay to intake
  chassis.drive_distance(-30, 184, 10, 6, 1, 460, 480);
  chassis.drive_distance(-6, 180, 5, 6, 1, 100, 150); //aligning with long goal
  hood_down = false;
  Intake.spin(forward, 12.7, volt); //scoring long goal
  toggle_red_sort = true;
  wait(1100, msec); 
  matchloader_down = false;
  Intake.stop();
  chassis.drive_distance(15, 180, 12, 6, 1, 350, 450); 
  hood_down = true;
  toggle_red_sort = false;
  chassis.turn_to_angle(63.3, 8, 1, 300, 350); //turn to three pile
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(24, 63.3, 10, 0, 1, 400, 410);
  matchloader_down = true;
  chassis.drive_distance(10.2, 63.3, 5, 0, 1, 200, 250); //slow down to not push balls
  wait(600, msec);
  Intake.stop();
  chassis.turn_to_angle(-145, 6, 1, 300, 350); //turn to middle goal
  chassis.drive_distance(-12.4, -145, 7, 10, 1, 300, 350);
  chassis.drive_stop(brake);
  scoreMiddleGoal(5, 5, 12.7, volt);
  //scoreMiddleGoal(8.5, volt); 
  wait(1200, msec);
  IntakeTop.spin(forward, 12.7, volt);
  IntakeMid.spin(reverse, 12.7, volt); 
  chassis.drive_distance(16.4, 0, 10, 0, 1, 400, 450); //drive forward
  matchloader_down = false;
  chassis.turn_to_angle(93, 10, 1, 250, 300); //turn to low goal three pile
  Intake.stop();
  IntakeBottom.spin(forward, 12.7, volt);
  IntakeMid.spin(forward, 5, volt);
  chassis.drive_distance(35, 92, 10, 10, 1, 450, 500);
  matchloader_down = true;
  chassis.drive_distance(10.4, 96, 6, 5, 6, 300, 320); //slow down to not push balls x2
  wait(180, msec);
  matchloader_down = false;
  chassis.turn_to_angle(-35, 8, 1, 350, 400); //turn to low goal
  Intake.stop();
  Intake.spin(reverse, 5.5, volt);
  IntakeLift.set(true);
  chassis.drive_distance(19, -35, 8.5, 5, 6, 350, 360); //drive to low goal
  //intake_lift = true;

  chassis.drive_stop(brake); */


  //NANJING OLD FIELD
  chassis.set_coordinates(0, 0, -90); //calibrating start pos
  chassis.drive_distance(27.8, -90, 12.7, 10, 0.5, 450, 500);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 300);
  chassis.drive_distance(10.4, 180, 10, 6, 3, 380, 400); //drive to matchloader
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(12, 180, 2, 6, 3, 270, 290); //stay to intake
  chassis.drive_distance(-30, 181, 10, 6, 1, 460, 480);
  chassis.drive_distance(-6, 180, 5, 6, 1, 100, 150); //aligning with long goal
  hood_down = false;
  Intake.spin(forward, 12.7, volt); //scoring long goal
  toggle_red_sort = true;
  wait(1000, msec); 
  matchloader_down = false;
  Intake.stop();
  chassis.drive_distance(15, 180, 12, 6, 1, 350, 450); 
  hood_down = true;
  toggle_red_sort = false;
  chassis.turn_to_angle(69.3, 8, 1, 300, 350); //turn to three pile
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(24, 63.3, 10, 0, 1, 400, 410);
  matchloader_down = true;
  chassis.drive_distance(10.2, 63.3, 5, 0, 1, 200, 250); //slow down to not push balls
  wait(600, msec);
  Intake.stop();
  chassis.turn_to_angle(-140.8, 6, 1, 350, 400); //turn to middle goal
  chassis.drive_distance(-13.1, -144, 7, 0, 1, 350, 380);
  chassis.drive_stop(brake);
  scoreMiddleGoal(5, 5, 12.7, volt);
  //scoreMiddleGoal(8.5, volt); 
  wait(1000, msec);
  scoreMiddleGoal(8.5, 5, 12.7, volt);
  wait(200,msec);
  IntakeTop.spin(forward, 12.7, volt);
  IntakeMid.spin(reverse, 12.7, volt); 
  chassis.drive_distance(16.4, 0, 10, 0, 1, 400, 450); //drive forward
  matchloader_down = false;
  chassis.turn_to_angle(93, 10, 1, 250, 300); //turn to low goal three pile
  Intake.stop();
  IntakeBottom.spin(forward, 12.7, volt);
  chassis.drive_distance(37.4, 92, 10, 10, 1, 450, 500);
  matchloader_down = true;
  chassis.drive_distance(10.4, 96, 6, 5, 6, 300, 320); //slow down to not push balls x2
  wait(180, msec);
  matchloader_down = false;
  chassis.turn_to_angle(-35, 8, 1, 350, 400); //turn to low goal
  Intake.stop();
  Intake.spin(reverse, 5.5, volt);
  IntakeLift.set(true);
  chassis.drive_distance(19, -35, 8.5, 5, 6, 350, 360); //drive to low goal
  //intake_lift = true;

  chassis.drive_stop(brake);

  

}

void red_solo() {
  startRedAutonTasks();
  chassis.set_coordinates(0, 0, -90);
  /*  straightline_to_pose(-32.8, 0, 12, 0, 1, 450, 750);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 300);
  chassis.drive_distance(7.8, 180, 10, 0, 3, 350, 400); //drive to matchloader
  chassis.drive_distance(-30, 180, 10, 0, 1, 460, 480);
  chassis.drive_distance(-6, 180, 5, 6, 1, 100, 150); //aligning with long goal
  chassis.set_coordinates(-32.8, 20.1, chassis.get_absolute_heading());
  chassis.drive_distance(15, 180, 12, 6, 1, 350, 450); 
  chassis.turn_to_point(-16, 18.);
  straightline_to_pose(-6, 18, 10);
  chassis.turn_to_point(4, 34, 180);
  straightline_to_pose(4, 34, 6, 0, 1, 700, 1000, true);
  chassis.turn_to_angle(231);
  chassis.drive_distance(-5, 231, 12, 6, 1, 350, 450); */






  /*
  //NANJING NEW FIELD
  startRedAutonTasks();
  chassis.set_coordinates(0, 0, -90); //calibrating start pos
  chassis.drive_distance(32.3, -90, 12.7, 10, 0.5, 450, 500);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 300);
  chassis.drive_distance(10.8, 180, 10, 0, 3, 350, 400); //drive to matchloader
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(12, 180, 2, 6, 3, 250, 270); //stay to intake
  chassis.drive_distance(-30, 180, 10, 6, 1, 460, 480);
  chassis.drive_distance(-6, 180, 5, 6, 1, 100, 150); //aligning with long goal
  hood_down = false;
  Intake.spin(forward, 12.7, volt); //scoring long goal
  //toggle_red_sort = true;
  wait(1100, msec); 
  matchloader_down = false;
  Intake.stop();
  chassis.drive_distance(15, 180, 12, 6, 1, 350, 450); 
  hood_down = true;
  //toggle_red_sort = false;
  chassis.turn_to_angle(63.3, 8, 1, 300, 350); //turn to three pile
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(24, 61, 10, 0, 1, 400, 410);
  matchloader_down = true;
  chassis.drive_distance(10.2, 63.3, 5, 0, 1, 220, 270); //slow down to not push balls
  wait(600, msec);
  Intake.stop();
  chassis.turn_to_angle(-136.2, 6, 1, 300, 350); //turn to middle goal
  chassis.drive_distance(-13.5, -136.2, 7, 6, 1, 350, 380);
  chassis.drive_stop(brake);
  scoreMiddleGoal(9, 9, 12.7, volt);
  //scoreMiddleGoal(8.5, volt); 
  wait(1200, msec);
  IntakeTop.spin(forward, 12.7, volt);
  IntakeMid.spin(reverse, 12.7, volt); 
  chassis.drive_distance(16.4, 0, 10, 0, 1, 400, 450); //drive forward
  matchloader_down = false;
  chassis.turn_to_angle(93, 10, 1, 250, 300); //turn to low goal three pile
  Intake.stop();
  IntakeBottom.spin(forward, 12.7, volt);
  chassis.drive_distance(38.7, 92, 10, 10, 1, 450, 500);
  matchloader_down = true;
  chassis.drive_distance(10.4, 92, 6, 5, 6, 300, 320); //slow down to not push balls x2
  wait(180, msec);
  matchloader_down = false;
  chassis.turn_to_angle(-35, 8, 1, 350, 400); //turn to low goal
  Intake.stop();
  Intake.spin(reverse, 5.5, volt);
  IntakeLift.set(true);
  chassis.drive_distance(19, -35, 8.5, 5, 6, 350, 360); //drive to low goal
  //intake_lift = true;

  chassis.drive_stop(brake);
  */

}

void blue_left_qual(){
  startBlueAutonTasks();

}

void red_left_qual(){
  startRedAutonTasks();
  chassis.set_coordinates(0, 0, -10.2);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(18, 0, 10, 0, 1, 350, 400);
  matchloader_down = true;
  chassis.drive_distance(10.7, 0, 4, 0, 1, 400, 450); //slow down for three pile
  chassis.turn_to_angle(-131.4, 7, 1, 300, 320); //turn to mid goal
  chassis.drive_distance(-16.4, -131.4, 7, 0, 1, 400, 450); //back up
  Intake.stop();
  scoreMiddleGoal(12.7, 12.7, 12.7, volt); //score mid goal
  wait(850, msec);
  Intake.stop();
  IntakeTop.spin(forward, 12.7, volt);
  IntakeMid.spin(reverse, 12.7, volt); //reverse ball if needed
  matchloader_down = false;
  chassis.drive_distance(4, -130, 10, 6, 1, 150, 200);
  chassis.turn_to_angle(-73, 7, 1, 300, 320); //turn to under goal
  Intake.stop();
  scoreTopGoal(12.7, volt);
  chassis.drive_distance(26.2, -73, 7, 6, 1, 400, 450); //drive to 2 under goal
  wait(150, msec);
  matchloader_down = true;
  chassis.turn_to_angle(-64, 3, 1, 250, 300); //micro adjustment (wobble)
  chassis.drive_distance(-14, -65, 10, 10, 1, 450, 500);
  chassis.turn_to_angle(220, 4, 1, 300, 320); //turn to matchloader
  matchloader_down = false;
  chassis.drive_distance(41.7, 220, 12, 10, 1, 500, 530); //drive to matchloader
  matchloader_down = true;
  chassis.turn_to_angle(-172, 10, 1, 200, 250); //turn to face matchloader 172 to compensate
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(9.4, -172, 6, 10, 1, 350, 400);
  wait(240, msec);
  chassis.drive_distance(-35, -175, 8, 0, 1, 500, 550); //drive to long goal
  wait(100, msec);
  hood_down = false;


}

void blue_right_qual(){
  startBlueAutonTasks();
  
  //NANJING NEW FIELD
  LeftHook.set(true);
  chassis.set_coordinates(0, 0, 13.5);
  hood_down = true;
  IntakeBottom.spin(forward, 12.7, volt);
  chassis.drive_distance(18, 0, 10, 0, 1, 350, 600);
  matchloader_down = true;
  chassis.drive_distance(10.7, 0, 4, 0, 1, 400, 650); //slow down for three pile
  matchloader_down = false;
  MatchLoader.set(false);
  chassis.turn_to_angle(-43, 7, 1, 300, 620); //turn to loq goal
  chassis.drive_distance(16.2, -43, 7, 6, 1, 400, 650); 
  Intake.stop();
  Intake.spin(reverse, 9, volt);
  IntakeLift.set(true);
  wait(700, msec);
  Intake.stop();
  wait(80, msec);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(-7.2, -40, 8.5, 5, 6, 400, 610);
  Intake.stop();
  IntakeLift.set(false);
  chassis.turn_to_angle(68.2, 10, 1, 300, 650);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(23.95, 68.2, 7, 6, 1, 400, 650); //drive to 2 under goal
  matchloader_down = true;
  MatchLoader.set(true);
  wait(300, msec);
  chassis.drive_stop(brake);
  chassis.turn_to_angle(48, 3, 1, 250, 600); //micro adjustment (wobble)
  chassis.drive_distance(-14, 48, 8, 10, 1, 450, 600);
  chassis.turn_to_angle(144, 4, 1, 600, 650); //turn to matchloader
  chassis.drive_distance(37.7, 144, 10, 10, 1, 580, 700); //drive to matchloader
  wait(80, msec);
  chassis.turn_to_angle(176, 10, 1, 200, 400);
  chassis.drive_distance(10.6, 176, 6, 10, 1, 350, 600);
  wait(270, msec);
  chassis.drive_distance(-35, 175, 8, 8, 1, 500, 650); //drive to long goal
  wait(50, msec);
  IntakeMid.spin(reverse, 6.5, volt);
  wait(80, msec);
  Intake.spin(forward, 12.7, volt);
  hood_down = false;
  
}

void red_right_qual(){

  //NANJING OLD FIELD
  startRedAutonTasks();
  chassis.set_coordinates(0, 0, 13.5);
  hood_down = true;
  IntakeBottom.spin(forward, 12.7, volt);
  chassis.drive_distance(18, 0, 10, 0, 1, 350, 400);
  matchloader_down = true;
  chassis.drive_distance(10.7, 0, 4, 0, 1, 400, 550); //slow down for three pile
  matchloader_down = false;
  MatchLoader.set(false);
  chassis.turn_to_angle(-43, 7, 1, 300, 320); //turn to mid goal
  chassis.drive_distance(16.2, -43, 7, 6, 1, 400, 450); 
  Intake.stop();
  Intake.spin(reverse, 7, volt);
  IntakeLift.set(true);
  wait(780, msec);
  Intake.stop();
  wait(80, msec);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(-7.2, -40, 8.5, 5, 6, 400, 510);
  Intake.stop();
  IntakeLift.set(false);
  chassis.turn_to_angle(68.2, 10, 1, 300, 450);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(24, 68.2, 7, 6, 1, 400, 550); //drive to 2 under goal
  matchloader_down = true;
  MatchLoader.set(true);
  wait(300, msec);
  chassis.drive_stop(brake);
  chassis.turn_to_angle(51.5, 3, 1, 250, 300); //micro adjustment (wobble)
  chassis.drive_distance(-14, 51.5, 8, 10, 1, 450, 500);
  chassis.turn_to_angle(144, 4, 1, 600, 650); //turn to matchloader
  chassis.drive_distance(41, 144, 10, 10, 1, 580, 620); //drive to matchloader
  wait(80, msec);
  chassis.turn_to_angle(175, 10, 1, 200, 250);
  chassis.drive_distance(7.3, 175, 6, 10, 1, 350, 400);
  wait(260, msec);
  chassis.drive_distance(-35, 175, 8, 10, 1, 500, 550); //drive to long goal
  wait(50, msec);
  IntakeMid.spin(reverse, 6.5, volt);
  wait(80, msec);
  Intake.spin(forward, 12.7, volt);
  hood_down = false;

  /*
  chassis.drive_distance(42.5, 220, 12, 10, 1, 500, 530); //drive to matchloader
  matchloader_down = true;
  chassis.turn_to_angle(-172, 10, 1, 200, 250); //turn to face matchloader 172 to compensate
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(11, -172, 6, 10, 1, 350, 400);
  wait(240, msec);
  chassis.drive_distance(-35, -172, 10, 10, 1, 500, 550); //drive to long goal
  wait(100, msec);
  hood_down = false;*/
  
}

void blue_left_elim(){
  startBlueAutonTasks();

}

void red_left_elim(){
  startRedAutonTasks();

}

void blue_right_elim(){
  startBlueAutonTasks();
  
}

void red_right_elim(){
  startRedAutonTasks();
  
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


