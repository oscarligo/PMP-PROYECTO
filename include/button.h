#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

// Inicializar el botón
void setupButton();

// Leer estado del botón (retorna true si está presionado)
bool isButtonPressed();

// Detectar si el botón fue presionado (con debounce)
bool buttonPressedDebounce();

#endif
