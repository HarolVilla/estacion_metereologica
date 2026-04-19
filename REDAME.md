# 🌦️ Estación Meteorológica ESP32 (AHT20 + BMP280)

Proyecto de estación meteorológica basado en ESP32 que permite medir, visualizar y registrar datos ambientales en tiempo real.

El sistema combina sensores, pantalla física, servidor web y registro de datos en hoja de cálculo para crear un sistema completo de monitorización.

---

## 🚀 Funcionalidades

* 🌡️ Medición de temperatura
* 💧 Medición de humedad
* 🌬️ Medición de presión atmosférica
* 📟 Visualización en pantalla I2C (tiempo real)
* 🌐 Servidor web local desde el ESP32
* 📊 Registro de datos en hoja de cálculo (Excel / CSV)
* 📈 Análisis automático diario de datos

---

## 🧠 Hardware utilizado

* ESP32U
* Sensor AHT20 (temperatura y humedad)
* Sensor BMP280 (presión atmosférica)
* Pantalla I2C (OLED / LCD)

---

## 🌐 Funcionamiento del sistema

El ESP32 realiza las siguientes tareas de forma continua:

1. Lee los datos de los sensores AHT20 y BMP280
2. Muestra los valores en la pantalla I2C
3. Genera un servidor web accesible desde la red local
4. Envía o guarda los datos en una hoja de cálculo

---

## 💻 Acceso a la web

El dispositivo crea un servidor web accesible desde cualquier dispositivo conectado a la misma red WiFi:

```
http://IP_DEL_ESP32
```

Desde esta web se pueden visualizar los datos en tiempo real sin necesidad de instalar ninguna aplicación.

---

## 📊 Registro y análisis de datos

Los datos recogidos se almacenan en una hoja de cálculo (Excel / CSV), donde:

* Se registran lecturas periódicas
* Se genera automáticamente un análisis diario

### 📈 Métricas calculadas:

* Temperatura máxima diaria
* Temperatura mínima diaria
* Humedad media
* Presión atmosférica

Esto permite llevar un control completo del entorno a lo largo del tiempo.

---

## 📁 Estructura del proyecto

```
estacion-meteorologica-esp32/
│
├── codigo_esp32/
│   └── estacion_meteorologica.ino
│
├── datos/
│   ├── registros.csv
│   └── script.js
│
├── imagenes/
│   └── montaje.jpg
│
└── README.md
```

---

## 📷 Montaje

El sistema está basado en comunicación I2C para sensores y pantalla, simplificando el cableado.

(Añadir imagen en la carpeta `/imagenes`)

---

## ⚙️ Estado del proyecto

✔ Sistema funcional
✔ Monitorización en tiempo real
✔ Registro de datos activo
🔧 En desarrollo de mejoras

---

## 🚀 Próximas mejoras

* Acceso remoto desde fuera de la red local
* Sistema de alertas (temperatura alta/baja)
* Interfaz web más avanzada

---

## 👨‍💻 Autor

Harol Lozano

---
