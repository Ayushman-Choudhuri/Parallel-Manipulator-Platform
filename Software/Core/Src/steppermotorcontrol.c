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

float32_t MotorTargetAngle[6] = {+360,0,0,0,0,0};
uint32_t  MotorCurrentAngle[6] = {0,0,0,0,0,0};
uint32_t  MotorTargetStepCount[6] = {0,0,0,0,0,0};
uint32_t  MotorCurrentStepCount[6] = {0,0,0,0,0,0};
uint32_t  MotorDirection[6] = {CLOCKWISE, CLOCKWISE, CLOCKWISE, CLOCKWISE, CLOCKWISE, CLOCKWISE};
uint8_t  MotorState[6] = {HIGH, HIGH,HIGH,HIGH,HIGH,HIGH};

uint8_t	  LimitSwitchState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
uint8_t   LimitSwitchMode[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
uint32_t  LimitSwitchCounter[6] = {0,0,0,0,0,0};


uint8_t test = 0;
uint32_t test2 = 0;
uint8_t test3 = 0;
/*........................................Function Definitions...............................................*/

/*
 * Function Name	 			: LimitSwitchDebounce
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

static void LimitSwitchDebounce(uint32_t limit_switch_index)
{
	switch(LimitSwitchState[limit_switch_index -1])
	{
		case LOW:	LimitSwitchCounter[limit_switch_index - 1] = 0;
					LimitSwitchMode[limit_switch_index - 1] = LOW;
					break;

		case HIGH:	LimitSwitchCounter[limit_switch_index -1] ++;

					if (LimitSwitchCounter[limit_switch_index -1] >= LIMIT_SWITCH_DEBOUNCE_THRESHOLD)
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

void LimitSwitchTriggerScan()
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



