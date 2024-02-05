#include "autons.hpp"
#include "devices.hpp"
#include "drivercontrol.hpp"
#include "main.h"
#include "api.h"

/* -- Quentin Toner -- EZ-temp3.0.0 -- 2/4/2024 
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

      1111111     222222222222222     ZZZZZZZZZZZZZZZZZZZ
     1::::::1    2:::::::::::::::22   Z:::::::::::::::::Z
    1:::::::1    2::::::222222:::::2  Z:::::::::::::::::Z
    111:::::1    2222222     2:::::2  Z:::ZZZZZZZZ:::::Z 
       1::::1                2:::::2  ZZZZZ     Z:::::Z  
       1::::1                2:::::2          Z:::::Z    
       1::::1             2222::::2          Z:::::Z     
       1::::l        22222::::::22          Z:::::Z      
       1::::l      22::::::::222           Z:::::Z       
       1::::l     2:::::22222             Z:::::Z        
       1::::l    2:::::2                 Z:::::Z         
       1::::l    2:::::2       222222  ZZ:::::Z     ZZZZZ
    111::::::111 2:::::222222222::::2 Z::::::ZZZZZZZZ:::Z
    1::::::::::1 2::::::::::::::::::2 Z:::::::::::::::::Z
    111111111111 22222222222222222222 ZZZZZZZZZZZZZZZZZZZ

-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

// -- Chassis constructor --
ez::Drive chassis (
  {-1,2,-3,4}
  // Right Chassis Ports (negative port will reverse it!)
  ,{-7,8,-9,10}
  // IMU Port
  ,5
  // Wheel Diameter
  ,2.75
  // Cartridge RPM
  ,600 // (blue cartridge)
  // External Gear Ratio (MUST BE DECIMAL)
  // eg. 60:36 RATIO = 1.66... , 36:36 RATIO = 1
  ,1 // (36:36 RATIO = 1) 
  //radio is port 
);



/**
 * Runs initialization code. This occurs as soon as the program is started */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    // Auton("Example Drive\n\nDrive forward 24 and come back.", drive_example),
    // Auton("Example Turn\n\nTurn 3 times.", turn_example),
    // Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    // Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    // Auton("Combine all 3 movements", combining_movements),
    // Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
    // Auton("Swing Test 90",swing_test),
    Auton("Setup for:\n\ntest\n\n   SETUP\n\n          pg. 1", test),
    Auton("Run:\n\nL-OffGoal\n\n mid rush\n\n          pg. 2    2", L_offG_midRush),
    Auton("Run:\n\nL-OffGoal\n\n Preload NO RUSH\n\n          pg. 3   3   3", L_offG_Preload),

    Auton("Run:\n\nR-OnGoal\n\n 4 Ball\n\n          pg. 4  4  4  4", R_on_goal4ball)
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or the VEX Competition Switch, following either autonomous or opcontrol. */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task */
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
}



/**
 * Runs the operator control code. This function will be started in its own task */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(pros::E_MOTOR_BRAKE_COAST);
  wingL.set_value(false);
  wingR.set_value(false);
  intake1.set_value(false);
  intake2.set_value(false);
  while (true) {
    // // PID Tuner
    // // After you find values that you're happy with, you'll have to set them in auton.cpp
    // if (!pros::competition::is_connected()) { 
    //   // Enable / Disable PID Tuner
    //   //  When enabled: 
    //   //  * use A and Y to increment / decrement the constants
    //   //  * use the arrow keys to navigate the constants
    //   if (master.get_digital_new_press(DIGITAL_X)) 
    //     chassis.pid_tuner_toggle();
        
    //   // Trigger the selected autonomous routine
    //   if (master.get_digital_new_press(DIGITAL_B)) 
    //     autonomous();

    //   chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    // } 

    chassis.opcontrol_tank(); // Tank control
    // chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    
  //---- Controller Buttons ----
    // -- Wings --
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        left_wing(); }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        right_wing(); }

    // -- Pneumatic Intake --
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake_(); }

    // -- Hang --
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        hang_(); }

    // -- Puncher --
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        puncher_(); }


    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
