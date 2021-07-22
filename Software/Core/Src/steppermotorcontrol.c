/*
 * Filename			 : steppermotor.c
 * Version No		 : 1.0
 * Version Date		 : 20-03-2021
 * Description		 :
 * External Functions:
 * Internal Functions:
 * Notes			 :


 * Revision History
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 *
*/
#include "steppermotorcontrol.h"

/*.........................................Global Variable Definitions.......................................*/

float32_t MotorTargetAngle[6] = {0,0,0,0,0,0};
float32_t MotorTargetAnglePrevious[6] = {0,0,0,0,0,0};
uint8_t   MotorTagetAngleSet[6] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
uint32_t  MotorCurrentAngle[6] = {0,0,0,0,0,0};
uint32_t  MotorTargetStepCount[6] = {0,0,0,0,0,0};
uint32_t  MotorCurrentStepCount[6] = {0,0,0,0,0,0};
int8_t    MotorDirection[6] = {ANGLE_UP,ANGLE_UP,ANGLE_UP,ANGLE_UP,ANGLE_UP,ANGLE_UP};
int8_t    MotorDirectionBias[6] = {1,1,1,1,1,1};
uint8_t   MotorState[6] = {HIGH, HIGH,HIGH,HIGH,HIGH,HIGH};


uint8_t	  LimitSwitchState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
uint8_t   LimitSwitchMode[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
uint32_t  LimitSwitchCounter[6] = {0,0,0,0,0,0};


uint8_t test = 0;
uint32_t test2 = 0;
uint8_t test3 = 0;
/*........................................Function Definitions...............................................*/

/*
 * Function Name	 			: LimitSwitchDebounce
 * Function Description 		: Function performs debouncing operation on the incoming limit switch signal stored in LimitSwitchState[].
 * 								  If a limit switch signal passes the debounce test, the LimitSwitchMode[] for the limit switch is set to HIGH.
 *
 * Return Type					: void
 * Return Type Description 		: N/A
 *
 * Parameter(s)					: limit_switch_index
 * Parameter Description		: limit_switch_index : The index of the limit switch for a specific motor. The values vary from 1 for the limit switch of Motor 1
 * 													   to 6 for the limit switch of the 6th motor.
 * Global Variables Accessed	: LimitSwitchCounter[], LimitSwitchMode
 * Global Variable(s) Modified	: LimitSwitchCounter[],
 * Library Function(s) Called	: N/A
 * Called by					: LimitSwitchTriggerScan()
 *  Notes			 			: Tune the LIMIT_SWITCH_DEBOUNCE_THRESHOLD configuration parameter to increase or decrease the debounce threshold.

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com		base file
*/

static void LimitSwitchDebounce(uint32_t limit_switch_index)
{
	switch(LimitSwitchState[limit_switch_index -1])
	{
		case LOW:	LimitSwitchCounter[limit_switch_index - 1] = 0;
					LimitSwitchMode[limit_switch_index - 1] = LOW;
					break;

		case HIGH:	LimitSwitchCounter[limit_switch_index -1] ++;

					if (LIMIT_SWITCH_DEBOUNCE_THRESHOLD <= LimitSwitchCounter[limit_switch_index -1])
					{
						LimitSwitchMode[limit_switch_index -1] = HIGH;
					}

					else
					{
						LimitSwitchMode[limit_switch_index -1] = LOW;

					}

					break;

		default: 	break;
	}
}

/*
 * Function Name	 			: LimitSwitchStateDetect
 * Function Description 		: This function determines the state of the limit switch
 * 								  HIGH : Switch is triggered (Closed position)
 * 								  LOW : Switch is not triggered (Open Position)
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: limit_switch_index
 * Parameter Description		: limit_switch_index : The index of the limit switch for a specific motor. The values vary from 1 for the limit switch of Motor 1
 * 													   to 6 for the limit switch of the 6th motor.
 * Global Variables Accessed	: LimitSwitchState[]
 * Global Variable(s) Modified	: LimitSwitchState[]
 * Library Function(s) Called	:
 * Called by					: HAL_GPIO_EXTI_Callback()
 *  Notes			 			: To use this function for the limit switch, please set the interrupt trigger to both rising and falling edges

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void LimitSwitchStateDetect(uint32_t limit_switch_index)
{
	switch (LimitSwitchState[limit_switch_index -1])
								  {
						  	  	  case LOW:  LimitSwitchState[limit_switch_index -1] = HIGH;
						  	  	  	  	  	 break;

						  	  	  case HIGH: LimitSwitchState[limit_switch_index -1] = LOW;
						  	  	  	  	  	 break;

						  	  	  default: break;
								  }
}

/*
 * Function Name	 			: LimitSwitchTriggerScan
 * Function Description 		: Function scans all the limit switches and updates the state variables to detect the switch mode.
 * Return Type					: void
 * Return Type Description 		: N/A
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	:
 * Called by					: SysTick_Handler()
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void LimitSwitchTriggerScan(void)
{
	for(uint8_t switch_index = 1; switch_index <=6 ; switch_index ++)
	{
		LimitSwitchDebounce(switch_index);
	}
}

/*
 * Function Name	 			: MotorStopTriggerDetect
 * Function Description 		:
 * Return Type					:
 * Return Type Description 		:
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	:
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void MotorStopTriggerDetect(uint8_t motor_index)
{
	switch(LimitSwitchState[motor_index -1])
	{
		case HIGH: MotorState[motor_index -1] = LOW;
				   MotorCurrentAngle[motor_index - 1] = 0;
				   break;
		case LOW:  break;

		default:   break;
	}

}

/*
 * Function Name	 			: MotorStopTriggerScan()
 * Function Description 		:
 * Return Type					:
 * Return Type Description 		:
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	:
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void MotorStopTriggerScan()
{
	for (uint8_t motor_index = 1; motor_index <=6 ; motor_index ++)
	{
		MotorStopTriggerDetect(motor_index);
	}
}

/*
 * Function Name	 			: MotorRotateAbsolute()
 * Function Description 		:
 * Return Type					:
 * Return Type Description 		:
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	:
 * Called by					:
 *  Notes			 			: This function is to be excecuted only in the Systick handler or any loop which excecutes every 1ms

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-03-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void MotorRotateAbsolute(uint8_t motor_index)
{
	float32_t delta_motor_angle = 0;

	switch(MotorState[motor_index -1])
	{
		case HIGH: switch(MotorTagetAngleSet[motor_index -1])
					{
						case FALSE : /* Set the  target Angle and Calculate the required numbers of steps*/

									MotorTargetAnglePrevious[motor_index -1] = MotorTargetAngle[motor_index -1];
									MotorTargetStepCount[motor_index -1] = (uint32_t)(MotorTargetAngle[motor_index -1]/MOTOR_STEP_ANGLE);
									MotorTagetAngleSet[motor_index -1] = TRUE;
									break;

						case TRUE : /*Check if there has been a change in the target angle */

									if (MotorTargetAngle[motor_index -1] != MotorTargetAnglePrevious[motor_index -1]) /*Condition for target angle change*/
									{
									  MotorTagetAngleSet[motor_index -1] = FALSE;

									  delta_motor_angle = MotorTargetAngle[motor_index -1]  - MotorTargetAnglePrevious[motor_index -1];

									  if (delta_motor_angle > 0)
									  {
										  MotorDirection[motor_index] = MotorDirectionBias[motor_index -1]*ANGLE_UP;
									  }

									  else if (delta_motor_angle < 0)
									  {
										  MotorDirection[motor_index] = MotorDirectionBias[motor_index -1]*ANGLE_DOWN;
									  }

									  else
									  {
										  ;
									  }
									  break;
									}

									else if (MotorTargetAngle[motor_index -1] == MotorTargetAnglePrevious[motor_index -1]) /*Condition for no change in target angle*/
									{
										MotorCurrentStepCount[motor_index -1] ++;
										MotorCurrentAngle[motor_index -1] += MOTOR_STEP_ANGLE;
									}

									else
									{
										;
									}
									break;


						default:    break;
					}

				   break;

		case LOW:  break;

		default :  break;
	}
}


