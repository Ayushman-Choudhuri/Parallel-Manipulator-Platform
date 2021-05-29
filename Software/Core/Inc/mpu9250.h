/*
 * Filename			 : mpu9250.h
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
#ifndef MPU9250_H_
#define MPU9250_H_

#include "typedef.h"
#include "math.h"
#include "main.h"
#include "i2c.h"


/*..................................................................Register Map.............................................................................*/

/*Slave Address of MPU9250*/

#define ADO 0						/* Configure the Status of the AD0 Pin (1- High 0 - Low) */

#if ADO == 1
#define MPU9250_ADDRESS	  0x69<<1	/* Slave address of 0b1101000 as AD0 pin is HIGH*/
#else
#define MPU9250_ADDRESS	  0x68<<1	/* Slave address of 0b1101000 as AD0 pin is low*/
#endif

/* I2C Channel*/

#define MPU9250_I2C_COMM_CHECK_TRY	 	 (uint32_t)1	/*Number of trials to check I2C Device*/
#define MPU9250_I2C_COMM_CHECK_TIMEOUT	 (uint32_t)10	/*Timeout time in ms to check I2C Device*/
#define AK8963_ADDRESS_I2C_COMM_CHECK_TRY	 	 (uint32_t)1	/*Number of trials to check I2C Device*/
#define AK8963_ADDRESS_I2C_COMM_CHECK_TIMEOUT	 (uint32_t)10	/*Timeout time in ms to check I2C Device*/


/* Gyroscope Register Addresses*/

#define SELF_TEST_X_GYRO  0x00  /* Gyroscope Self Test Register*/
#define SELF_TEST_Y_GYRO  0x01
#define SELF_TEST_Z_GYRO  0x02

#define XG_OFFSET_H       0x13  /* User Defined Gyroscope Offset Register*/
#define XG_OFFSET_L       0x14
#define YG_OFFSET_H       0x15
#define YG_OFFSET_L       0x16
#define ZG_OFFSET_H       0x17
#define ZG_OFFSET_L       0x18

#define SMPLRT_DIV        0x19	/* Sample Rate Divider Register*/

#define CONFIG            0x1A	/* Configuration Register*/

#define GYRO_CONFIG       0x1B	/*Gyroscope Configuration Register*/

#define GYRO_XOUT_H       0x43	/*Gyroscope Measurement*/
#define GYRO_XOUT_L       0x44
#define GYRO_YOUT_H       0x45
#define GYRO_YOUT_L       0x46
#define GYRO_ZOUT_H       0x47
#define GYRO_ZOUT_L       0x48


/* Accelerometer Register Addresses*/

#define SELF_TEST_X_ACCEL 0x0D 	/*Accelerometer Self Test Register*/
#define SELF_TEST_Y_ACCEL 0x0E
#define SELF_TEST_Z_ACCEL 0x0F

#define ACCEL_CONFIG      0x1C	/*Accelerometer Configuration*/
#define ACCEL_CONFIG2     0x1D	/*Accelerometer Configuration 2*/
#define LP_ACCEL_ODR      0x1E  /*Low Power Accelerometer ODR Control*/
#define WOM_THR           0x1F	/*Wake-on Motion Threshold*/

#define ACCEL_XOUT_H      0x3B	/*Accelerometer Measurements*/
#define ACCEL_XOUT_L      0x3C
#define ACCEL_YOUT_H      0x3D
#define ACCEL_YOUT_L      0x3E
#define ACCEL_ZOUT_H      0x3F
#define ACCEL_ZOUT_L      0x40

#define ACCEL_INTEL_CTRL  0x69	/*Accelerometer Interrupt Control*/

#define XA_OFFSET_H       0x77	/* Upper bits of X Accelerometer offset cancellation*/
#define XA_OFFSET_L       0x78	/* Lower bits of X accelerometer offset cancellation*/
#define YA_OFFSET_H       0x7A	/* Upper bits of Y Accelerometer offset cancellation*/
#define YA_OFFSET_L       0x7B	/* Lower bits of Y accelerometer offset cancellation*/
#define ZA_OFFSET_H       0x7D	/* Upper bits of Z Accelerometer offset cancellation*/
#define ZA_OFFSET_L       0x7E	/* Lower bits of Z accelerometer offset cancellation*/

/*Magnetometer Register Addresses*/

#define AK8963_ADDRESS    0x0C<<1
#define AK8963_WHO_AM_I   0x00 /*should return 0x48*/
#define AK8963_INFO       0x01
#define AK8963_ST1        0x02 /*data ready status bit 0*/
#define AK8963_XOUT_L     0x03 /*data*/
#define AK8963_XOUT_H     0x04
#define AK8963_YOUT_L     0x05
#define AK8963_YOUT_H     0x06
#define AK8963_ZOUT_L     0x07
#define AK8963_ZOUT_H     0x08
#define AK8963_ST2        0x09  /*Data overflow bit 3 and data read error status bit 2*/
#define AK8963_CNTL       0x0A  /*Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0*/
#define AK8963_ASTC       0x0C  /* Self test control*/
#define AK8963_I2CDIS     0x0F  /*I2C disable*/
#define AK8963_ASAX       0x10  /*Fuse ROM x-axis sensitivity adjustment value */
#define AK8963_ASAY       0x11  /*Fuse ROM y-axis sensitivity adjustment value*/
#define AK8963_ASAZ       0x12  /* Fuse ROM z-axis sensitivity adjustment value */

/*Temperature Sensor Register Addresses*/
#define TEMP_OUT_H        0x41	/*Temperature Measurement*/
#define TEMP_OUT_L        0x42

/*Communication Register Addresses*/
#define FIFO_EN           0x23	/*FIFO Enable*/
#define I2C_MST_CTRL      0x24	/*I2C Master Control*/

#define I2C_SLV0_ADDR     0x25	/*I2C Slave 0 Control*/
#define I2C_SLV0_REG      0x26
#define I2C_SLV0_CTRL     0x27

#define I2C_SLV1_ADDR     0x28	/*I2C Slave 1 Control*/
#define I2C_SLV1_REG      0x29
#define I2C_SLV1_CTRL     0x2A

#define I2C_SLV2_ADDR     0x2B	/*I2C Slave 2 Control*/
#define I2C_SLV2_REG      0x2C
#define I2C_SLV2_CTRL     0x2D

#define I2C_SLV3_ADDR     0x2E	/*I2C Slave 3 Control*/
#define I2C_SLV3_REG      0x2F
#define I2C_SLV3_CTRL     0x30

#define I2C_SLV4_ADDR     0x31	/*I2C Slave 4 Control*/
#define I2C_SLV4_REG      0x32
#define I2C_SLV4_DO       0x33
#define I2C_SLV4_CTRL     0x34
#define I2C_SLV4_DI       0x35

#define I2C_SLV0_DO       0x63	/*I2C Slave 0 Data Out*/
#define I2C_SLV1_DO       0x64	/*I2C Slave 1 Data Out*/
#define I2C_SLV2_DO       0x65	/*I2C Slave 2 Data Out*/
#define I2C_SLV3_DO       0x66	/*I2C Slave 3 Data Out*/

#define I2C_MST_STATUS    0x36	/*I2C Master Status*/

#define I2C_MST_DELAY_CTRL 0x67	/*I2C Master Delay Control*/

#define SIGNAL_PATH_RESET 0x68	/*Signal Path Reset*/

#define INT_PIN_CFG       0x37	/*INT Pin / Bypass Enable Configuration*/
#define INT_ENABLE        0x38	/*Interrupt Enable*/
#define INT_STATUS        0x3A	/*Interrupt Status*/

#define USER_CTRL         0x6A  /*User Control (Bit 7 Enable DMP and Bit 3 Reset DMP) */

#define FIFO_COUNTH       0x72	/*FIFO Count Registers*/
#define FIFO_COUNTL       0x73
#define FIFO_R_W          0x74

/*External Sensors  Register Addresses*/

#define EXT_SENS_DATA_00  0x49
#define EXT_SENS_DATA_01  0x4A
#define EXT_SENS_DATA_02  0x4B
#define EXT_SENS_DATA_03  0x4C
#define EXT_SENS_DATA_04  0x4D
#define EXT_SENS_DATA_05  0x4E
#define EXT_SENS_DATA_06  0x4F
#define EXT_SENS_DATA_07  0x50
#define EXT_SENS_DATA_08  0x51
#define EXT_SENS_DATA_09  0x52
#define EXT_SENS_DATA_10  0x53
#define EXT_SENS_DATA_11  0x54
#define EXT_SENS_DATA_12  0x55
#define EXT_SENS_DATA_13  0x56
#define EXT_SENS_DATA_14  0x57
#define EXT_SENS_DATA_15  0x58
#define EXT_SENS_DATA_16  0x59
#define EXT_SENS_DATA_17  0x5A
#define EXT_SENS_DATA_18  0x5B
#define EXT_SENS_DATA_19  0x5C
#define EXT_SENS_DATA_20  0x5D
#define EXT_SENS_DATA_21  0x5E
#define EXT_SENS_DATA_22  0x5F
#define EXT_SENS_DATA_23  0x60

/*Power Management  Register Addresses*/

#define PWR_MGMT_1        0x6B
#define PWR_MGMT_2        0x6C

/*Other  Register Addresses*/

#define WHO_AM_I_MPU9250  0x75 /* Register to indicate to user which device is accessed.(Should return 0x71)*/


/* Initial Input Parameters */

enum AccelScale				   /*Input Parameters for Accelerometer Full Scale Range Setting*/
{

	AccelScale_2G = 0,
	AccelScale_4G = 1,
	AccelScale_8G = 2,
	AccelScale_16G= 3
};

enum GyroScale				  /*Input Parameters for Gyroscope Full Scale Range Setting*/
{

	GyroScale_250DPS = 	0,
	GyroScale_500DPS = 	1,
	GyroScale_1000DPS= 	2,
	GyroScale_2000DPS= 	3
};

enum MagScale			 	  /*Input Parameters for Magnetometer Full Scale Setting*/
{
	MagScale_14BITS = 0,
	MagScale_16BITS = 1
};

/* Global Variables*/

HAL_StatusTypeDef MPUReturnStatus;

extern float32_t AccelResolution ;
extern float32_t GyroResolution;
extern float32_t MagResolution ;



/*..............................................................................Function Prototypes....................................................................*/

bool MPU9250IsConnected();
void MPU9250Init();
void AK8963Init();

#endif /* MPU9250_H_ */
