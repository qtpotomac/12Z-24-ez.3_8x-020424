#pragma once
#include "EZ-Template/drive/drive.hpp"
#include "main.h"

// -- Motors --
extern pros::Motor puncher1;
extern pros::Motor puncher2;
extern bool puncher_toggle;

// -- Pneumatics -- 
extern pros::ADIDigitalOut wingL;
extern pros::ADIDigitalOut wingR;
extern bool leftWing_toggle;
extern bool rightWing_toggle;

extern pros::ADIDigitalOut intake1;
extern pros::ADIDigitalOut intake2;
extern bool intake_toggle;

extern pros::ADIDigitalOut hang;
extern bool hang_toggle;

// -- Sensors -- 
extern pros::Controller master;
