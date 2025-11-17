#ifndef LEDRGB_H
#define LEDRGB_H

#include <Arduino.h>

// Colores del LED
enum LedColor {
  LED_GREEN,
  LED_RED,
  LED_OFF
};

// Inicializar el LED RGB
void setupLED();

// Cambiar color del LED
void setLEDColor(LedColor color);

#endif
