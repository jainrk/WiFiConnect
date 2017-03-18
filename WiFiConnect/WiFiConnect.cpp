/*  
	March 20 2017 Raj Jain
	The WiFiConnect class is created to have one class do the work to connect an ESP8266 to a router.
	It removes the spaghetti of code from you main sketch and encapsulates it into reusable class. 
	Parts of this code have come from various sources floating around in various resources
	This project is licensed under the terms of the MIT license.
*/

#include "WiFiConnect.h"

WiFiConnect* WiFiConnect::_instance = 0;
WiFiConnect::WiFiConnect() {}
WiFiConnect* WiFiConnect::Instance(String _ssid, String _password){
  if (_instance == 0)
    _instance = new WiFiConnect;
    _instance->ssid = _ssid;
    _instance->password = _password;
  return _instance;
}

uint8_t WiFiConnect::makeConnection() {

  static uint16_t attempt = 0;
  Serial.print("\n\nConnecting to ");
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println(ssid);


  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available on " + ssid + " and " +  password + "\r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("Got IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void WiFiConnect::Awaits(){
  uint32_t ts = millis();
  while (!connection_state)  {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = makeConnection();
      ts = millis();
    }
  }
}

bool WiFiConnect::Connect() {
  connection_state = makeConnection();
  if (!connection_state)  // if not connected to WIFI
    Awaits();             // constantly trying to connect
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  return true;
}

void  WiFiConnect::changeMyIP(IPAddress myIP, IPAddress gateway, IPAddress mask) {
  WiFi.config(myIP, gateway, mask);
  Serial.print("IP reset to: ");
  Serial.println(WiFi.localIP());
}


