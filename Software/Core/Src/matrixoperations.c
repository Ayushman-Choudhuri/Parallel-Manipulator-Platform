/*
 * Filename			 : matrixoperations.c
 * Version No		 : 1.0
 * Version Date		 : 20-01-2021
 * Description		 : This source file contains all necessary matrix operations needed to operate the parallel manipulator
 * External Functions: MatrixAdd
 * 					   MatrixSubtract
 *
 * Internal Functions:
 * Notes			 :


 * Revision History
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com	  Basic Functions needed to obtain data from accelerometer, magnetometer and gyroscope
*/



#include "typedef.h"

/*
 * Function Name	 			: MatrixAdd
 * Function Description 		: Adds two Matrices
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					:
 * Parameter Description		:
 * Global Variables Accessed	:
 * Global Variable(s) Modified	:
 * Library Function(s) Called	:
 *
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

 void MatrixAdd( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]])
{
	uint32_t mat_1_row = matrix_1_size[0];
	uint32_t mat_1_col = matrix_1_size[1];
	uint32_t mat_2_row = matrix_2_size[0];
	uint32_t mat_2_col = matrix_2_size[1];


	if ((mat_1_row == mat_2_row)&&(mat_1_col == mat_2_col))
	{
		for (uint32_t row_index = 0; row_index <=mat_1_row ; row_index ++ )
		{
			for (uint32_t col_index = 0; col_index <=mat_1_col ; col_index++)
			{
				result_matrix[row_index][col_index] = matrix_1[row_index][col_index]+ matrix_2[row_index][col_index];
			}
		}
	}

	else
	{
		;
	}

}
 /*
  * Function Name	 			: MatrixSubtract
  * Function Description 		: Subtracts two Matrices
  * Return Type					: void
  * Return Type Description 	: None
  *
  * Parameter(s)			    :
  * Parameter Description		:
  * Global Variables Accessed	:
  * Global Variable(s) Modified	:
  * Library Function(s) Called	:
  *
  * Called by					:
  *  Notes			 			:

  * Change Log
  * Version No.		 Date			Author 					Email				Description
  * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 */

 void MatrixSubtract( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]])
{
	uint32_t mat_1_row = matrix_1_size[0];
	uint32_t mat_1_col = matrix_1_size[1];
	uint32_t mat_2_row = matrix_2_size[0];
	uint32_t mat_2_col = matrix_2_size[1];


	if ((mat_1_row == mat_2_row)&&(mat_1_col == mat_2_col))
	{
		for (uint32_t row_index = 0; row_index <mat_1_row ; row_index ++ )
		{
			for (uint32_t col_index = 0; col_index <mat_1_col ; col_index++)
			{
				result_matrix[row_index][col_index] = matrix_1[row_index][col_index]- matrix_2[row_index][col_index];
			}
		}
	}

}

 /*
  * Function Name	 			: MatrixMultiply
  * Function Description 		: Multiplies two Matrices
  * Return Type					: void
  * Return Type Description 	: None
  *
  * Parameter(s)			    :
  * Parameter Description		:
  * Global Variables Accessed	:
  * Global Variable(s) Modified	:
  * Library Function(s) Called	:
  *
  * Called by					:
  *  Notes			 			:

  * Change Log
  * Version No.		 Date			Author 					Email				Description
  * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 */
 void MatrixMultiply (uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_2_size[1]])
{
	uint32_t mat_1_row = matrix_1_size[0];
	uint32_t mat_1_col = matrix_1_size[1];

	uint32_t mat_2_row = matrix_2_size[0];
	uint32_t mat_2_col = matrix_2_size[1];


	if (mat_2_row == mat_1_col)
	{
		for (uint32_t row_index = 0; row_index <mat_1_row ; row_index ++ )
			{
				for (uint32_t col_index = 0; col_index <mat_2_col ; col_index++)
					{

						float32_t temp_sum = 0;

						for (uint32_t temp_index = 0; temp_index <mat_1_col ; temp_index ++)
						{
							float32_t temp_val_1 = matrix_1[row_index][temp_index];
							float32_t temp_val_2 = matrix_2[temp_index][col_index];
							temp_sum = temp_sum + (temp_val_1*temp_val_2);
						}

						result_matrix[row_index][col_index] = temp_sum ;

					}
			}
	}


	else
	{
		;
	}

}


 /*
  * Function Name	 			: MatrixTranspose
  * Function Description 		: Performs Matrix Transpose operation on the input matrix
  * Return Type					: void
  * Return Type Description 	: None
  *
  * Parameter(s)			    :
  * Parameter Description		:
  * Global Variables Accessed	:
  * Global Variable(s) Modified	:
  * Library Function(s) Called	:
  *
  * Called by					:
  *  Notes			 			:

  * Change Log
  * Version No.		 Date			Author 					Email				Description
  * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 */

 void MatrixTranspose(uint32_t matrix_size[2], float32_t matrix[matrix_size[0]][matrix_size[1]] , float32_t result_matrix[matrix_size[1]][matrix_size[0]])
{
	uint32_t mat_row = matrix_size[0];
	uint32_t mat_col = matrix_size[1];


	for (uint32_t row_index = 0; row_index <mat_row ; row_index ++ )
		{
			for (uint32_t col_index = 0; col_index <mat_col ; col_index++)
				{
					result_matrix[col_index][row_index] = matrix[row_index][col_index];
				}
		}

}

 /*
  * Function Name	 			: MatrixScalar Multiply
  * Function Description 		: Performs scalar multiplication between the input matrix and scalar
  * Return Type					: void
  * Return Type Description 	: None
  *
  * Parameter(s)			    :
  * Parameter Description		:
  * Global Variables Accessed	:
  * Global Variable(s) Modified	:
  * Library Function(s) Called	:
  *
  * Called by					:
  *  Notes			 			:

  * Change Log
  * Version No.		 Date			Author 					Email				Description
  * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 */
 void MatrixScalarMultiply(uint32_t matrix_size[2], float32_t matrix[matrix_size[0]][matrix_size[1]] , float32_t result_matrix[matrix_size[0]][matrix_size[1]], float32_t scalar_value)
{

	uint32_t mat_row = matrix_size[0];
	uint32_t mat_col = matrix_size[1];

  for (uint32_t row_index = 0; row_index < mat_row ; row_index ++)
  {
	  for (uint32_t col_index = 0 ; col_index < mat_col ; col_index ++)
	  {
		  result_matrix[row_index][col_index] = scalar_value*matrix[row_index][col_index];
	  }
  }
}

 /*
  * Function Name	 			: MatrixElementwiseMultiply
  * Function Description 		: Performs elementwise multiplication between two input matrices
  * Return Type					: void
  * Return Type Description 	: None
  *
  * Parameter(s)			    :
  * Parameter Description		:
  * Global Variables Accessed	:
  * Global Variable(s) Modified	:
  * Library Function(s) Called	:
  *
  * Called by					:
  *  Notes			 			:

  * Change Log
  * Version No.		 Date			Author 					Email				Description
  * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
 */
 void MatrixElementwiseMultiply( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]])
{
	uint32_t mat_1_row = matrix_1_size[0];
	uint32_t mat_1_col = matrix_1_size[1];
	uint32_t mat_2_row = matrix_2_size[0];
	uint32_t mat_2_col = matrix_2_size[1];


	if ((mat_1_row == mat_2_row)&&(mat_1_col == mat_2_col))
	{
		for (uint32_t row_index = 0; row_index <=mat_1_row ; row_index ++ )
		{
			for (uint32_t col_index = 0; col_index <=mat_1_col ; col_index++)
			{
				result_matrix[row_index][col_index] = (matrix_1[row_index][col_index])*(matrix_2[row_index][col_index]);
			}
		}
	}

	else
	{
		;
	}

}

