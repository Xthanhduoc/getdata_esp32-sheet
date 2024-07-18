#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"  // Include Adafruit TCS34725 library
const char* host = "script.google.com";
const int httpsPort = 443;

String GAS_ID = "AKfycbxv0HykLFnesfFmZTCf9eCmMfqTYd7ZUeo5YFxRetxj5uJQmnnUmuq4x4KgnXiF2l3OgA";

const char* ssid = "K70E";  // Tên WiFi của bạn
const char* password = "99999999";      // Mật khẩu WiFi của bạn
bool irState = false;
unsigned long currentTime = 0;
unsigned long currentTime2 = 0;

const char* root_ca=\
"-----BEGIN CERTIFICATE-----\n"\
"MIIFVzCCAz+gAwIBAgINAgPlk28xsBNJiGuiFzANBgkqhkiG9w0BAQwFADBHMQsw\n"\
"CQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZpY2VzIExMQzEU\n"\
"MBIGA1UEAxMLR1RTIFJvb3QgUjEwHhcNMTYwNjIyMDAwMDAwWhcNMzYwNjIyMDAw\n"\
"MDAwWjBHMQswCQYDVQQGEwJVUzEiMCAGA1UEChMZR29vZ2xlIFRydXN0IFNlcnZp\n"\
"Y2VzIExMQzEUMBIGA1UEAxMLR1RTIFJvb3QgUjEwggIiMA0GCSqGSIb3DQEBAQUA\n"\
"A4ICDwAwggIKAoICAQC2EQKLHuOhd5s73L+UPreVp0A8of2C+X0yBoJx9vaMf/vo\n"\
"27xqLpeXo4xL+Sv2sfnOhB2x+cWX3u+58qPpvBKJXqeqUqv4IyfLpLGcY9vXmX7w\n"\
"Cl7raKb0xlpHDU0QM+NOsROjyBhsS+z8CZDfnWQpJSMHobTSPS5g4M/SCYe7zUjw\n"\ 
"TcLCeoiKu7rPWRnWr4+wB7CeMfGCwcDfLqZtbBkOtdh+JhpFAz2weaSUKK0Pfybl\n"\
"qAj+lug8aJRT7oM6iCsVlgmy4HqMLnXWnOunVmSPlk9orj2XwoSPwLxAwAtcvfaH\n"\
"szVsrBhQf4TgTM2S0yDpM7xSma8ytSmzJSq0SPly4cpk9+aCEI3oncKKiPo4Zor8\n"\
"Y/kB+Xj9e1x3+naH+uzfsQ55lVe0vSbv1gHR6xYKu44LtcXFilWr06zqkUspzBmk\n"\
"MiVOKvFlRNACzqrOSbTqn3yDsEB750Orp2yjj32JgfpMpf/VjsPOS+C12LOORc92\n"\
"wO1AK/1TD7Cn1TsNsYqiA94xrcx36m97PtbfkSIS5r762DL8EGMUUXLeXdYWk70p\n"\
"aDPvOmbsB4om3xPXV2V4J95eSRQAogB/mqghtqmxlbCluQ0WEdrHbEg8QOB+DVrN\n"\
"VjzRlwW5y0vtOUucxD/SVRNuJLDWcfr0wbrM7Rv1/oFB2ACYPTrIrnqYNxgFlQID\n"\
"AQABo0IwQDAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4E\n"\
"FgQU5K8rJnEaK0gnhS9SZizv8IkTcT4wDQYJKoZIhvcNAQEMBQADggIBAJ+qQibb\n"\
"C5u+/x6Wki4+omVKapi6Ist9wTrYggoGxval3sBOh2Z5ofmmWJyq+bXmYOfg6LEe\n"\
"QkEzCzc9zolwFcq1JKjPa7XSQCGYzyI0zzvFIoTgxQ6KfF2I5DUkzps+GlQebtuy\n"\
"h6f88/qBVRRiClmpIgUxPoLW7ttXNLwzldMXG+gnoot7TiYaelpkttGsN/H9oPM4\n"\
"7HLwEXWdyzRSjeZ2axfG34arJ45JK3VmgRAhpuo+9K4l/3wV3s6MJT/KYnAK9y8J\n"\
"ZgfIPxz88NtFMN9iiMG1D53Dn0reWVlHxYciNuaCp+0KueIHoI17eko8cdLiA6Ef\n"\
"MgfdG+RCzgwARWGAtQsgWSl4vflVy2PFPEz0tv/bal8xa5meLMFrUKTX5hgUvYU/\n"\
"Z6tGn6D/Qqc6f1zLXbBwHSs09dR2CQzreExZBfMzQsNhFRAbd03OIozUhfJFfbdT\n"\
"6u9AWpQKXCBfTkBdYiJ23//OYb2MI3jSNwLgjt7RETeJ9r/tSQdirpLsQBqvFAnZ\n"\
"0E6yove+7u7Y/9waLd64NnHi/Hm3lCXRSHNboTXns5lndcEZOitHTtNCjv0xyBZm\n"\
"2tIMPNuzjsmhDYAPexZ3FL//2wmUspO8IFgV6dtxQ/PeEMMA3KgqlbbC1j+Qa3bb\n"\
"bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c==\n"
"-----END CERTIFICATE-----\n";
// TCS34725 configuration
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(115200);

  // Initialize TCS34725 sensor
  if (!tcs.begin()) {
    Serial.println("Could not find a valid TCS34725 sensor, check wiring!");
    while (1);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  int timeWait = 30; // Wait time for WiFi connection (30 seconds)
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
    timeWait--;
    if (timeWait == 0) {
      Serial.println("WiFi connection failed. Restarting...");
      delay(5000);
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read color data from TCS34725 every 1 second
  if (millis() - currentTime > 1000) {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    Serial.print("Color (R,G,B): ");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);

    // Send data to Google Sheets
    sendData(r, g, b);

    currentTime = millis();
  }
}

void sendData(uint16_t red, uint16_t green, uint16_t blue) {
  // Prepare data to send to Google Sheets
  String str = "r=" + String(red) + "&g=" + String(green) + "&b=" + String(blue);
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + GAS_ID + "/exec?" + str;
  Serial.print("Sending data to Google Sheets. URL: ");
  Serial.println(url);

  // Send HTTP GET request to write data
  http.begin(url, root_ca);
  int httpCode = http.GET();

  // Check result of sending data and close connection
  if (httpCode > 0) {
    Serial.print("HTTP response code: ");
    Serial.println(httpCode);
  } else {
    Serial.println("Error sending data.");
  }

  http.end();
}

/*
var sheet_id = '17Q8MnJ3Jw6zoXKo9CpLx9hA5F832AkTWilws89D_Q38';  // Spreadsheet ID
var sheet = SpreadsheetApp.openById(sheet_id).getActiveSheet();

function doGet(e) {
  var r = e.parameter.r;  // Get red value
  var g = e.parameter.g;  // Get green value
  var b = e.parameter.b;  // Get blue value

  // Check if RGB values exist
  if (r !== undefined && g !== undefined && b !== undefined) {
    var newRow = sheet.getLastRow() + 1;
    var rowData = [];

    var currDate = new Date();
    rowData[0] = currDate;  // Date in column A

    var currTime = Utilities.formatDate(currDate, Session.getScriptTimeZone(), 'HH:mm:ss');
    rowData[1] = currTime;  // Time in column B

    rowData[2] = r;  // Red value in column C
    rowData[3] = g;  // Green value in column D
    rowData[4] = b;  // Blue value in column E

    // Append new row with RGB data to the spreadsheet
    sheet.appendRow(rowData);

    return ContentService.createTextOutput("Success");
  } else {
    return ContentService.createTextOutput("Error! Missing parameters.");
  }
}
*/