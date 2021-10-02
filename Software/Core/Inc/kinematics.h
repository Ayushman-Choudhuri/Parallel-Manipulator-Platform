/*
 * Filename			 : kinematics.h
 * Version No		 : 1.0
 * Version Date		 : 20-01-2021
 * Description		 :
 * External Functions:
 * Internal Functions:
 * Notes			 :


 * Revision History
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com

*/

#ifndef KINEMATICS_H_
#define KINEMATICS_H_

#include "typedef.h"
#include "math.h"
#include "matrixoperations.h"

/*.................................................................CONFIGURATION PARAMETERS...................................................................................*/

#define pi 		(float32_t)3.1416


/*...........................................External Global Variables.........................................*/

extern float32_t MotorAngles[6];
extern float32_t PoseSetpoint[6];

#define MOTOR_COUPLER_LENGTH							(float32_t)33.81		/*Length of the motor coupler joining the motor shaft and the SS link*/
#define SS_LINK_LENGTH									(float32_t)146			/*Length of the link joining the motor coupler and the end effector */
#define HOME_POSITION_Z_OFFSET							(float32_t)130.64

#define TOTAL_LINKS										(uint8_t)6




/*.................................................................FUNCTION PROTOTYPES...................................................................................*/
void SolveKinematics(void);


#endif /*KINEMATICS_H_ */
