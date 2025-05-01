function doGet(e) { 
  Logger.log(JSON.stringify(e));
  var result = 'Ok';

  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  } else {
    var sheet_id = '1bxeGckU-xJb3MSYdt2bltwRkPE6aEIB_ewGS9JrwZIg'; // Replace with your Spreadsheet ID
    var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];
    
    var Curr_Date = new Date();
    rowData[0] = Curr_Date; // Date in column A
    var Curr_Time = Utilities.formatDate(Curr_Date, "Asia/Kolkata", 'HH:mm:ss');
    rowData[1] = Curr_Time; // Time in column B
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      
      switch (param) {
        case 'temperature':
          rowData[2] = value; // Temperature in column C
          result = 'Temperature Written on column C'; 
          break;
        case 'humidity':
          rowData[3] = value; // Humidity in column D
          result += ' ,Humidity Written on column D'; 
          break;
        case 'Ground':
          rowData[4] = value; // Ground data in column E
          result += ' ,Ground Data Written on column E'; 
          break;
        default:
          result = "unsupported parameter";
      }
    }
    
    Logger.log(JSON.stringify(rowData));
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
  }
  
  return ContentService.createTextOutput(result);
}

function stripQuotes(value) {
  return value.replace(/^['"]|['"]$/g, "");
}
