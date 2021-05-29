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

/*
 * Function Name	 			: RotationMatrixUpdate
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
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void RotationMatrixUpdate()
{

	RotationMatrix[0][0] = cos(PoseSetpoint.Yaw)*cos(PoseSetpoint.Pitch);
	RotationMatrix[0][1] = -(sin(PoseSetpoint.Yaw)*cos(PoseSetpoint.Roll)) + (cos(PoseSetpoint.Yaw)*sin(PoseSetpoint.Pitch)*sin(PoseSetpoint.Roll));
	RotationMatrix[0][2] = (sin(PoseSetpoint.Yaw)*sin(PoseSetpoint.Roll)) + (cos(PoseSetpoint.Yaw)*sin(PoseSetpoint.Pitch)*cos(PoseSetpoint.Roll));
	RotationMatrix[1][0] = sin(PoseSetpoint.Yaw)*cos(PoseSetpoint.Pitch);
	RotationMatrix[1][1] = (cos(PoseSetpoint.Yaw)*cos(PoseSetpoint.Roll)) + (sin(PoseSetpoint.Yaw)*sin(PoseSetpoint.Pitch)*sin(PoseSetpoint.Roll));
	RotationMatrix[1][2] = -(cos(PoseSetpoint.Yaw)*sin(PoseSetpoint.Roll)) + (sin(PoseSetpoint.Yaw)*sin(PoseSetpoint.Pitch)*cos(PoseSetpoint.Roll));
	RotationMatrix[2][0] = -sin(PoseSetpoint.Pitch);
	RotationMatrix[2][1] = cos(PoseSetpoint.Pitch)*sin(PoseSetpoint.Roll);
	RotationMatrix[2][2] = cos(PoseSetpoint.Pitch)*cos(PoseSetpoint.Roll);

}

/*
 * Function Name	 			: TranslationVectorUpdate
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
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void TranslationMatrixUpdate()
{
	TranslationVector[0][0] +=  PoseSetpoint.Surge;
	TranslationVector[1][0] +=  PoseSetpoint.Sway;
	TranslationVector[2][0] +=  PoseSetpoint.Heave;
}


/*
 * Function Name	 			: EffectiveLinkLengthCalculation()
 * Function Description 		: Calculation of effective link length between Bi and Ei
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: EndEffectorParameters,BaseParameters,RotationMatrix,RotationMatrixSize,TranslationVector,TranslationVectorSize
 * Global Variable(s) Modified	: EndEffectorParameters,BaseParameters,RotationMatrix,TranslationVector
 * Library Function(s) Called	: MatrixMultiply,MatrixSubtract,MatrixAdd,sqrt
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void EffectiveLinkLengthCalculation()
{
	/*Declare Local Variables*/

	uint8_t link_index = 0;
	float32_t temp_1 = 0;
	float32_t temp_2 = 0;
	float32_t temp_3 = 0;

	float32_t effective_link_vector[3][1] = {{0},{0},{0}};

	float32_t end_effector_junction_coordinate[3][1] =  {{0},{0},{0}};
	uint32_t  end_effector_junction_coordinate_size[2] = {3,1};

	float32_t base_motor_axis_junction_coordinate[3][1] = {{0},{0},{0}};
	uint32_t  base_motor_axis_junction_coordinate_size[2] = {3,1};

	float32_t temp_matrix_1[3][1] = {{0},{0},{0}};
	uint32_t  temp_matrix_1_size[2] = {3,1};

	float32_t temp_matrix_2[3][1] = {{0},{0},{0}};
	uint32_t  temp_matrix_2_size[2] = {3,1};

	float32_t temp_matrix_3[3][1] = {{0},{0},{0}};
	/*uint32_t  temp_matrix_3_size[2] = {3,1};*/


	/*Update Effective Link Length Matrix*/

	for(link_index = 1 ; link_index <= TOTAL_LINKS ; link_index ++ )
	{
		/*Update Respective End Effector Junction Coordinate*/

		end_effector_junction_coordinate[3][1] = EndEffectorParameters[link_index-1][3];
		base_motor_axis_junction_coordinate[3][1] = BaseParameters[link_index-1][3];

		/*Matrix Operations*/

		MatrixMultiply(RotationMatrixSize,end_effector_junction_coordinate_size, RotationMatrix,end_effector_junction_coordinate, temp_matrix_1 );
		MatrixSubtract(temp_matrix_1_size, base_motor_axis_junction_coordinate_size,temp_matrix_1,base_motor_axis_junction_coordinate,temp_matrix_2);
		MatrixAdd(TranslationVectorSize,temp_matrix_2_size,TranslationVector,temp_matrix_2,temp_matrix_3);

		/*Update effective link vector*/

		effective_link_vector[3][1] = temp_matrix_3[3][1];

		/*Calculate effective link length*/

		temp_1 = effective_link_vector[0][1]*effective_link_vector[0][1];
		temp_2 = effective_link_vector[1][1]*effective_link_vector[1][1];
		temp_3 = effective_link_vector[2][1]*effective_link_vector[2][1];

		EffectiveLinkLengthMatrix[link_index - 1] = sqrt(temp_1 + temp_2 + temp_3);
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

 float32_t temp_1 = 0;
 float32_t temp_2 = 0;
 float32_t temp_3 = 0;
 float32_t temp_4 = 0;
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
	 temp_1 = EffectiveLinkLengthMatrix[motor_index -1] * EffectiveLinkLengthMatrix[motor_index -1];
	 temp_2 = MOTOR_COUPLER_LENGTH*MOTOR_COUPLER_LENGTH;
	 temp_3 = SS_LINK_LENGTH*SS_LINK_LENGTH;

	 x_e = EndEffectorParameters[motor_index -1][0];
	 y_e = EndEffectorParameters[motor_index -1][1];
	 z_e = EndEffectorParameters[motor_index -1][2];

	 x_b = BaseParameters[motor_index -1][0];
	 y_b = BaseParameters[motor_index -1][1];
	 z_b = BaseParameters[motor_index -1][2];

	 motor_plane_angle = MotorPlaneAngle[motor_index - 1];

	 temp_L = temp_1 - (temp_3 - temp_2);

	 temp_M = 2*MOTOR_COUPLER_LENGTH*(z_e - z_b);

	 temp_N = 2*MOTOR_COUPLER_LENGTH*(((cos(motor_plane_angle))*(x_e - x_b)) + (sin(motor_plane_angle)*(y_e - y_b)));

	 temp_4 = temp_L/sqrt((temp_M*temp_M) + (temp_N*temp_N));

	 MotorAngles[motor_index - 1] = asin(temp_4) - atan(temp_N/temp_M);

 }

}

