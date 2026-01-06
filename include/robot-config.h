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
extern motor IntakeMid;
extern motor IntakeBottom;
extern controller Controller1;
extern rotation RS;
extern distance SortDist;
extern distance BackDist;
extern distance LeftDist;
extern distance rightDist;
extern optical SortOptical;
extern digital_out Hood;
extern digital_out LeftHook;
extern digital_out IntakeLift;
extern digital_out MatchLoader;
extern inertial IMU;


//Add your devices below, and don't forget to do the same in robot-config.cpp:

void  vexcodeInit( void );