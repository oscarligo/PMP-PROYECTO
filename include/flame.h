#ifndef FLAME_H
#define FLAME_H

#include <Arduino.h>

// Inicializar el sensor de flama
void setupFlame();

// Detectar si hay flama (retorna true si detecta fuego)
bool isFlameDetected();

#endif
