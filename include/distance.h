#ifndef DISTANCE_H
#define DISTANCE_H

#include <Arduino.h>

// Inicializar el sensor de distancia HC-SR04
void setupDistance();

// Leer distancia en centímetros
float readDistance();

#endif
