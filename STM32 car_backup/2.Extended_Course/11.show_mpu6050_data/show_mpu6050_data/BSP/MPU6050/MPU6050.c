#include "mpu6050.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
										  0, -1, 0,
										  0, 0, 1};
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;
float Pitch, Roll, Yaw;
unsigned long sensor_timestamp;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];

// 函数功能：MPU数据初始化
// 传入参数:无
// Function function: MPU data initialization
// Incoming parameter: None
void MPU6050_Init(void)
{
	int result = 0;
	result = mpu_init();
	if (!result)
	{
#ifdef DEBUG_USARTx
		printf("mpu initialization complete......\n "); // mpu initialization complete

		if (!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL)) // mpu_set_sensor
			printf("mpu_set_sensor complete ......\n");
		else
			printf("mpu_set_sensor come across error ......\n");

		if (!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL)) // mpu_configure_fifo
			printf("mpu_configure_fifo complete ......\n");
		else
			printf("mpu_configure_fifo come across error ......\n");

		if (!mpu_set_sample_rate(DEFAULT_MPU_HZ)) // mpu_set_sample_rate
			printf("mpu_set_sample_rate complete ......\n");
		else
			printf("mpu_set_sample_rate error ......\n");

		if (!dmp_load_motion_driver_firmware()) // dmp_load_motion_driver_firmvare
			printf("dmp_load_motion_driver_firmware complete ......\n");
		else
			printf("dmp_load_motion_driver_firmware come across error ......\n");

		if (!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) // dmp_set_orientation
			printf("dmp_set_orientation complete ......\n");
		else
			printf("dmp_set_orientation come across error ......\n");

		if (!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
								DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
								DMP_FEATURE_GYRO_CAL)) // dmp_enable_feature
			printf("dmp_enable_feature complete ......\n");
		else
			printf("dmp_enable_feature come across error ......\n");

		if (!dmp_set_fifo_rate(DEFAULT_MPU_HZ)) // dmp_set_fifo_rate
			printf("dmp_set_fifo_rate complete ......\n");
		else
			printf("dmp_set_fifo_rate come across error ......\n");

		run_self_test();

		if (!mpu_set_dmp_state(1))
			printf("mpu_set_dmp_state complete ......\n");
		else
			printf("mpu_set_dmp_state come across error ......\n");
#else
		mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
		mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
		mpu_set_sample_rate(DEFAULT_MPU_HZ);
		dmp_load_motion_driver_firmware();
		dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation));
		dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
						   DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
						   DMP_FEATURE_GYRO_CAL);
		dmp_set_fifo_rate(DEFAULT_MPU_HZ);
		run_self_test();
		mpu_set_dmp_state(1);
#endif
	}
	else // MPU6050
	{
		while (1)
		{
			printf("mpu6050 error ,please reset!!\r\n");
			Delay_ms(300);
		}
	}
}

// 函数功能:处理MPU信息的函数
// 传入参数:无
// Function function: a function for processing IMU information
// Incoming parameter: None
void MPU6050_Pose(void)
{

	dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);
	/* Gyro and accel data are written to the FIFO by the DMP in chip frame and hardware units.
	 * This behavior is convenient because it keeps the gyro and accel outputs of dmp_read_fifo and mpu_read_fifo consistent.
	 **/
	/*if (sensors & INV_XYZ_GYRO )
	send_packet(PACKET_TYPE_GYRO, gyro);
	if (sensors & INV_XYZ_ACCEL)
	send_packet(PACKET_TYPE_ACCEL, accel); */
	/* Unlike gyro and accel, quaternions are written to the FIFO in the body frame, q30.
	 * The orientation is set by the scalar passed to dmp_set_orientation during initialization.
	 **/

	if (sensors & INV_WXYZ_QUAT)
	{
		q0 = quat[0] / q30;
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30;

		Pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;									// pitch
		Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;		// roll
		Yaw = atan2(2 * (q1 * q2 + q0 * q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * 57.3; // yaw

		//		//Print fused data 打印融合数据
		//		printf("pitch = %.3f\t",Pitch);
		//		printf("Roll  = %.3f\t",Roll);
		//		printf("Yaw   = %.3f\r\n",Yaw);

		// Print raw data 打印原始数据
		printf("gyro[0] = %d\t gyro[1] = %d\t gyro[2] = %d\t \r\n", gyro[0], gyro[1], gyro[2]);
		printf("accel[0] = %d\t accel[1] = %d\t accel[2] = %d\t \r\n", accel[0], accel[1], accel[2]);
	}
}
