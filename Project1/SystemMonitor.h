#ifndef SystemMonitor_h
#define SystemMonitor_h
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Bit field structure for warning and critical signals
struct {
	uint8_t TEMP_CRITICAL : 1;
	uint8_t TEMP_WARNING : 1;
	uint8_t reserved : 6;
} SystemMonitor_TempSignals;

// Status codes for sensors
typedef enum STATUS_CODE { SUCCESS, NO_SENSOR, ERROR } STATUS_CODE;

// Get a status code and temperature for a sensor
STATUS_CODE SystemMonitor_GetTemp(uint8_t, uint8_t*);
// Get an array for available sensors
void SystemMonitor_GetAvailableSensors(uint8_t[], uint16_t*);

#endif