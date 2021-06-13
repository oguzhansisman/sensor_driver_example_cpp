#include <iostream>
#include <stdint.h>
#include <stdlib.h>

#include"sensor.hpp"


int main()
{
	sensor imu_sensor(0x16);
	
	uint8_t rx_buffer[200] = {0};
	uint8_t tx_buffer[200] = {0};

	//!< fill tx_buffer
	for (int i = 0; i < 50; i++)
	{
		tx_buffer[i] = i;
	}


	imu_sensor.write(12, &tx_buffer[20], 10);

	imu_sensor.read(12, rx_buffer, 10);


	return 0;
}