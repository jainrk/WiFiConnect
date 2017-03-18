/*  
	March 20 2017 Raj Jain
	The WiFiConnect class is created to have one class do the work to connect an ESP8266 to a router.
	It removes the spaghetti of code from you main sketch and encapsulates it into reusable class. 
	Parts of this code have come from various sources floating around in various resources
	This project is licensed under the terms of the MIT license.
*/

#ifndef __WIFICONNECT__
#define __WIFICONNECT__
#include <ESP8266WiFi.h>

class WiFiConnect {
  protected:
    uint8_t connection_state = 0;                    // Connected to WIFI or not
    uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
    WiFiConnect();
    void Awaits();
    uint8_t makeConnection();
  private:
    static WiFiConnect* _instance;
  public:
    String ssid;                     
    String password;            

    static WiFiConnect* Instance(String _ssid, String _password);
    bool Connect();
    void changeMyIP(IPAddress myIP, IPAddress gateway, IPAddress mask);
};
#endif // __WIFICONNECT__
