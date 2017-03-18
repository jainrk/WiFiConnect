/*  
	March 20 2017 Raj Jain
	The WiFiConnect class is created to have one class do the work to connect an ESP8266 to a router.
	It removes the spaghetti of code from you main sketch and encapsulates it into reusable class. 
	Parts of this code have come from various sources floating around in various resources
	This project is licensed under the terms of the MIT license.
*/

#include <WiFiConnect.h>

#define aSSID  "myUSERID"                     
#define aPASSWORD  "myPASSWD"            

const IPAddress ESP8266IP = IPAddress(192, 168, 2, 201);
const IPAddress GATEWAY = IPAddress(192, 168, 2, 1);
const IPAddress MASK = IPAddress(255, 255, 255, 0);

WiFiConnect* wifiCon = WiFiConnect::Instance(aSSID, aPASSWORD); 

void setup() {
  Serial.begin(115200);
  wifiCon->Connect();
  wifiCon->changeMyIP(ESP8266IP, GATEWAY, MASK);
}
void loop() {}
