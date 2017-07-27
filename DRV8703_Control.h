/*
  DRV8703_Control.h - Library for Controlling DRV8703.
  Created by Ashlyn Frahm
  Released into the public domain.
*/
#ifndef DRV8703_Control_h
#define DRV8703_Control_h

#include "Arduino.h"

class DRV8703_Control
{
  public:
    DRV8703_Control(int in1, int in2, int n_sleep, int mode);
    void forward_with_speed(uint8_t motor_speed);
    void reverse_with_speed(uint8_t motor_speed);
    void test_ramp_up_down_forward(int ramp_time);
    void test_ramp_up_coast_down_forward();
    void test_ramp_up_brake_forward();
    enum MotorMode { MOTOR_COAST, MOTOR_FWD, MOTOR_BRAKE, MOTOR_REV };
    void motorWrite(MotorMode motor_mode, uint8_t motor_speed);
    void brake();
    void coast();

  private:
    int _in1;
    int _in2;
    int _n_sleep;
    int _mode;
};

#endif