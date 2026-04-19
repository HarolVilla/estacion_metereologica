📊 Paso a paso (lo que tienes que hacer)
1. Subir el Excel a Google Drive
Abres Google Drive
Subes o creas una hoja de cálculo (Google Sheets)
La renombras si quieres (ej: DATOS ESP32)
2. Abrir Apps Script

En la hoja de cálculo:

Menú superior → Extensiones
→ Apps Script
3. Pegar el código

Borras lo que haya y pegas esto:

function doPost(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("DATOS");
  var data = JSON.parse(e.postData.contents);

  if (sheet.getLastRow() == 0) {
    sheet.appendRow(["Fecha","Temp BMP","Temp AHT","Humedad","Presion"]);
  }

  sheet.appendRow([
    new Date(),
    data.temp_bmp,
    data.temp_aht,
    data.hum,
    data.pres
  ]);

  return ContentService.createTextOutput("OK");
}


4. MUY IMPORTANTE: hoja correcta

Tu Google Sheet debe tener una pestaña llamada exactamente:

👉 DATOS

(Si no existe, créala o cambia el nombre en el script)

5. Desplegar como Web App
Botón superior: Implementar
→ Nueva implementación
En la rueda dentada ⚙️ seleccionas:
👉 Aplicación web

Configura así:

Ejecutar como: tú mismo
Quién tiene acceso: 👉 Cualquier usuario

Luego:

Pulsas Implementar
Aceptas permisos de Google
6. IMPORTANTE (te dará la URL)

Al final te dará una URL tipo:

https://script.google.com/macros/s/XXXX/exec

Esa es la que tienes que poner en el ESP32 para enviar datos.
