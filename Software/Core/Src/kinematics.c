/*
 * Filename			 : kinematics.c
 * Version No		 : 1.0
 * Version Date		 : 20-01-2021
 * Description		 : This source file contains all the static and external functions needed to solve the inverse kinematics of a 6DOF RSS Parallel Manipulator
 * External Functions:
 * Internal Functions:
 * Notes			 :


 * Revision History
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 *
*/

#include "kinematics.h"
#include "steppermotorcontrol.h"
/*.........................................Global Variable Definitions.......................................*/
float32_t EndEffectorCoordinates[6][3] = 				{{ 73.7, 19.46, 0},
														 { 53.7 ,54.1 , 0},
													 	 { -53.7  ,54.1 ,0},
													 	 {-73.7, 19.46, 0},
													 	 {-20 ,-73.55 ,0},
													 	 { 20, -73.55 , 0}};	/*Coordinates (in mm) of the end effector pivot point coordinates with respect to the end effector frame of reference.*/

uint32_t EndEffectorCoordinatesSize[2] = {6,3};

float32_t BaseCoordinates[6][3] = 					 {{ 81.63, 0.36, 0},
		 	 	 	 	 	 	 	 	 	 	 	  { 41.13 , 70.51, 0},
													  {-41.13, 70.51 ,0},
													  {-81.63, 0.36, 0},
													  { -41.13 ,-70.51 ,0},
													  {41.13, -70.5, 0}};	/*Coordinates (in mm) of the base pivot point coordinates with respect to the base frame of reference. */

uint32_t BaseCoordinatesSize[2] = {6,3};

const float32_t MotorPlaneAngle[6] = 					 {-pi/3 , 2*pi/3 , - 2*pi/3 , pi/3 , -pi , 0 };




float32_t MotorAngles[6] = {0,0,0,0,0,0};										/*Variable stores the motor angles of all the 6 motors in order from 1 to 6*/


float32_t PoseSetpoint[6] = {0,0,0,0,0,0};										/*Instance of the Pose structure used to store the Pose Setpoint*/

float32_t RotationMatrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};						/*Variable stores the rotation matrix to express end effector coordinates with respect to base frame*/
uint32_t  RotationMatrixSize[2] = {3,3};

float32_t TranslationVector[3][1] = {{0},{0},{0}};								/*Variable Stores the Translation Vector between the base frame and the end effector frame*/
uint32_t  TranslationVectorSize[2] = {3,1};

float32_t EffectiveLinkLengthMatrix[6] = {0,0,0,0,0,0};							/*Variable stores the effective link lengths of the RSS link structures*/
uint32_t  EffectiveLinkLengthMatrixLength = 6;

float32_t EndEffectorCordTransform[3][6] = {{0,0,0,0,0,0},
											{0,0,0,0,0,0},
											{0,0,0,0,0,0}};


//uint32_t  EndEffectorCordTransformSize = {3,6};

/*........................................Function Definitions...............................................*/

/*
 * Function Name	 			: RotationMatrixUpdate
 * Function Description 		: Calculates the Rotation matrix to transform coordinates from end effector frame to base frame
 * 								  The function takes inputs from the global structure PoseSetpoint which stores the current pose setpoint for the end effector
 * Return Type					: None
 * Return Type Description 		: None
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: PoseSetpoint.Yaw, PoseSetpoint.Pitch, PoseSetpoint.Roll
 * Global Variable(s) Modified	: RotationMatrix
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			: All the angle setpoints need to be in degrees and shall be converted into radians in the function before being used in the rotation matrix

*/

static void RotationMatrixUpdate()
{
	/*Declare Local Variables*/
	float32_t Y = 0.0174*PoseSetpoint[0]; /*Convert Yaw Setpoint from degrees to radians*/
	float32_t P = 0.0174*PoseSetpoint[1];/*Convert Pitch Setpoint from degrees to radians*/
	float32_t R = 0.0174*PoseSetpoint[2];/*Convert Roll Setpoint from degrees to radians*/

	RotationMatrix[0][0] = cos(Y)*cos(P);
	RotationMatrix[0][1] = -(sin(Y)*cos(R)) + (cos(Y)*sin(P)*sin(R));
	RotationMatrix[0][2] = (sin(Y)*sin(R)) + (cos(Y)*sin(P)*cos(R));
	RotationMatrix[1][0] = sin(Y)*cos(P);
	RotationMatrix[1][1] = (cos(Y)*cos(R)) + (sin(Y)*sin(P)*sin(R));
	RotationMatrix[1][2] = -(cos(Y)*sin(R)) + (sin(Y)*sin(P)*cos(R));
	RotationMatrix[2][0] = -sin(P);
	RotationMatrix[2][1] = cos(P)*sin(R);
	RotationMatrix[2][2] = cos(P)*cos(R);
}

/*
 * Function Name	 			: TranslationVectorUpdate
 * Function Description 		: Calculates the position vector of the end effector frame origin with respect to the base frame
 * Return Type					: None
 * Return Type Description 		: None
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: PoseSetpoint.delx, PoseSetpoint.dely, PoseSetpoint.delz
 * Global Variable(s) Modified	: TranslationVector
 * Library Function(s) Called	: None
 * Called by					: all the units are in mm
 *  Notes			 			:
*/

static void TranslationVectorUpdate()
{
	TranslationVector[0][0] =  PoseSetpoint[3];
	TranslationVector[1][0] =  PoseSetpoint[4];
	TranslationVector[2][0] =  PoseSetpoint[5] + HOME_POSITION_Z_OFFSET;
}

/*
 * Function Name	 			: EffectiveLinkLengthCalculationVectorized()
 * Function Description 		: Calculation of effective link length between Bi and Ei using a vectorized approach
 * Return Type					: void
 * Return Type Description 		: None
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: EndEffectorCoordinates,BaseCoordinates,RotationMatrix,RotationMatrixSize,TranslationVector,TranslationVectorSize
 * Global Variable(s) Modified	: EndEffectorCoordinates,BaseCoordinates,RotationMatrix,TranslationVector
 * Library Function(s) Called	: MatrixMultiply,MatrixSubtract,MatrixAdd,sqrt
 * Called by					:
 *  Notes			 			:
*/

static void EffectiveLinkLengthCalculationVectorized()
{
	/*Declare Local Variables*/
	float32_t ee_coordinates_transposed [3][6] = {{0,0,0,0,0,0},
												  {0,0,0,0,0,0},
												  {0,0,0,0,0,0}};


	float32_t base_coordinates_transposed [3][6] = {{0,0,0,0,0,0},
													{0,0,0,0,0,0},
													{0,0,0,0,0,0}};


	float32_t effective_link_vectors[3][6] = {{0,0,0,0,0,0},
											  {0,0,0,0,0,0},
											  {0,0,0,0,0,0}};

	float32_t translation_vector_broadcast[3][6] = {{0,0,0,0,0,0},
													{0,0,0,0,0,0},
													{0,0,0,0,0,0}};

	uint32_t link_length_calc_vector_size[2] = {3,6};

	float32_t temp_matrix_1[3][6] = {{0,0,0,0,0,0},
									 {0,0,0,0,0,0},
									 {0,0,0,0,0,0}};


    /*Transpose End Effector coordinate matrix and Base Frame Matrix*/

	MatrixTranspose(EndEffectorCoordinatesSize, EndEffectorCoordinates,ee_coordinates_transposed);
	MatrixTranspose(BaseCoordinatesSize, BaseCoordinates,base_coordinates_transposed);

	/*Build translation_vector_broadcast*/
	for (uint8_t col_index = 0; col_index<link_length_calc_vector_size[1]; col_index ++)
	{
		for(uint8_t row_index = 0; row_index< link_length_calc_vector_size[0]; row_index ++)
		{
			translation_vector_broadcast[row_index][col_index] = TranslationVector[row_index][0];
		}
	}

	/*Calculation of effective link vectors*/
	MatrixMultiply(RotationMatrixSize, link_length_calc_vector_size ,RotationMatrix, ee_coordinates_transposed, temp_matrix_1);
	MatrixAdd(link_length_calc_vector_size,link_length_calc_vector_size,translation_vector_broadcast,temp_matrix_1,EndEffectorCordTransform);
	MatrixSubtract(link_length_calc_vector_size,link_length_calc_vector_size,EndEffectorCordTransform,base_coordinates_transposed,effective_link_vectors);


    /*Calculate value of effective links*/

    for (uint8_t link_index = 0; link_index < EffectiveLinkLengthMatrixLength ; link_index ++)
    {
    	uint32_t comp_sum = 0;

    	for (uint8_t comp_index = 0; comp_index <3 ; comp_index ++)
    	{
    		comp_sum +=  pow(effective_link_vectors[comp_index][link_index],2);
    	}

    	EffectiveLinkLengthMatrix[link_index] = sqrt(comp_sum);
    }
}


/*
 * Function Name	 			: MotorAngleUpdate()
 * Function Description 		: Calculates the motor angle for each motor in the parallel manipulator
 * Return Type					: void
 * Return Type Description 		: None
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
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void MotorAngleUpdate()
{

 uint8_t motor_index = 0;

 float32_t temp = 0;
 float32_t temp_L = 0;
 float32_t temp_M = 0;
 float32_t temp_N = 0;

 float32_t x_e = 0;
 float32_t x_b = 0;
 float32_t y_e = 0;
 float32_t y_b = 0;
 float32_t z_e = 0;
 float32_t z_b = 0;
 float32_t motor_plane_angle = 0;

 for (motor_index = 1; motor_index <=6 ; motor_index++)
 {
	 x_e = EndEffectorCordTransform[0][motor_index -1];
	 y_e = EndEffectorCordTransform[1][motor_index -1];
	 z_e = EndEffectorCordTransform[2][motor_index -1];


	 x_b = BaseCoordinates[motor_index -1][0];
	 y_b = BaseCoordinates[motor_index -1][1];
	 z_b = BaseCoordinates[motor_index -1][2];

	 motor_plane_angle = MotorPlaneAngle[motor_index - 1];

	 temp_L = pow(EffectiveLinkLengthMatrix[motor_index -1],2) - ( pow(SS_LINK_LENGTH,2) - pow(MOTOR_COUPLER_LENGTH,2));

	 temp_M = 2*MOTOR_COUPLER_LENGTH*(z_e - z_b);

	 temp_N = 2*MOTOR_COUPLER_LENGTH*(((cos(motor_plane_angle))*(x_e - x_b)) + (sin(motor_plane_angle)*(y_e - y_b)));

	 temp = temp_L/sqrt(pow(temp_M,2) + pow(temp_N,2));

	 /*for Odd Legs*/
	 if (motor_index%2 != 0)
	 {
		 MotorTargetAngle[motor_index - 1] = -1 *((asin(temp) - atan(temp_N/temp_M))/0.0174);
	 }

	 /*For Even Legs*/
	 else if (motor_index%2 == 0)
	 {
	 MotorTargetAngle[motor_index - 1] = (asin(temp) - atan(temp_N/temp_M))/0.0174;
	 }
	 else
	 {
		 ;
	 }

 }

}

/*
 * Function Name	 			: SolveKinematics()
 * Function Description 		:
 * Return Type					: void
 * Return Type Description 		: None
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
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void SolveKinematics(void)
{
	RotationMatrixUpdate();
	TranslationVectorUpdate();
	EffectiveLinkLengthCalculationVectorized();
	MotorAngleUpdate();
}

