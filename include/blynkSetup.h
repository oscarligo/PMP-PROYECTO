#ifndef BLYNK_SETUP_H
#define BLYNK_SETUP_H

#include <Arduino.h>

// Virtual pins mapping (configure in Blynk app dashboard)
// V0: Temperature (float)
// V1: Pressure (float)
// V2: Altitude (float)
// V3: Distance (float)
// V4: Flame detected (0/1)
// V5: LED state (0=GREEN, 1=RED)
// V6: Button to activate buzzer (Switch)

void setupBlynk(const char* authToken);
void blynkRun();
// Force (re)connection attempt if disconnected (non-blocking style)
void blynkEnsureConnected();
// Return true if currently connected to Blynk cloud
bool blynkIsConnected();

// Publish current values to Blynk
void blynkPublish(float temperature, float pressure, float altitude,
                    float distance, bool flameDetected, bool ledIsRed);

// Query remote buzzer request (from Blynk button V6)
bool isBlynkBuzzerRequested();

#endif // BLYNK_SETUP_H
