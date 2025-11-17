/**
 * CONFIGURACIÓN DE PINES - ESP8266 NodeMCU
 * ========================================
 * 
 * Este archivo documenta la asignación completa de pines para el proyecto.
 */

#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// ============================================
// SENSORES
// ============================================

// BMP280 - Sensor de Temperatura/Presión (I2C)
#define BMP_SDA     4   // D2 (GPIO4)
#define BMP_SCL     5   // D1 (GPIO5)
#define BMP_ADDR    0x76  // Dirección I2C (puede ser 0x76 o 0x77)

// HC-SR04 - Sensor de Distancia Ultrasónico
#define TRIG_PIN    14  // D5 (GPIO14)
#define ECHO_PIN    13  // D7 (GPIO13) - ¡USAR DIVISOR DE VOLTAJE 5V→3.3V!

// Sensor de Flama
#define FLAME_PIN   12  // D6 (GPIO12)

// ============================================
// ACTUADORES
// ============================================

// Buzzer
#define BUZZER_PIN  15  // D8 (GPIO15)

// LED RGB (solo Rojo y Verde)
#define LED_RED_PIN   16  // D0 (GPIO16)
#define LED_GREEN_PIN  0  // D3 (GPIO0)

// ============================================
// CONTROL
// ============================================

// Botón (configurado como INPUT_PULLUP)
#define BUTTON_PIN  2   // D4 (GPIO2)


#endif // PIN_CONFIG_H
