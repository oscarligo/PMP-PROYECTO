#include "buzzer.h"

// Pin del buzzer
#define BUZZER_PIN 15  // D8 (GPIO15)
\

// Frecuencia para el buzzer PASIVO 
const unsigned int BUZZER_FREQ = 2000; // Hz

/*
 * TIPOS DE BUZZER:
 * - Activo: suena sólo con aplicar HIGH (ya trae oscilador interno). Mantener HIGH = sonido constante.
 * - Pasivo: requiere señal PWM (tone) para generar sonido. HIGH fijo sólo produce un "click" inicial.
 *
 * Este código usa tone() para soportar buzzers pasivos y también funciona con activos.
 */

void setupBuzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Estado inicial silencioso
    Serial.println("Buzzer inicializado");
}

// Encender buzzer de forma continua (tono constante)
void buzzerOn() {
  // tone() gestiona internamente el pin en ESP8266
    tone(BUZZER_PIN, BUZZER_FREQ);
}

// Apagar buzzer
void buzzerOff() {
  noTone(BUZZER_PIN); // Detiene generación de onda
  digitalWrite(BUZZER_PIN, LOW); // Asegura LOW (importante para GPIO15)
}

// Beep corto con duración en ms
void buzzerBeep(int duration) {
    tone(BUZZER_PIN, BUZZER_FREQ);
    delay(duration);
    noTone(BUZZER_PIN);
    digitalWrite(BUZZER_PIN, LOW);
}
