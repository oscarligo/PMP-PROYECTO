#include "ledRGB.h"

// Pines del LED RGB
#define LED_RED_PIN 16   // D0 (GPIO16)
#define LED_GREEN_PIN 0  // D3 (GPIO0) - Nota: GPIO0 debe estar HIGH en boot normal

void setupLED() {
    // Configurar pines como OUTPUT
    pinMode(LED_RED_PIN, OUTPUT);
    pinMode(LED_GREEN_PIN, OUTPUT);

    // Asegurar que ambos estén apagados primero
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);

    delay(100); 

    // Iniciar con LED verde
    setLEDColor(LED_GREEN);
    Serial.println("LED RGB inicializado (Verde=D3/GPIO0, Rojo=D0/GPIO16)");
}

void setLEDColor(LedColor color) {

    switch(color) {
        case LED_GREEN:
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
        break;
        case LED_RED:
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_GREEN_PIN, LOW);
        break;
        case LED_OFF:
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, LOW);
        break;
    }
}
