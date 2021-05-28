#ifndef MATRIXOPERATIONS_H_
#define MATRIXOPERATIONS_H_

/*............................................................Function Prototype.........................................................................................*/
 void MatrixAdd( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]]);
 void MatrixSubtract( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]]);
 void MatrixMultiply (uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_2_size[1]]);
 void MatrixTranspose(uint32_t matrix_size[2], float32_t matrix[matrix_size[0]][matrix_size[1]] , float32_t result_matrix[matrix_size[1]][matrix_size[0]]);
 void MatrixScalarMultiply(uint32_t matrix_size[2], float32_t matrix[matrix_size[0]][matrix_size[1]] , float32_t result_matrix[matrix_size[0]][matrix_size[1]], float32_t scalar_value);
 void MatrixElementwiseMultiply( uint32_t matrix_1_size[2], uint32_t matrix_2_size[2], float32_t matrix_1[matrix_1_size[0]][matrix_1_size[1]] , float32_t matrix_2[matrix_2_size[0]][matrix_2_size[1]] , float32_t result_matrix[matrix_1_size[0]][matrix_1_size[1]]);

#endif /*MATRIXOPERATIONS_H_ */
