#include "button.h"

// Pin del botón
#define BUTTON_PIN 2  // D4 (GPIO2)

// Variables para debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;
int buttonState = HIGH;

void setupButton() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("Botón inicializado");
}

bool isButtonPressed() {
  // El botón está presionado cuando lee LOW (por INPUT_PULLUP)
    return digitalRead(BUTTON_PIN) == LOW;
}

bool buttonPressedDebounce() {
    
    int reading = digitalRead(BUTTON_PIN);

    if (reading != lastButtonState) {
    lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading != buttonState) {

            buttonState = reading;

            if (buttonState == LOW) {

            lastButtonState = reading;
            return true;

            }

        }
    }

    lastButtonState = reading;
    return false;
}
