/******************************************************
* Universidad del Valle de Guatemala
* Facultad de Ingeniería
* Curso: Microprocesadores
* Proyecto: Proyecto Final de Curso
*
* Descripción: Envío de lecturas de temperatura, 
* presión, altitud, distancia y detección de llama 
* desde un ESP8266 hacia Google Sheets
*******************************************************/

function doGet(e) { 
  Logger.log(JSON.stringify(e));
  var result = 'Ok';
  
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  } else {
    var sheet_id = '1Y8cAc1fjBw5YBQoIkWO8lxLyRh14hbSeA2cK8ac0TlM';  // ID de tu hoja
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1; 
    var rowData = [];
    
    var Curr_Date = new Date();
    rowData[0] = Utilities.formatDate(Curr_Date, "America/Guatemala", "yyyy-MM-dd"); // Fecha
    rowData[1] = Utilities.formatDate(Curr_Date, "America/Guatemala", "HH:mm:ss");   // Hora
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      
      switch (param) {
        case 'temperature':
          rowData[2] = value; // Columna C
          result += ', Temperature written on column C'; 
          break;
          
        case 'pressure':
          rowData[3] = value; // Columna D
          result += ', Pressure written on column D'; 
          break;
          
        case 'altitude':
          rowData[4] = value; // Columna E
          result += ', Altitude written on column E';
          break;
          
        case 'distance':
          rowData[5] = value; // Columna F
          result += ', Distance written on column F';
          break;
          
        case 'flame':
          rowData[6] = value; // Columna G
          result += ', Flame written on column G';
          break;
          
        default:
          result += ', Unsupported parameter: ' + param;
      }
    }
    
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  
  return ContentService.createTextOutput(result);
}

function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}
