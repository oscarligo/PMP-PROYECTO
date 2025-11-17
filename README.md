# Sistema de Monitorea con ESP8266

Este proyecto implementa un sistema de monitoreo para ESP8266 con arquitectura modular utilizando platformIO.

## Características

### Sensores
- **BMP280**: Sensor de temperatura, presión y altitud
- **HC-SR04**: Sensor ultrasónico de distancia
- **Sensor de Flama**: Detección de fuego

### Actuadores
- **LED RGB**: Indicador visual (verde/rojo)
  - Verde: Estado normal
  - Rojo: Alerta por temperatura o proximidad
- **Buzzer**: Alarma audible cuando se detecta fuego
- **Botón**: Resetear temperatura base de referencia

## Asignación de Pines (ESP8266)

### Sensores
- **D1 (GPIO5)** → BMP280 SCL
- **D2 (GPIO4)** → BMP280 SDA
- **D5 (GPIO14)** → HC-SR04 Trig
- **D7 (GPIO13)** → HC-SR04 Echo 
- **D6 (GPIO12)** → Sensor de flama DO

### Actuadores
- **D8 (GPIO15)** → Buzzer
- **D0 (GPIO16)** → LED Rojo
- **D3 (GPIO0)** → LED Verde

### Control
- **D4 (GPIO2)** → Botón (INPUT_PULLUP)

### Alimentación
- **3.3V** → BMP280, LED RGB, HC-SR04, Buzzer
- **GND** → Común para todos


## Ejemplo de Salida 

```
=== Iniciando sistema de sensores ===
LED RGB inicializado
Buzzer inicializado
Botón inicializado
Sensor de distancia HC-SR04 inicializado
Sensor de flama inicializado
BMP280 inicializado correctamente

=== Sistema listo ===
LED Verde = Estado normal
LED Rojo = Temperatura alta o proximidad detectada
Buzzer = Fuego detectado

========================================
Temperatura: 24.5 °C
Presión: 1013.2 hPa
Altitud: 120.3 m
Distancia: 45.2 cm
Flama: No detectada
========================================
```

## Estructura del Proyecto

```
PMP-PROYECTO/
├── src/
│   ├── main.cpp          // Programa principal
│   ├── bmp280.cpp        // Módulo sensor BMP280
│   ├── Distance.cpp      // Módulo sensor HC-SR04
│   ├── flame.cpp         // Módulo sensor de flama
│   ├── ledRGB.cpp        // Módulo LED RGB
│   ├── buzzer.cpp        // Módulo buzzer
│   ├── button.cpp        // Módulo botón
│   └── wifiSetup.cpp     // Configuración WiFi 
├── include/              // Headers
│   ├── bmp280.h
│   ├── distance.h
│   ├── flame.h
│   ├── ledRGB.h
│   ├── buzzer.h
│   ├── button.h
│   └── wifiSetup.h
└── platformio.ini        // Configuración del proyecto
```

