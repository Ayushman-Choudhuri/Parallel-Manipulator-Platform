/*
 * Filename			 : mpu9250.c
 * Version No		 : 1.0
 * Version Date		 : 20-01-2021
 * Description		 : This source file contains all the static and external functions needed to operate the MPU 9250 9 Axis IMU and gather orientation and pose data.
 * External Functions: MPU9250IsConnected()
 * 					   MPU 9250Init()
 * Internal Functions: MPUI2CWrite
 * 					   MPUI2CRead
 * Notes			 : The following documents have been referred to while developing this library
 * 						1. MPU 9250 Register Map Rev 1.4 by InvenSense
 * 						2. MPU 9250 Product Specification Rev 1.1 by InvenSense


 * Revision History
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com	  Basic Functions needed to obtain data from accelerometer, magnetometer and gyroscope
*/

#include "mpu9250.h"

float32_t AccelResolution = 0.0;
float32_t GyroResolution = 0.0;
float32_t MagResolution = 0.0;

float32_t MagBiasFactory[3] = {0,0,0};
uint8_t	  MMode = 0x06; /*Either 8 Hz 0x02) or 100 Hz (0x06) magnetometer data ODR */

float32_t GyroBias[3] = {0,0,0};/*Bias Correction for Gyroscope*/
float32_t AccelBias[3] = {0,0,0};/*Bias Correction for Accelerometer*/

enum AccelScale AScale = AccelScale_2G;
enum GyroScale  GScale = GyroScale_250DPS;
enum MagScale 	MScale = MagScale_16BITS;

/*
 * Function Name	 			: getMRes()
 * Function Description 		:
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/
static void getMRes()
{
	switch(MScale)
	{
	case MagScale_16BITS : MagResolution = 10.0*4912.0/8190.0; /*Scale to return MilliGauss*/
						   break;
	case MagScale_14BITS : MagResolution = 10.0*4912.0/32760.0;/*Scale to return MilliGauss*/
						   break;
	default			     : break;
	}
}


/*
 * Function Name	 			: getGRes()
 * Function Description 		:
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/
static void getGRes()
{
	switch(GScale)
	{
	case GyroScale_250DPS : GyroResolution = 250.0/32768.0;
							break;
	case GyroScale_500DPS : GyroResolution = 500.0/32768.0;
							break;
	case GyroScale_1000DPS :GyroResolution = 1000.0/32768.0;
							break;
	case GyroScale_2000DPS :GyroResolution = 2000.0/32768.0;
							break;
	default		  		   : break;
	}
}

/*
 * Function Name	 			: getARes()
 * Function Description 		:
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

static void getARes()
{

	switch(AScale)
	{
	case AccelScale_2G : AccelResolution = 2.0/32768.0;
						 break;
	case AccelScale_4G : AccelResolution = 4.0/32768.0;
						 break;
	case AccelScale_8G : AccelResolution = 8.0/32768.0;
						 break;
	case AccelScale_16G: AccelResolution = 16.0/32768.0;
						 break;
	default			   : break;
	}
}

/*
 * Function Name	 			: MPU9250IsConnected
 * Function Description 		: Checks for the connection status with MPU 9250 on the I2C Bus
 * Return Type					: bool
 * Return Type Description 		: 1 - Connected
 * 								  0 - Not Connected
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: HAL_I2C_IsDeviceReady	- stm32f1xx_hal_i2c.h
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com		Basic function using HAL_I2C_IsDeviceReady function
*/

bool  MPU9250IsConnected()
{
	if (HAL_I2C_IsDeviceReady(&hi2c1,MPU9250_ADDRESS,MPU9250_I2C_COMM_CHECK_TRY, MPU9250_I2C_COMM_CHECK_TIMEOUT) == HAL_OK)
		{
			return true;
		}
	else
		{
			return false;
		}

}


/*
 * Function Name	 			: MPUI2CWrite
 * Function Description 		: The function writes data to a specific register address in the MPU9250
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: *data , write_address, num_bytes
 * Parameter Description		: *data - Pointer to the data to be written - uint8_t
 * 								  write_Address - 8 bit register address -    uint8_t
 * 								  num_bytes - number of bytes to be written - uint16_t
 *
 * Global Variables Accessed	:  MPUReturnStatus
 * Global Variable(s) Modified	:  MPUReturnStatus
 * Library Function(s) Called	:  HAL_I2C_Mem_Write	- stm32f1xx_hal_i2c.h
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com		Basic routine using HAL_I2C_Mem_Write function
*/

static void I2CWrite(uint8_t *data,uint8_t device_address ,uint8_t write_address , uint16_t num_bytes)
{
	MPUReturnStatus = HAL_I2C_Mem_Write(&hi2c1, device_address, write_address, I2C_MEMADD_SIZE_8BIT, data, num_bytes, HAL_MAX_DELAY);

	/*Insert Error Handling Routine*/


}



/*
 * Function Name	 			: MPUI2CRead
 * Function Description 		: Reads the data in a specific register in the MPU9250 Module
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: *data_recieve_buffer , read_address, num_bytes_to_read
 * Parameter Description		: *data_recieve_buffer : pointer to the buffer storing the read data
 * 								   read_address: register address within the MPU 9250 to be read
 * 								   num_bytes_to_read: size of the data (in bytes) to be read
 *
 * Global Variables Accessed	: MPUReturnStatus
 * Global Variable(s) Modified	: MPUReturnStatus
 * Library Function(s) Called	: HAL_I2C_Master_Transmit - stm32f1xx_hal_i2c.h
 * 								  HAL_I2C_Master_Receive  - stm32f1xx_hal_i2c.h
 * Called by					:
 *  Notes			 			:

 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com		Basic routine using HAL_I2C_Master_Transmit
 * 	  																			and HAL_I2C_Master_Receive function
*/

static void I2CRead(uint8_t *data_recieve_buffer,uint8_t device_address ,uint8_t read_address, uint16_t num_bytes_to_read)
{

	uint8_t data_send = read_address;

	/*Transmit the register address(to be read) in the MPU 9250*/
	MPUReturnStatus = HAL_I2C_Master_Transmit(&hi2c1 , device_address, &data_send , 1 , HAL_MAX_DELAY);

	/*Insert Error Handling Routine*/


	/* Recieve data in the register in MPU9250 and store it in data_recieve_buffer*/
	MPUReturnStatus = HAL_I2C_Master_Receive(&hi2c1 , device_address, data_recieve_buffer, num_bytes_to_read , HAL_MAX_DELAY);

}

/*
 * Function Name	 			: WriteRegister
 * Function Description 		: Writes to a specific register in the MPU 9250
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: register_address, data
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

static void WriteMPURegister(uint8_t register_address , uint8_t data)
{
	I2CWrite(&data,MPU9250_ADDRESS,register_address, sizeof(data));
	HAL_Delay(10);
}

/*
 * Function Name	 			: ReadRegister
 * Function Description 		:
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

static void ReadMPURegister(uint8_t register_address , uint8_t* data_buffer, uint8_t data_size)
{
	I2CRead(data_buffer ,MPU9250_ADDRESS	 ,register_address, data_size);
}

/*
 * Function Name	 			: WriteAK8963Register
 * Function Description 		:
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

static void WriteAK8963Register(uint8_t register_address , uint8_t data)
{
	I2CWrite(&data,AK8963_ADDRESS,register_address, sizeof(data));
	HAL_Delay(10);

}

/*
 * Function Name	 			: ReadAK8963Register
 * Function Description 		:
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

static void ReadAK8963Register(uint8_t register_address, uint8_t* data_buffer, uint8_t data_size)
{

	I2CRead(data_buffer ,AK8963_ADDRESS,register_address, data_size);
}


/*
 * Function Name	 			: MPU9250Init
 * Function Description 		: Initializes the MPU9250 and starts communication
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void MPU9250Init()
{
	WriteMPURegister(PWR_MGMT_1,0x00);
	HAL_Delay(100);
	WriteMPURegister(PWR_MGMT_1,0x01);
	HAL_Delay(200);
	WriteMPURegister(CONFIG,0x03);
	WriteMPURegister(SMPLRT_DIV,0x04);

	/*Set Gyroscope Scale Configuration*/
	uint8_t gyro_config = 0;
	uint8_t* gyro_config_addr = &gyro_config;
	ReadMPURegister(GYRO_CONFIG,gyro_config_addr,sizeof(gyro_config));
	gyro_config = gyro_config &~0x02;
	gyro_config = gyro_config &~0x18;
	gyro_config = gyro_config|GScale << 3;
	/*gyro_config = gyro_config|0x00;*/
	WriteMPURegister(GYRO_CONFIG,gyro_config);

	/*Set Accelerometer Scale Configuration*/
	uint8_t accel_config = 0;
	uint8_t* accel_config_addr = &accel_config;
	ReadMPURegister(ACCEL_CONFIG,accel_config_addr,sizeof(accel_config));
	/*accel_config = accel_config &~0xE0;*/
	accel_config = accel_config &~0x18;
	accel_config = accel_config | AScale << 3;
	WriteMPURegister(ACCEL_CONFIG,accel_config);

	/*Set accelerometer sample rate configuration*/
	uint8_t accel_config_2 = 0;
	uint8_t* accel_config_2_addr = &accel_config_2;
	ReadMPURegister(ACCEL_CONFIG2,accel_config_2_addr,sizeof(accel_config_2));
	accel_config = accel_config_2 &~0x0F;
	accel_config = accel_config_2 | 0x03;
	WriteMPURegister(ACCEL_CONFIG2,accel_config_2);

	WriteMPURegister(INT_PIN_CFG,0x22);
	WriteMPURegister(INT_ENABLE,0x01);
	HAL_Delay(100);
}

/*
 * Function Name	 			: ResetMPU9250
 * Function Description 		: Resets MPU 9250
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void ResetMPU9250()
{
	WriteMPURegister(PWR_MGMT_1,0x80);
	HAL_Delay(100);
}

/*
 * Function Name	 			: AK8963Init
 * Function Description 		: Initializes the AK8963 module
 * Return Type					: void
 * Return Type Description 		: None
 *
 * Parameter(s)					: None
 * Parameter Description		: None
 * Global Variables Accessed	: None
 * Global Variable(s) Modified	: None
 * Library Function(s) Called	: None
 * Called by					:
 *  Notes			 			:
 * Change Log
 * Version No.		 Date			Author 					Email				Description
 * 	  1.0		  20-01-2021	Ayushman Choudhuri	 ayushc205@gmail.com
*/

void AK8963Init()
{
	uint8_t raw_data[3];
	WriteAK8963Register( AK8963_CNTL,0x00);
	HAL_Delay(100);
	WriteAK8963Register( AK8963_CNTL,0x0F);
	HAL_Delay(100);
	ReadAK8963Register(AK8963_ASAX, &raw_data[0], sizeof(raw_data));

	MagBiasFactory[0] = (float)(raw_data[0] - 128)/256.0f +1.0f;
	MagBiasFactory[1] = (float)(raw_data[1] - 128)/256.0f +1.0f;
	MagBiasFactory[2] = (float)(raw_data[2] - 128)/256.0f +1.0f;

	WriteAK8963Register(AK8963_CNTL,0x00);
	HAL_Delay(100);

	WriteAK8963Register(AK8963_CNTL,MScale <<4|MMode);
	HAL_Delay(100);
}
