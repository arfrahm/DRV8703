/*
  DRV8703_pwm.cpp - Library for Controlling DRV8703 EVM.
  Created by Ashlyn R Frahm
  Released into the public domain.
*/

#include "Arduino.h"
#include "DRV8703_Control.h"

DRV8703_Control::DRV8703_Control(int in1, int in2, int n_sleep, int mode)
{
  pinMode(in1, OUTPUT);   // sets the pin as output
  pinMode(in2, OUTPUT);   // sets the pin as output
  pinMode(n_sleep, OUTPUT);   // sets the pin as output
  pinMode(mode, INPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(n_sleep, LOW);
  delay(1000);
  digitalWrite(n_sleep, HIGH);
  _in1 = in1;
  _in2 = in2;
  _n_sleep = n_sleep;
  _mode = mode;
}

void DRV8703_Control::motorWrite(MotorMode motor_mode, uint8_t motor_speed){
  
  
  /*
  
  from section 7.3.1.1 for details
  Table 5. DRV870x-Q1 Standard PWM Control Interface (MODE = Hi-Z)
    nSLEEP IN1/PH IN2/EN GH1 GL1 SH1 GH2 GL2 SH2 AVDD/DVDD DESCRIPTION
    0 X X X X Hi-Z X X Hi-Z Disabled Sleep mode H bridge disabled Hi-Z
    1 0 0 0 0 Hi-Z 0 0 Hi-Z Enabled Coast H bridge disabled Hi-Z
    1 0 1 0 1 L 1 0 H Enabled Reverse (Current SH2 → SH1)
    1 1 0 1 0 H 0 1 L Enabled Forward (Current SH1 → SH2)
    1 1 1 0 1 L 0 1 L Enabled Brake low-side slow decay
  */
  switch (motor_mode){
    case MOTOR_COAST:
      analogWrite(_in1, 0 );
      analogWrite(_in2, 0);
      Serial.println("coasted");
      break;
    case MOTOR_FWD:
        analogWrite(_in1, motor_speed);
        analogWrite(_in2, 0);
      break;
    case MOTOR_REV: //best to comment out unused cases so that the default triggers
        analogWrite(_in1, 0);
        analogWrite(_in2, motor_speed);
      break;
    case MOTOR_BRAKE:
        analogWrite(_in1, 255);
        analogWrite(_in2, 255);
      break;
    default: //default to coast
      analogWrite(_in1, 0);
      analogWrite(_in2, 0);
      break;
  }
}

void DRV8703_Control::test_ramp_up_down_forward(int ramp_time){
  int steps = 25;
  uint8_t max_speed = 128;
  int ramp_time_ms = ramp_time;
  for(int i = 0; i < steps; ++i){
   motorWrite(MOTOR_FWD, map(i, 0, steps, 0, max_speed));
   delay(ramp_time_ms/steps);
  }
  for(int i = 0; i < steps; ++i){
   motorWrite(MOTOR_FWD, map(i, 0, steps, max_speed, 0));
   delay(ramp_time_ms/steps);
  }
}

void DRV8703_Control::test_ramp_up_coast_down_forward(){
  int steps = 25;
  uint8_t max_speed = 128;
  int ramp_time_ms = 3000;
  for(int i = 0; i < steps; ++i){
   motorWrite(MOTOR_FWD, map(i, 0, steps, 0, max_speed));
   delay(ramp_time_ms/steps);
  }
  motorWrite(MOTOR_COAST, 0);
  delay(3000);
}

void DRV8703_Control::test_ramp_up_brake_forward(){
  int steps = 25;
  uint8_t max_speed = 64;
  int ramp_time_ms = 3000;
  for(int i = 0; i < steps; ++i){
   motorWrite(MOTOR_FWD, map(i, 0, steps, 0, max_speed));
   delay(ramp_time_ms/steps);
  }
  motorWrite(MOTOR_BRAKE, 0);
  delay(3000);
}

void DRV8703_Control::forward_with_speed(uint8_t motor_speed){
  motorWrite(MOTOR_FWD, motor_speed); 
}

void DRV8703_Control::reverse_with_speed(uint8_t motor_speed){
  motorWrite(MOTOR_REV, motor_speed); 
}
void DRV8703_Control::brake(){
  motorWrite(MOTOR_BRAKE, 0);
  Serial.println("braking");
  // int down_steps = 25;
  // for(int i = 0; i < down_steps; ++i){
  //  motorWrite(MOTOR_FWD, map(i, 0, down_steps, speed, 0));
  //  delay(3000/down_steps);
  // }
}

void DRV8703_Control::coast(){
  motorWrite(MOTOR_COAST, 0);
  Serial.println("coasting");
}
