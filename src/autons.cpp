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
  chassis.set_drive_constants(12, 0.87, 0, 7, 0);
  chassis.set_heading_constants(12, 0.4, 0, 1, 0);
  chassis.set_turn_constants(12, 0.36, 0.0, 2.1, 15);
  //chassis.set_turn_constants(12, 0.37, 0.01, 2, 15);
  chassis.set_swing_constants(12, .4, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 500, 3000);
  chassis.set_turn_exit_conditions(1, 500, 3000);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */


void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 6;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 1;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
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
  //chassis.drive_distance(24);
  odom_constants();
  chassis.set_coordinates(24, -24, 0);
  //chassis.turn_to_point(12, 12);
  //chassis.turn_to_point(12, 12, 90);
  //chassis.drive_to_point(0,0);
  //chassis.turn_to_angle(0);
  /*while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    Brain.Screen.printAt(5,120, "Heading: %f", chassis.Gyro.rotation());
    task::sleep(20);
  } */
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
  chassis.set_coordinates(-15.2, -49.5, -90);
  startRedAutonTasks();
  //intakeLift.suspend();
  LeftHook.set(true);
  hood_down = true;
  straightline_to_pose(-46, -49.5, 12, 0, 0.5, 470, 490);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 280, 320);
  Intake.spin(forward, 12.7, volt);
  rightHorizontalResetPosition();
  straightline_to_pose(-48, -61.3, 6, 1, 1, 340, 370);
  chassis.drive_distance(12, 180, 2, 6, 3, 110, 120); //stay to intake
  chassis.drive_distance(-30, 180, 12, 6, 1, 390, 410);
  chassis.drive_distance(-6, 180, 5, 6, 1, 70, 90); //aligning with long goal
  chassis.set_coordinates(-48, -28.7, chassis.get_absolute_heading());
  hood_down = false;
  scoreTopGoal(740);
  matchloader_down = false;
  Intake.stop();  
  chassis.drive_distance(15, 180, 12.7, 6, 1, 270, 300); 
  hood_down = true;
  chassis.turn_to_point(-22.7, -23, 0, 10, 5, 250, 300); //turn to three pile
  Intake.spin(forward, 12.7, volt);
  //straightline_to_pose(-22, 20, 12, 0, 1, 350, 380);
  chassis.drive_distance(21, chassis.get_absolute_heading(), 12, 0, 1, 300, 320);
  matchloader_down = true;
  straightline_to_pose(-22.7, -24, 6, 6, 1, 250, 300);
  matchloader_down = false;
  chassis.drive_to_point(12.6, -23, 6, 12, 6, 1, 450, 470);
  matchloader_down = true;
  chassis.drive_distance(10, chassis.get_absolute_heading(), 7, 0, 1, 360, 370);
  matchloader_down = false;
  chassis.drive_to_point(47, -39.5, 0, 10, 5, 1, 550, 600);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 200, 250);
  horizontalResetPosition();
  straightline_to_pose(48, -19.8, 5, 3, 0.1, 510, 530, true);
  chassis.set_coordinates(48, -28.7, chassis.get_absolute_heading()); 
  hood_down = false;
  scoreTopGoal(12.7, volt);
  chassis.turn_to_angle(180, 9, 1, 200, 250);
  scoreTopGoal(320);
  Intake.spin(reverse, 2, volt);
  hood_down = true;
  scoreTopGoal(12.7, volt);
  straightline_to_pose(48, -62, 5, 0.2, 1, 470, 490);
  chassis.drive_distance(13, 180, 2, 1, 3, 380, 390); //stay to intake */
  chassis.drive_distance(-10, 180, 10, 0, 3, 220, 250);
  matchloader_down = false;
  IntakeTop.spin(reverse, 3, volt);
  IntakeBottom.spin(forward, 12.7, volt);
  //intakeLift.resume();
  chassis.turn_to_point(8, -13.3, 0, 10, 8, 220, 260); //turn to low goal
  Intake.stop();
  intake_lift = true;
  LowerIntakeLift.set(true);
  straightline_to_pose(8, -13.8, 10, 6, 0.1, 780, 820);
  Intake.spin(reverse, 6, volt);
  chassis.drive_distance(12, chassis.get_absolute_heading(), 2, 1, 3, 180, 200); //align
  chassis.drive_stop(brake);



  /*chassis.drive_stop(brake);
  hood_down = false;
  matchloader_down = false;
  scoreTopGoal(12.7, volt);
  wait(200, msec);
  Intake.stop();
  wait(100, msec);
  scoreTopGoal(12.7, volt);*/
  

}

void fast_solo(){
  chassis.set_coordinates(0, -47.3, 90);
  startRedAutonTasks();
  resetPositionSolo();
  //intakeLift.suspend();
  LeftHook.set(true);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  //chassis.drive_with_voltage(12.7, 12.7);
  //wait(300, msec);
  chassis.drive_distance(8, 0, 12, 0, 3, 330, 350);
  straightline_to_pose(-45, -47, 12, 5, 0.5, 570, 580, true);
  matchloader_down = true;
  chassis.turn_to_angle(180, 10, 1, 350, 370);
  Intake.spin(forward, 12.7, volt);
  rightHorizontalResetPosition();

  
  straightline_to_pose(-47.7, -62.5, 7, 5, 1, 450, 470);
  chassis.drive_with_voltage(5, 5);
  wait(90, msec);
  straightline_to_pose(-47.7, -20, 6, 5, 1, 510, 550, true);
  chassis.drive_with_voltage(-7, -7);
  //chassis.set_coordinates(-48, -28.7, chassis.get_absolute_heading());
  hood_down = false;
  scoreTopGoal(600);
  matchloader_down = false;
  Intake.stop();  
  //chassis.drive_distance(15, 180, 12.7, 6, 1, 270, 300); 
  hood_down = true;
  chassis.turn_to_point(-22.7, -26, 0, 10, 2, 430, 440); //turn to three pile


  
  Intake.spin(forward, 12.7, volt);
  straightline_to_pose(-22.7, -25, 10, 5, 1, 350, 380);
  //chassis.drive_to_point(17, -25, 8, 10, 5, 1, 450, 500);
  //chassis.drive_stop(coast);
  //matchloader_down = false;
  straightline_to_pose(25, -25.5, 12, 7, 1, 400, 450);
  matchloader_down = true;
  //chassis.drive_stop(brake);
  //chassis.drive_distance(5, chassis.get_absolute_heading(), 10, 0, 1, 280, 300);
  chassis.turn_to_point(40.3, -32, 180, 10, 1, 300, 350); 
  straightline_to_pose(40.3, -32, 12, 10, 1, 350, 400, true);
  //chassis.drive_to_point(47, -50, 0, 8, 12, 1, 600, 650);



  //swing_to_pose(47, -50, 12, 10, 200, 300, 1);
  //chassis.turn_to_point(47, -50, 0, 10, 10, 200, 250);
  //chassis.drive_to_point(47, -50, 0, 8, 12, 1, 600, 650);
  matchloader_down = true;
  chassis.turn_to_angle(180, 12, 1, 430, 450);
  horizontalResetPosition();
  straightline_to_pose(47.7, -20, 6, 6, 0.1, 450, 480, true);
  chassis.drive_with_voltage(-7, -7);
  chassis.set_coordinates(48, -28.7, chassis.get_absolute_heading()); 
  hood_down = false;
  scoreTopGoal(12.7, volt);
  chassis.turn_to_angle(180, 12, 1, 200, 250);
  scoreTopGoal(500);
  matchloader_down = true;
  IntakeTop.spin(reverse, 4, volt);
  IntakeBottom.spin(forward, 4, volt);
  straightline_to_pose(47, -63, 6, 4, 1, 450, 470);
  chassis.drive_with_voltage(5, 5);
  wait(500, msec);
  //chassis.drive_distance(12, 180, 2, 6, 3, 80, 100); //stay to intake
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  
  chassis.drive_distance(-10, 180, 12, 5, 3, 220, 250);
  horizontalResetPosition();
  matchloader_down = false;
  IntakeTop.spin(reverse, 3, volt);
  IntakeBottom.spin(forward, 12.7, volt);
  chassis.turn_to_point(10, -8, 0, 10, 8, 220, 260); //turn to low goal
  Intake.stop();
  intake_lift = true;
  LowerIntakeLift.set(true);
  straightline_to_pose(10, -8, 12, 12, 0.1, 780, 820);
  Intake.spin(reverse, 7, volt);
  chassis.drive_distance(12, chassis.get_absolute_heading(), 2, 1, 3, 180, 200); //align
  chassis.drive_stop(brake);
 
 
  

}

void left_nine_split(){
//FIELD THREE 48.4
startRedAutonTasks();
LeftHook.set(true);
chassis.set_coordinates(-17.8, -48.7, -12.9);
hood_down = true;
Intake.spin(forward, 12.7, volt);
//straightline_to_pose(-21.41, -31.1, 10, 0, 1, 350, 380);
straightline_to_pose(-22, -28.22, 10, 0, 1, 350, 380);
matchloader_down = true;
chassis.drive_distance(10, chassis.get_absolute_heading(), 4, 0, 1, 300, 380);
matchloader_down = false;
chassis.turn_to_point(-47, -8, 0, 7, 5, 200, 220);
straightline_to_pose(-47, -8, 7, 5, 1, 370, 390);
straightline_to_pose(-20, -21.7, 10, 5, 1, 320, 360, true);
matchloader_down = true;
Intake.spin(forward, 12.7, volt);
chassis.turn_to_point(-48, -47.2, 0, 9, 5, 220, 240);
straightline_to_pose(-48, -47.2, 10, 10, 1, 550, 570);
chassis.turn_to_angle(180, 9, 3, 240, 260);
rightHorizontalResetPosition();
straightline_to_pose(-48, -60, 10, 5, 1, 460, 490);
straightline_to_pose(-48, -26, 5, 1, 1, 550, 650, true);
hood_down = false;
scoreTopGoal(800);
matchloader_down = false;
IntakeTop.spin(reverse, 4, volt);
IntakeBottom.spin(forward, 4, volt);
chassis.drive_distance(16, 180, 10, 6, 3, 350, 380);
hood_down = true;
rightHorizontalResetPosition();
Intake.spin(forward, 12.7, volt);
chassis.turn_to_point(-10.5, -8, 180, 10, 3, 260, 300);
straightline_to_pose(-10.5, -8, 8, 10, 1, 670, 700, true);
Intake.spin(reverse, 12.7, volt);
wait(50, msec);
scoreMiddleGoal(7, volt);
//chassis.drive_distance(-5, chassis.get_absolute_heading(), 4, 1, 3, 180, 200); //align
wait(500, msec);
chassis.drive_to_point(-39, -33, 0, 10, 6, 1, 600, 700);
chassis.turn_to_angle(0, 10, 1, 330, 350);
LeftHook.set(false);
scoreTopGoal(12.7, volt);
chassis.drive_distance(28, 0, 6, 2, 1, 600, 650);
chassis.drive_stop(brake);
//FIELD 1
}

void right_nine_split(){
startBlueAutonTasks();
chassis.set_coordinates(18.79, -50.63, 9.85);
LeftHook.set(true);
hood_down = true;
Intake.spin(forward, 12.7, volt);
straightline_to_pose(24, -28.33, 10, 3, 1, 450, 500);
matchloader_down = true;
chassis.drive_distance(12, chassis.get_absolute_heading(), 4, 0, 1, 400, 450);
matchloader_down = false;
chassis.turn_to_point(46, -7.5, 0, 7, 5, 430, 450);
straightline_to_pose(46, -7.5, 7, 5, 1, 700, 750);
straightline_to_pose(19.98, -21.7, 10, 5, 1, 550, 650, true);
matchloader_down = true;
chassis.turn_to_point(49.5, -47.2, 0, 9, 5, 390, 420);
straightline_to_pose(49.5, -47.2, 10, 10, 1, 830, 850);
chassis.turn_to_angle(180, 9, 3, 400, 450);
horizontalResetPosition();
straightline_to_pose(48, -61, 7, 3, 1, 760, 775);
chassis.drive_with_voltage(5, 5);
wait(90, msec);
straightline_to_pose(47.7, -20, 6, 3, 1, 620, 700, true);
chassis.drive_with_voltage(-7, -7);
chassis.set_coordinates(48, -28.7, chassis.get_absolute_heading());
hood_down = false;
scoreTopGoal(650);
matchloader_down = false;
IntakeTop.spin(reverse, 4, volt);
IntakeBottom.spin(forward, 4, volt);
chassis.drive_distance(12, 180, 10, 6, 3, 420, 430); //stay to intake
Intake.stop();
hood_down = true;
horizontalResetPosition();
chassis.turn_to_point(20, -8, 0, 10, 3, 420, 450);
straightline_to_pose(20, -8, 10, 10, 1, 500, 600);
//Intake.spin(reverse, 5.5, volt);
chassis.drive_distance(24, chassis.get_absolute_heading(), 4, 1, 3, 180, 200); //align
Intake.spin(reverse, 5.5, volt);
intake_lift = true;
wait(2200, msec);
/*straightline_to_pose(35.6, -33, 10, 5, 0.1, 900, 1000, true);
chassis.turn_to_angle(180, 10, 1, 530, 560);
LeftHook.set(false);
scoreTopGoal(12.7, volt);
chassis.drive_distance(-28, 180, 4.6, 2, 1, 600, 650);
chassis.drive_stop(brake);*/
  
}

void right_four_hook(){
  startBlueAutonTasks();
  LeftHook.set(true);
  chassis.set_coordinates(18.5, -49.2, 12.7);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(18, 0, 12, 0, 1, 350, 450);
  matchloader_down = true;
  chassis.drive_distance(12, 0, 5, 0, 1, 300, 450); //slow down for three pile
  matchloader_down = false;
  MatchLoader.set(false);
  chassis.drive_to_point(48.5, -37.2, 0, 10, 4, 1, 730, 750);
  matchloader_down = true;
  chassis.turn_to_angle(180, 8, 1, 300, 400);
  horizontalResetPosition();
  straightline_to_pose(48.5, -20, 6, 6, 1, 500, 650, true);
  hood_down = false;
  Intake.spin(forward, 12.7, volt);
  wait(780, msec);
  LeftHook.set(false);
  matchloader_down = false;
  straightline_to_pose(37, -36.2, 6.5, 10, 1, 600, 700);
  auto_straightline_to_pose(37, -36.2, 6.5, 10, 1, 350, 400);
  chassis.turn_to_angle(180, 7, 0, 350, 400);
  horizontalResetPosition();
  straightline_to_pose(37, -12, 6.5, 10, 1, 600, 700, true);
  chassis.drive_stop(brake);
}



void left_four_hook(){
  //FIELD 3 48.4
  startRedAutonTasks();
  chassis.set_coordinates(-17.8, -48.7, -12.9);
  LeftHook.set(true);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(18, 0, 12, 0, 1, 280, 300);
  matchloader_down = true;
  chassis.drive_distance(12, 0, 5, 0, 1, 350, 400); //slow down for three pile
  matchloader_down = false;
  chassis.drive_to_point(-48.4, -37.2, 0, 10, 4, 1, 640, 680);
  chassis.turn_to_angle(180, 8, 1, 260, 300);
  rightHorizontalResetPosition();
  straightline_to_pose(-48, -20, 6, 6, 1, 400, 450, true);
  hood_down = false;
  scoreTopGoal(870);
  LeftHook.set(false);
  straightline_to_pose(-60, -36.2, 6.5, 10, 1, 450, 500);
  auto_straightline_to_pose(-60, -36.2, 6.5, 10, 1, 350, 400);
  chassis.turn_to_angle(180, 7, 0, 260, 300);
  rightHorizontalResetPosition();
  straightline_to_pose(-60, -12, 6.5, 10, 1, 600, 700, true);
  chassis.drive_stop(brake);

  //FIELD 1


}

void right_seven_hook(){
  startRedAutonTasks();
  LeftHook.set(true);
  chassis.set_coordinates(18.5, -49.2, 12.7);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(20, 0, 12, 0, 1, 350, 450);
  matchloader_down = true;
  chassis.drive_distance(10, 0, 4, 0, 1, 300, 450); //slow down for three pile
  //matchloader_down = false;
  //MatchLoader.set(false);
  chassis.drive_to_point(49, -37.2, 0, 10, 4, 1, 730, 750);
  matchloader_down = true;
  chassis.turn_to_angle(180, 8, 1, 350, 400);
  horizontalResetPosition();
  straightline_to_pose(48.5, -58.6, 5, 5, 1, 470, 490);
  wait(570, msec);
  straightline_to_pose(48.5, -20, 6, 6, 1, 500, 650, true);
  hood_down = false;
  Intake.spin(forward, 12.7, volt);
  wait(1400, msec);
  LeftHook.set(false);
  matchloader_down = false;
  //chassis.drive_to_point(21, 13, 0, 8, 3.5, 1, 700, 800);
  straightline_to_pose(35.6, -36.2, 6.5, 10, 1, 600, 700);
  hood_down = true;
  auto_straightline_to_pose(36, -36.2, 6.5, 10, 1, 350, 400);
  chassis.turn_to_angle(180, 7, 0, 350, 400);
  horizontalResetPosition();
  straightline_to_pose(36, -12, 6, 10, 1, 600, 700, true);
  chassis.drive_stop(brake);
}

void left_seven_hook(){
  //FIELD THREE 48.4
  startRedAutonTasks();
  chassis.set_coordinates(-17.8, -48.7, -12.9);
  LeftHook.set(true);
  hood_down = true;
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(20, 0, 12, 0, 1, 350, 450);
  matchloader_down = true;
  chassis.drive_distance(10, 0, 4, 0, 1, 300, 450); //slow down for three pile
  //matchloader_down = false;
  //MatchLoader.set(false);
  chassis.drive_to_point(-48.4, -37.2, 0, 10, 4, 1, 640, 680);
  matchloader_down = true;
  chassis.turn_to_angle(180, 8, 1, 260, 300);
  rightHorizontalResetPosition();
  straightline_to_pose(-48.4, -59, 5, 5, 1, 470, 490);
  chassis.drive_distance(12, 180, 3, 0, 5, 270, 300); //stay to intake
  straightline_to_pose(-48, -20, 6, 6, 1, 500, 650, true);
  hood_down = false;
  scoreTopGoal(1650);
  LeftHook.set(false);
  matchloader_down = false;
  //chassis.drive_to_point(21, 13, 0, 8, 3.5, 1, 700, 800);
  straightline_to_pose(-60, -36.2, 6.5, 10, 1, 450, 500);
  auto_straightline_to_pose(-60, -36.2, 6.5, 10, 1, 350, 400);
  chassis.turn_to_angle(180, 7, 0, 260, 300);
  rightHorizontalResetPosition();
  straightline_to_pose(-60, -12, 6.5, 10, 1, 600, 700, true);
  chassis.drive_stop(brake);
  
}

void skills(){
  startBlueAutonTasks();
  chassis.set_coordinates(0, -47.2, -180);
  hood_down = true;
  intake_lift = false;
  OdomLift.set(false);
  Intake.spin(forward, 12.7, volt);
  //chassis.drive_distance(20, 180, 10, 10);
  chassis.drive_distance(10, 180, 5, 10, 1, 350, 400);
  chassis.drive_distance(6, 180, 5, 10, 2, 200, 700);
  LeftHook.set(true);
  wait(300, msec);
  Intake.spin(forward, 12.7, volt);
  chassis.drive_distance(-5, 180, 7, 10, 1, 200, 700);//can be deleted
  wait(100, msec); //can be deleted
  chassis.drive_distance(8, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(300, msec); //can be deleted
  chassis.drive_distance(-6, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(100, msec); //can be deleted
  chassis.drive_distance(10, 180, 7, 10, 2, 200, 700);//can be deleted
  wait(300, msec); //can be deleted
  chassis.drive_distance(-25, 180, 10, 10, 2, 200, 800); //previously timeout 1500
  OdomLift.set(true);
  wait(10, msec);
  chassis.turn_to_angle(0, 10, 1, 700, 800); //turn to wall
  wait(100, msec);
  resetPositionSkills();

  chassis.turn_to_point(24, -22, 0, 10, 2, 350, 450); //turn to three pile
  straightline_to_pose(24, -22, 8, 3, 0.5, 500, 650);
  chassis.turn_to_point(8.5, -9, 0, 5, 0.5, 550, 750); //turn to low goal
  straightline_to_pose(8.5, -9, 12, 1, 0, 700, 1000); //drive to low goal
  scoreLowGoal(12, volt);
  wait(250, msec);
  scoreLowGoal(8, volt);
  wait(450, msec);
  scoreLowGoal(4.7, volt);
  wait(2200, msec);
  chassis.drive_distance(-20, 0, 6, 0, 2, 380, 470); 
  Intake.spin(reverse, 12.7, volt);
  chassis.turn_to_point(41, -45.3, 0, 7, 5, 400, 470);
  matchloader_down = true;
  storeBall(12, volt);
  straightline_to_pose(41., -45, 10, 10, 0.1, 650, 700); 
  chassis.turn_to_angle(180, 8, 1, 250, 350);
  wait(200, msec);
  horizontalResetPosition();
  straightline_to_pose(47, -60, 10, 6, 1, 350, 400);
  drive_time(2, 1300);
  //chassis.drive_distance(15, 180, 2, 6, 3, 1000, 1200);
  chassis.drive_distance(-10, 180, 10, 6, 3, 300, 350);
  chassis.drive_to_point(63, -30.7, 0, 5, 6, 7, 500, 650); //back to right of goal
  matchloader_down = false;
  chassis.turn_to_angle(180, 8, 1, 300, 380);
  straightline_to_pose(63, 30, 10, 0, 1, 1000, 1020, true);
  chassis.turn_to_angle(180, 2, 1, 200, 280);
  wait(200, msec);
  backLeftResetPosition();
  chassis.turn_to_point(47, 45, 180, 8, 1, 400, 540);
  straightline_to_pose(47, 45, 8, 10, 1, 400, 500, true);
  chassis.turn_to_angle(0, 7, 1, 550, 700);
  wait(200, msec);
  rightHorizontalResetPosition();
  straightline_to_pose(48, 18, 6, 1, 1, 500, 600, true);
  Intake.spin(reverse, 10, volt);
  wait(50, msec);
  scoreTopGoal(1300);  
  matchloader_down = true;
  storeBall(12, volt);
  straightline_to_pose(50, 72, 7, 6, 1, 700, 800); 
  drive_time(2, 1300);
  //chassis.drive_distance(18, 0, 2, 6, 3, 1400, 1600);
  //chassis.drive_distance(-10, 0, 10, 6, 3, 300, 350);
  straightline_to_pose(50, 20, 6, 1, 1, 700, 800, true);
  Intake.spin(reverse, 10, volt);
  wait(50, msec);
  scoreTopGoal(1300);
  matchloader_down = false;
  
  chassis.turn_to_point(24, 60, 0, 8, 0.5, 400, 500);
  straightline_to_pose(24, 60, 7, 2, 0.5, 900, 1100);
  drive_side(1, 8, 650);

  OdomLift.set(false);
  storeBall(12, volt);
  drive_time(8, 500);
  drive_time(3, 1300);
  drive_time(8, 700);
  chassis.turn_to_angle(180, 8, 1, 500, 700);
  wait(100, msec);
  OdomLift.set(true);
  backRightResetPosition();
  wait(50, msec);
  
  chassis.turn_to_point(-48, 40, 0, 8, 1, 400, 500);
  straightline_to_pose(-48, 40, 10, 8, 0.1, 900, 1020);
  chassis.turn_to_angle(0, 8, 1, 580, 600);
  horizontalResetPosition();
  straightline_to_pose(-48, 18, 6, 1, 1, 500, 600, true);
  hood_down = false;
  Intake.spin(reverse, 10, volt);
  wait(50, msec);
  scoreTopGoal(800);
  matchloader_down = true;
  storeBall(12, volt);
  straightline_to_pose(-50, 72, 7, 6, 1, 700, 800); 
  drive_time(2, 1300);
  //chassis.drive_distance(18, 0, 2, 6, 3, 1400, 1600);
  //chassis.drive_distance(-10, 0, 10, 6, 3, 300, 350);
  straightline_to_pose(-50, 25, 6, 1, 1, 700, 800, true);
  Intake.spin(reverse, 10, volt);
  hood_down = false;
  wait(50, msec);
  scoreTopGoal(1300);
  matchloader_down = false;

  straightline_to_pose(-50, 35, 10, 1, 1, 300, 400);
  storeBall(12, volt);
  chassis.turn_to_point(-27, 21, 0, 8, 1, 600, 800);
  straightline_to_pose(-27, 21, 8, 4, 1, 600, 700);
  matchloader_down = true;
  chassis.drive_distance(6, 0, 5, 0, 1, 300, 400);
  matchloader_down = false;

  chassis.turn_to_point(-26, -30, 0, 6, 1, 700, 900);
  straightline_to_pose(-26, -30, 8, 4, 1, 1000, 1300);
  matchloader_down = true;
  chassis.drive_distance(6, 0, 5, 0, 1, 300, 400);

  chassis.turn_to_angle(-135, 6, 1, 400, 600);
  //chassis.turn_to_point(-34, -40, 0, 8, 1, 600, 800);
  straightline_to_pose(-15, -12, 6, 3, 1, 600, 700, true);
  Intake.stop();
  UpperIntakeLift.set(true);
  wait(200, msec);
  scoreMiddleGoal(6, 10, 10, volt);
  wait(1200, msec);
  matchloader_down = false;

  
  chassis.turn_to_point(-50, -45, 0, 4, 1, 200, 300);
  straightline_to_pose(-50, -45, 10, 3, 1, 1000, 1100);
  storeBall(12, volt);
  matchloader_down = true;
  chassis.turn_to_angle(180, 8, 1, 600, 700);
  wait(100, msec);
  //horizontalResetPosition();
  straightline_to_pose(-50, -68, 8, 3, 1, 700, 900);
  drive_time(2, 1300);
  straightline_to_pose(-50, -20, 8, 3, 1, 700, 900, true);
  scoreTopGoal(600);
  matchloader_down = false;

  storeBall(12, volt);
  chassis.turn_to_point(-26, -61, 0, 8, 2, 400, 500);
  straightline_to_pose(-26, -61, 7, 2, 1, 800, 1000);
  drive_side(1, 8, 1000);

  OdomLift.set(false);
  drive_time(8, 800);
  
}

void straightline_test(){
  startBlueAutonTasks();
  //toggle_blue_sort = true;
  chassis.set_coordinates(0, 0, -90);
  //chassis.turn_to_angle(90, 10, 0.1, 4000, 5000);
  /*chassis.turn_to_point(20, -10, 0, 12, 5, 400, 600);
  straightline_to_pose(20, -10, 5, 5, 1, 1500, 3000);*/
  //Intake.spin(forward, 12.7, volt);
  //chassis.drive_distance(48, 0, 10, 0, 0.1, 4000, 5000);

}

void test() {
  startBlueAutonTasks();
  chassis.set_coordinates(-50, 25, 0);
  OdomLift.set(true);

  straightline_to_pose(-50, 35, 10, 1, 1, 300, 400);
  storeBall(12, volt);
  chassis.turn_to_point(-27, 16, 0, 8, 1, 600, 800);
  straightline_to_pose(-27, 16, 8, 4, 1, 600, 700);
  matchloader_down = true;
  chassis.drive_distance(6, 0, 5, 0, 1, 300, 400);
  matchloader_down = false;

  chassis.turn_to_point(-26, -25, 0, 6, 1, 700, 900);
  straightline_to_pose(-26, -25, 8, 4, 1, 1000, 1300);
  matchloader_down = true;
  chassis.drive_distance(6, 0, 5, 0, 1, 300, 400);

  chassis.turn_to_angle(-135, 6, 1, 400, 600);
  //chassis.turn_to_point(-34, -40, 0, 8, 1, 600, 800);
  straightline_to_pose(-9, -12, 6, 3, 1, 600, 700, true);
  UpperIntakeLift.set(true);
  wait(20, msec);
  scoreMiddleGoal(6, 10, 10, volt);
  wait(600, msec);
  matchloader_down = false;

  
  chassis.turn_to_point(-50, -45, 0, 4, 1, 200, 300);
  straightline_to_pose(-50, -45, 10, 3, 1, 1000, 1100);
  storeBall(12, volt);
  matchloader_down = true;
  chassis.turn_to_angle(180, 8, 1, 600, 700);
  wait(100, msec);
  //horizontalResetPosition();
  straightline_to_pose(-48, -68, 8, 3, 1, 700, 900);
  drive_time(2, 1200);
  straightline_to_pose(-48, -20, 8, 3, 1, 700, 900, true);
  scoreTopGoal(600);
  matchloader_down = false;

  chassis.turn_to_point(-26, -61, 0, 8, 2, 400, 500);
  straightline_to_pose(-26, -61, 7, 2, 1, 800, 1000);
  drive_side(1, 8, 1000);

  OdomLift.set(false);
  drive_time(8, 500);
  
}
