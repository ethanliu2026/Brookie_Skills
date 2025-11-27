#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void straightline_test();

void blue_solo();
void blue_left_qual();
void blue_right_qual();
void blue_left_elim();
void blue_right_elim();

void red_solo();
void red_left_qual();
void red_right_qual();
void red_left_elim();
void red_right_elim();

void skills();
void skillsAuto();