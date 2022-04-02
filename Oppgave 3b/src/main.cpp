#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include "index.h"  //Web page header file

WebServer server(80);

//Enter your SSID and PASSWORD
const char* ssid = "*";
const char* password = "*";


void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleDataValues() {
 double potVoltage = analogRead(33) * 3.3 / 4095; 
 double photoVoltage = analogRead(34) * 3.3 / 4095; 
 
 String newPotvalue = String(potVoltage);
 String newPhotovalue = String(photoVoltage);

 String values = "{\"val1\":\""+newPotvalue+"\",\"val2\":\""+newPhotovalue+"\"}";
 
 server.send(200, "application/json", values); //Send new values only to client ajax request
}

void setup(void){
  Serial.begin(9600);

//ESP32 connects to your wifi 
  WiFi.mode(WIFI_STA); //Connect to wifi
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to Wifi..");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nSucessfull connection to '" + String(ssid) + "'!\n");
  
  // Desplay IP-Adress
  Serial.println("IP-Adress; ");
  Serial.print(WiFi.localIP());
 
  server.on("/", handleRoot);              //This is display page
  server.on("/sensors", handleDataValues);    //To get update of values
 
 
  server.begin();                  //Start server
  Serial.println("\nHTTP server started");
}

void loop(void){        // This routine is executed when you open its IP in browser
  server.handleClient();
  delay(1);
}