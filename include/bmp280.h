#ifndef BMP280_H
#define BMP280_H

#include <Arduino.h>

// Inicializar el sensor BMP280
bool setupBMP280();

// Leer temperatura en °C
float readTemperature();

// Leer presión en hPa
float readPressure();

// Leer altitud en metros
float readAltitude();

#endif
