#include "main.h"
#include "devices.hpp"

// -- Motors --
pros::Motor puncher1 (5, true);
pros::Motor puncher2 (6, true);
bool puncher_toggle = false;

// -- Pneumatics --
pros::ADIDigitalOut wingL('F');
pros::ADIDigitalOut wingR ('E');
pros::ADIDigitalOut intake1('H');
pros::ADIDigitalOut intake2('G');
pros::ADIDigitalOut hang('C');

// -- Toggle Functions (for autos) -- 
bool leftWing_toggle = false;
bool rightWing_toggle = false;
bool intake_toggle = false;
bool hang_toggle = false;


pros::Controller master(pros::E_CONTROLLER_MASTER);