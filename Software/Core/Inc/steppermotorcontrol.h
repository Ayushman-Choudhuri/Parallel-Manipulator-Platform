#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

#include "typedef.h"

/*.........................................Configuration Parameters...................................*/

#define MOTOR_STEP_ANGLE						(float32_t)0.225  /*Motor step angle in degrees 1.8x microstepping ratio = 1.8 x 1/8 = 0.225*/

#define HIGH									(uint8_t)1
#define LOW										(uint8_t)0
#define TRUE									(uint8_t )1
#define FALSE									(uint8_t )0
#define ANGLE_UP							    (int8_t)1
#define ANGLE_DOWN								(int8_t)-1
#define ANGLE_HOLD								(int8_t)0
#define LIMIT_SWITCH_DEBOUNCE_THRESHOLD			(uint32_t)30
#define MOTOR_PWM_TIMER_FREQUENCY				(uint32_t)4	/*Frequency of the motor timer in kHZ*/
#define MOTOR_LOOP_UPDATE_FREQUENCY				(uint32_t)1	/*Frequency at which the motor parameters are getting updated (for systick loop excecution - 1Khz)*/
/*...........................................External Global Variables.........................................*/

extern uint8_t  LimitSwitchState[6];
extern uint32_t LimitSwitchCounter[6];
extern uint8_t  LimitSwitchMode[6];
extern uint8_t  MotorState[6];
extern uint8_t  MotorHighStateSetFlag[6];
extern int8_t   MotorDirection[6];
extern float32_t MotorTargetAngle[6];

//extern uint8_t test;
//extern uint32_t test2;
//extern uint8_t test3;
/*...........................................Function Prototypes.........................................*/
void LimitSwitchTriggerScan();
void LimitSwitchStateDetect(uint32_t limit_switch_index);
void MotorStopTriggerScan();
void MotorActuate();

void MotorActuateTest();

#endif /* STEPPERMOTOR_H_ */
