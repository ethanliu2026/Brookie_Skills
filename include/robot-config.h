using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

extern motor LF;
extern motor LM;
extern motor LB;
extern motor RF;
extern motor RM;
extern motor RB;
extern motor_group Intake;
extern motor IntakeTop;
extern motor IntakeBottom;
extern controller Controller1;
extern rotation RS;
extern rotation VertOdom;
extern rotation HorizOdom;
extern distance SortDist;
extern distance BackDist;
extern distance LeftDist;
extern optical SortOptical;
extern digital_out Hood;
extern digital_out LeftHook;
extern digital_out UpperIntakeLift;
extern digital_out LowerIntakeLift;
extern digital_out MatchLoader;
extern digital_out OdomLift;
extern inertial IMU;
extern distance rightDist;

extern int current_auton_selection;
//Add your devices below, and don't forget to do the same in robot-config.cpp:

void  vexcodeInit( void );