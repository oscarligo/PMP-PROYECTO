#include "flame.h"

// Pin del sensor de flama
#define FLAME_PIN 12  // D6 (GPIO12)

void setupFlame() {
    pinMode(FLAME_PIN, INPUT);
    Serial.println("Sensor de flama inicializado");
}

bool isFlameDetected() {
  // El sensor de flama DO da HIGH cuando detecta fuego
    return digitalRead(FLAME_PIN) == HIGH;  
}
