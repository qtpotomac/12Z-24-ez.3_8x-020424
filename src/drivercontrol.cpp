#include "main.h"
#include "devices.hpp"
#include <math.h>

// -- Toggles -- 
void left_wing() {
  leftWing_toggle = !leftWing_toggle;
  if (leftWing_toggle) {
    wingL.set_value(true); }
  else {
    wingL.set_value(false); }
}

void right_wing() {
  rightWing_toggle = !rightWing_toggle;
  if (rightWing_toggle) {
    wingR.set_value(true); }
  else {
    wingR.set_value(false); }
}

void intake_() { // for controller
  intake_toggle = !intake_toggle;
  if (intake_toggle) {
    intake1.set_value(true); 
    intake2.set_value(true); }
  else {
    intake1.set_value(false);
    intake2.set_value(false); }
}

void hang_() {
  hang_toggle = !hang_toggle;
  if (hang_toggle) {
    hang.set_value(true); }
  else {
    hang.set_value(false);}
}

void puncher_() {
  puncher_toggle = !puncher_toggle;
  if (puncher_toggle) {
    puncher1.move_velocity(100);
    puncher2.move_velocity(-100);
    }
  else {
    puncher1.set_brake_mode(MOTOR_BRAKE_COAST);
    puncher2.set_brake_mode(MOTOR_BRAKE_COAST);

    puncher1.brake();
    puncher2.brake();
    }
}

