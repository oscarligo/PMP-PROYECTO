#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

// Inicializar el buzzer
void setupBuzzer();

// Activar el buzzer
void buzzerOn();

// Desactivar el buzzer
void buzzerOff();

// Hacer sonar el buzzer por un tiempo (ms)
void buzzerBeep(int duration);

#endif
