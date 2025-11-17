#ifndef BLYNK_SETUP_H
#define BLYNK_SETUP_H

#include <Arduino.h>

// Pines Virtuales
// V0: Temperature (float)
// V1: Pressure (float)
// V2: Altitude (float)
// V3: Distance (float)
// V4: Flame detected (0/1)
// V5: LED state (0=GREEN, 1=RED)
// V6: Button to activate buzzer (Switch)

void setupBlynk(const char* authToken);
void blynkRun();

// Si no está conectado, forzar intento de reconexión.
void blynkEnsureConnected();

// Retorna true si está conectado actualmente al cloud de Blynk
bool blynkIsConnected();

// Publicar valores actuales a Blynk
void blynkPublish(float temperature, float pressure, float altitude,
                    float distance, bool flameDetected, bool ledIsRed);
                    
// Consultar solicitud remota de buzzer (desde botón Blynk V6)
bool isBlynkBuzzerRequested();

#endif // BLYNK_SETUP_H
