
📡 ESP32 + AHT20 + BMP280 + Pantalla I2C

🔌 Guía de conexión del hardware

Este proyecto utiliza un ESP32 junto con sensores de temperatura, humedad, presión y una pantalla I2C para mostrar datos y enviarlos a Google Sheets.

🧠 Arquitectura del sistema

Todos los dispositivos se conectan mediante el bus I2C compartido:

📟 Pantalla I2C (LCD/OLED)

🌡️ Sensor AHT20 (temperatura y humedad)

🌬️ Sensor BMP280 (presión y temperatura)

📡 ESP32 como controlador principal

📍 Pines I2C del ESP32

Señal	GPIO

SDA	GPIO 21

SCL	GPIO 22

🔌 Conexiones

📟 Pantalla I2C

Pantalla	ESP32

VCC	3.3V o 5V*

GND	GND

SDA	GPIO 21

SCL	GPIO 22

* Depende del módulo (recomendado 3.3V si no estás seguro)

🌡️ Sensor AHT20 + 🌬️ Sensor BMP280


AHT20	ESP32

VCC	3.3V

GND	GND

SDA	GPIO 21

SCL	GPIO 22


⚠️ Consideraciones importantes

🔴 Alimentación

Todos los módulos deben compartir GND común

Preferible alimentar sensores a 3.3V

🔴 Fallos típicos

❌ No detecta sensores → revisar SDA/SCL

❌ Lecturas en 0x00 → problema de conexión o alimentación

❌ Pantalla funciona pero sensores no → conflicto en bus I2C

