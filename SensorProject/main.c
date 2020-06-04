#define _CRT_SECURE_NO_WARNINGS
#define CONFIG "config.txt"
#include <time.h>
#include "SystemMonitor.h"

// Global variables for threshold temperatures values in *C
int critical;
int warning;
// Currently available sensors
uint8_t available_sensors[255];
// Sensor count as uint16_t for a scenerio when all 256 sensors are working
uint16_t sensor_count = 0;

// Status for temperatures from configuration file
typedef enum CONFIG_CHECK { FOUND, NOT_FOUND } CONFIG_CHECK;
// Get and set threshold values of temperature
CONFIG_CHECK GetThresholdTemp(int*, int*);
// Check if temperature of sensor is below threshold if not set a TempSignal
void CheckThresholdTemp(uint8_t[], uint16_t);

int main() {

	// Generator for random temperature values
	srand(time(NULL));
	// Set negative values for temperature being over the threshold values
	SystemMonitor_TempSignals.TEMP_CRITICAL = 0;
	SystemMonitor_TempSignals.TEMP_WARNING = 0;

	// Check if threshold temperatures values are found, then execute program
	if (GetThresholdTemp(&critical, &warning) == FOUND)
	{
		SystemMonitor_GetAvailableSensors(available_sensors, &sensor_count);
		CheckThresholdTemp(available_sensors, sensor_count);
	}

	return 0;
}

CONFIG_CHECK GetThresholdTemp(int *crit, int *warn) {

	FILE *fp;
	int i;

	// Open a configuration file
	fp = fopen(CONFIG, "r");

	// Check if the file exists
	if (fp == NULL)
	{
		printf("Error, file does not exist.\n");
		exit(0);
	}

	// Read and set values of critical and warning temperatures from a configuration file
	fscanf_s(fp, "[CRITICAL] = %d [WARNING] = %d", crit, warn);

	// Check if critical and warning temperatures are correct
	if ((*crit >= 0) && (*crit < 256) && (*warn >= 0) && (*warn < 256))
	{
		return FOUND;
	}

	else
	{
		return NOT_FOUND;
	}

	// Close a file
	fclose(fp);
};

void CheckThresholdTemp(uint8_t avail_sensors[], uint16_t s_count) {

	int i;
	uint8_t temperature;

	// For every available sensor
	for (i = 0; i < s_count; i++)
	{
		if (SystemMonitor_GetTemp(avail_sensors[i], &temperature) == SUCCESS)
		{
			// Check if temperature is over critical threshold
			if (critical < temperature)
			{
				SystemMonitor_TempSignals.TEMP_WARNING = 0;
				SystemMonitor_TempSignals.TEMP_CRITICAL = 1;
			}

			// Check if temperature is over warning threshold when not over critical
			else if (warning < temperature)
			{
				SystemMonitor_TempSignals.TEMP_WARNING = 1;
			}
		}
	}
};