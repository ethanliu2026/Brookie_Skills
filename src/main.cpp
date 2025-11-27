#include "JAR-Template/drive.h"
#include "autons.h"
#include "motion.h"
#include "vex.h"
#include "tasks.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
TANK_TWO_ROTATION,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(LF, LM, LB),

//Right Motors:
motor_group(RF, RM, RB),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT4,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.15,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
354,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
PORT18,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.02,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-1.5,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
PORT20,

//Sideways tracker diameter (reverse to make the direction switch):
-2.81,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
2.6

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  
  chassis.set_coordinates(0, -47.5,180);
  while (!auto_started){


    
    /* BATTERY */
   /*Controller1.Screen.setCursor(3,18);
    Controller1.Screen.print(Brain.Battery.capacity());
    Controller1.Screen.setCursor(3,20);
    Controller1.Screen.print("%"); */


    /* DRIVE TEMP */
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Drive:");
    Controller1.Screen.setCursor(1,8);
    Controller1.Screen.print((RF.temperature(celsius)+RM.temperature(celsius)+RB.temperature(celsius)+LF.temperature(celsius)+LM.temperature(celsius)+LB.temperature(celsius))/6);

    /* INTAKE TEMP */
    Controller1.Screen.setCursor(1,14);
    Controller1.Screen.print("Top:");
    Controller1.Screen.setCursor(1, 19);
    Controller1.Screen.print((int)(IntakeTop.temperature(celsius)+0.5));

    Controller1.Screen.setCursor(2,1);
    Controller1.Screen.print("Mid:");
    Controller1.Screen.setCursor(2,6);
    Controller1.Screen.print((int)(IntakeMid.temperature(celsius)+0.5));

    /* COLOR SORT */
    Controller1.Screen.setCursor(2,10);
    Controller1.Screen.print("Sort:");
    Controller1.Screen.setCursor(2,16);
    Controller1.Screen.print(getColorSortState().c_str());


    /* AUTON SELECTION */
    /*
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Blue SOLO");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("BSOLO");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Red SOLO");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RSOLO");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Blue LEFT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("BLQ");
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Red LEFT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RQ");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Blue RIGHT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("BRQ");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Red RIGHT Qual");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RRQ");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Blue LEFT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("BLE");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Red LEFT Elim");
        Controller1.Screen.clearLine(3);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print("AUTON:");
        Controller1.Screen.setCursor(3,8);
        Controller1.Screen.print("RLE");
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
    */
    if(Controller1.ButtonRight.pressing() || Brain.Screen.pressing()){
      //while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
      vexDelay(250);
    } else if (current_auton_selection == 13){
      current_auton_selection = 0;
    }

  

    /* BRAIN SCREEN */
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
    task::sleep(10);
  } 
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  auto_started = true;
  Controller1.Screen.clearScreen();
  autonControllerDisplay.resume();
  skills();
  //IMU.calibrate();
  /*
  switch(current_auton_selection){ 
    case 0:
      straightline_test();
      break;
    case 1:         
      red_solo();
      break;
    case 2:
      blue_left_qual();
      break;
    case 3:
      red_left_qual();
      break;
    case 4:
      blue_right_qual();
      break;
    case 5:
      red_right_qual();
      break;
    case 6:
      blue_left_elim();
      break;
    case 7:
      red_left_elim();
      break;
    case 8:
      blue_right_elim();
      break;
    case 9:
      red_right_elim();
      break;
    case 10:
      skills();
      break;
    case 11:
      drive_test();
      break;
    case 12:
      odom_test();
      break;
      
 }
      */
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    auto_started = false;
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_arcade();
    //vexcodeInit();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
