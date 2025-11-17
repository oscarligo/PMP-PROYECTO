#include "distance.h"

// Pines del HC-SR04
#define TRIG_PIN 14  // D5 (GPIO14)
#define ECHO_PIN 13  // D7 (GPIO13)

void setupDistance() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    Serial.println("Sensor de distancia HC-SR04 inicializado");
}

float readDistance() {
  // Generar pulso de 10µs en TRIG
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

  // Medir el tiempo del pulso ECHO
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout de 30ms

  // Calcular distancia en cm
  // Velocidad del sonido: 343 m/s = 0.0343 cm/µs
  // Distancia = (tiempo * velocidad) / 2
  float distance = (duration * 0.0343) / 2.0;

  // Retornar 0 si está fuera de rango o error
    if (distance == 0 || distance > 400) {
        return 0;
    }

    return distance;
}
