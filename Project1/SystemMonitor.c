#include "SystemMonitor.h"

void SystemMonitor_GetAvailableSensors(uint8_t avail_sensors[], uint16_t *s_count) {

	int i;
	uint8_t temperature;

	// Check how many sensors are available with SystemMonitor API
	for (i = 0; i < 256; i++)
	{
		if (SystemMonitor_GetTemp(i, &temperature) == SUCCESS)
		{
			(*s_count)++;
		}
	}

	// Fill the array with available sensors
	for (i = 0; i < (*s_count); i++)
	{
		avail_sensors[i] = i;
	}
};

STATUS_CODE SystemMonitor_GetTemp(uint8_t sensor_id, uint8_t *temp) {

	// Generate some diffrent STATUS_CODE for sensors
	if (sensor_id < 100)
	{
		*temp = (rand() % 250);
		return SUCCESS;
	}

	if (sensor_id >= 100 && sensor_id < 200)
	{
		return NO_SENSOR;
	}

	if (sensor_id >= 200)
	{
		return ERROR;
	}
};