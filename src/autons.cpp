#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 115;  
const int TURN_SPEED = 80;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}


///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 30
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(30);  // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 30 speed
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 

// ---- Auton Functions ----
// chassis.pid_drive_set("target inches"_in, max speed of 127, slew t/f)"
// chassis.pid_turn_set("target degrees"_deg, TURN_SPEED);
// chassis.pid_wait("null for full, or distance for part");

// ---------------- Autons ---------------- 
void test() {
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
}
void setup_LoffGmidRush() {
  //setup robot in reverse orientation
  chassis.drive_angle_set(180);
  chassis.pid_turn_set(196.75, TURN_SPEED); // 196.75 from jerry
  chassis.pid_wait();
  chassis.pid_drive_set(-3_in, DRIVE_SPEED); 
  chassis.pid_wait();
}

void L_offG_midRush() {
  //running after setup_LoffGmidRush
  chassis.drive_angle_set(196.75);
  wingL.set_value(true); //flick ball towards goal
  pros::delay(200);
  wingL.set_value(false);
  pros::delay(200);
  intake1.set_value(true); //prep for intaking mid rush
  intake2.set_value(true);
  
  chassis.pid_drive_set(54.6875_in, 127); //mid rush to triball 120/127
  chassis.pid_wait_until(50_in);
  chassis.pid_speed_max_set(30); //After driving 75,slow to 30 speed
  chassis.pid_wait();
  pros::delay(300);
  intake1.set_value(false); //collect triball
  intake2.set_value(false);
  pros::delay(200);
  chassis.pid_speed_max_set(100);
  pros::delay(300);
  chassis.pid_drive_set(-46.6875_in, DRIVE_SPEED); //come back
  chassis.pid_wait();
  
  pros::delay(200);
  chassis.pid_turn_set(305_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, 50); 
  chassis.pid_wait();
  
  chassis.pid_swing_set(ez::RIGHT_SWING, 355_deg, SWING_SPEED, 0);
  chassis.pid_wait();
  chassis.pid_drive_set(-5.5_in, 50); // Push triball backwards into goal
  chassis.pid_wait();
  chassis.pid_turn_set(359_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(10.5_in, DRIVE_SPEED); // turn and exit goal area
  chassis.pid_wait();
  
  chassis.pid_turn_set(180_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, TURN_SPEED); //turn in prep push triball out of corner
  chassis.pid_wait();
  wingL.set_value(true); //flick out triball from the corner

  chassis.pid_drive_set(-22_in, DRIVE_SPEED); 
  chassis.pid_wait();
  chassis.pid_turn_set(91_deg, 100);
  chassis.pid_wait();
  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();
  
  intake1.set_value(true); //open so triball rolls out at end
  intake2.set_value(true);
  chassis.pid_drive_set(24_in, DRIVE_SPEED); //go to touch the bar
  chassis.pid_wait();
  chassis.pid_turn_set(295_deg, TURN_SPEED);
  chassis.pid_wait();
}



void L_offG_Preload() {
  //running after setup_LoffGmidRush
  chassis.drive_angle_set(196.75);
  wingL.set_value(true); //flick ball towards goal
  pros::delay(200);
  wingL.set_value(false);
  
  pros::delay(200);
  chassis.pid_drive_set(7.25_in, DRIVE_SPEED); // skip going to midrush
  chassis.pid_wait();
  
  pros::delay(200);
  chassis.pid_turn_set(305_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-23_in, 50);
  chassis.pid_wait();
  chassis.pid_swing_set(ez::RIGHT_SWING, 355_deg, SWING_SPEED,0);
  chassis.pid_wait();
  chassis.pid_drive_set(-5.5_in, 50); // Push triball backwards into goal
  chassis.pid_wait();
  chassis.pid_turn_set(359_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(10.5_in, DRIVE_SPEED); // turn and exit goal area
  chassis.pid_wait();
  
  chassis.pid_turn_set(180_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, TURN_SPEED); //turn in prep flick triball out of corner
  chassis.pid_wait();
  wingL.set_value(true); //flick out triball from the corner

  chassis.pid_drive_set(-24_in, DRIVE_SPEED); 
  chassis.pid_wait();
  chassis.pid_turn_set(91_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(270_deg, TURN_SPEED);
  chassis.pid_wait();
  
  chassis.pid_drive_set(20_in, DRIVE_SPEED); //go to touch the bar
  chassis.pid_wait();
  chassis.pid_turn_set(295_deg, TURN_SPEED);
  chassis.pid_wait();
}





void R_on_goal4ball() {
  chassis.drive_angle_set(90);
//get triball under bar
  intake1.set_value(true); 
  intake2.set_value(true);
  chassis.pid_drive_set(2.5_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(500);
  intake1.set_value(false); 
  intake2.set_value(false);
  pros::delay(500);
  //go to match load area
  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait();
  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();
  //get matchload out
  wingL.set_value(true);
  chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait(); 
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.pid_drive_set(-2_in, DRIVE_SPEED);
  chassis.pid_wait();
  // chassis.set_turn_pid(270, TURN_SPEED);
  // chassis.wait_drive();
  chassis.pid_turn_set(-180_deg, TURN_SPEED);
  chassis.pid_wait();
  // //score the first three
  wingL.set_value(false);
  wingR.set_value(true);
  intake1.set_value(true);
  intake2.set_value(true);
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();
  // chassis.set_drive_pid(-10, DRIVE_SPEED);
  // chassis.wait_drive();
  // // get the last triball
  // chassis.set_turn_pid(270, TURN_SPEED);
  // chassis.wait_drive();
  // chassis.set_drive_pid(60, DRIVE_SPEED);
  // chassis.wait_drive();
  // intake1.set_value(true); 
  // intake2.set_value(true);
  // pros::delay(200);
  // intake1.set_value(false); 
  // intake2.set_value(false);
  // chassis.set_turn_pid(90, TURN_SPEED);
  // chassis.wait_drive();
  // //goes back to score the last triball
  // chassis.set_drive_pid(-60, DRIVE_SPEED);
  // chassis.wait_drive();
  // chassis.set_turn_pid(180, TURN_SPEED);
  // chassis.wait_drive();
  // intake1.set_value(true); 
  // intake2.set_value(true);
  // pros::delay(200);
  // chassis.set_drive_pid(10, DRIVE_SPEED);
  // chassis.wait_drive();
  // //
}
// . .  .