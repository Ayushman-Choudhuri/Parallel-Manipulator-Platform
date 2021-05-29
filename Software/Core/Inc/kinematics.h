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

const float32_t EndEffectorParameters[6][3] = 			{{-73.7, 19.46, 0},
														 {-53.7 ,54.1 , 0},
													 	 {53.7  ,54.1 ,0},
													 	 {73.7, 19.46, 0},
													 	 {20 ,-73.55 ,0},
													 	 {-20, -73.55 , 0}};	/*Coordinates (in mm) of the end effector pivot point coordinates with respect to the end effector frame of reference.*/


const float32_t BaseParameters[6][3] = 					 {{-81.63, 0.36, 0},
		 	 	 	 	 	 	 	 	 	 	 	 	 {-41.13 , 70.51, 0},
														 { 41.13, 70.51 ,0},
														 { 81.63, 0.36, 0},
														 { 40.5 ,-70.87 ,0},
														 {-81.63, -70.87, 0}};	/*Coordinates (in mm) of the base pivot point coordinates with respect to the base frame of reference. */

const float32_t MotorPlaneAngle[6] = 					 {0,0,0,0,0,0};



#define MOTOR_COUPLER_LENGTH							(float32_t)33.81		/*Length of the motor coupler joining the motor shaft and the SS link*/
#define SS_LINK_LENGTH									(float32_t)146			/*Length of the link joining the motor coupler and the end effector */
#define HOME_POSITION_Z_OFFSET							(float32_t)130.64

#define TOTAL_LINKS										(uint8_t)6

/*.................................................................GLOBAL VARIABLES...................................................................................*/

float32_t MotorAngles[6] = {0,0,0,0,0,0};										/*Variable stores the motor angles of all the 6 motors in order from 1 to 6*/

struct Pose																		/*Structure Storing the Pose of the End Effector*/
{
	float32_t Yaw;
	float32_t Pitch;
	float32_t Roll;
	float32_t Heave;
	float32_t Sway;
	float32_t Surge;
};


struct Pose PoseSetpoint = {0,0,0,0,0,0};										/*Instance of the Pose structure used to store the Pose Setpoint*/

//float32_t PoseParametersSetpoint[6] = {0,0,0,0,0,0};							/*Variable stores the pose parameters - Yaw, Pitch, Roll, Heave , Sway , Surge*/

float32_t RotationMatrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};						/*Variable stores the rotation matrix to express end effector coordinates with respect to base frame*/
uint32_t  RotationMatrixSize[2] = {3,3};

float32_t TranslationVector[3][1] = {{0},{0},{0}};										/*Variable Stores the Translation Vector between the base frame and the end effector frame*/
uint32_t  TranslationVectorSize[2] = {3,1};

float32_t EffectiveLinkLengthMatrix[6] = {0,0,0,0,0,0};								/*Variable stores the effective link lengths of the RSS link structures*/
uint32_t  EffectiveLinkLengthMatrixLength[2] = {1,3};

/*.................................................................FUNCTION PROTOTYPES...................................................................................*/

#endif /*KINEMATICS_H_ */
