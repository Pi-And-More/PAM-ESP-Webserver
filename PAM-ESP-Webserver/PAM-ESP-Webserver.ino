////////////////////////////////////////////////////////////////////////////////////
//
//                               PI and more
//                        ESP8266 basic webserver
//
// https://piandmore.wordpress.com/2016/10/05/esp-webserver-with-arduino-ide/
//
////////////////////////////////////////////////////////////////////////////////////
//
// Include the ESP8266WiFI library
//
#include <ESP8266WiFi.h>

//
// Fill in your own SSID and password
//
const char* ssid = "YourSSID";
const char* password = "YourPassword";

//
// Initialize the WiFiServer
//
WiFiServer server(80);

void setup() {
  //
  // Initialize serial output
  //
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //
  // Start the wifi and wait for a connection
  //
  WiFi.begin(ssid,password);
  while (WiFi.status()!=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //
  // Start the webserver
  //
  server.begin();
  delay(500);
  //
  // Show the IP of the server in serial monitor
  //
  Serial.println("Web server running. The IP is:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    //
    // A web client is asking for a page
    //
    Serial.println("New client");
    boolean blank_line = true;
    while (client.connected()) {
      //
      // We need to read the request of the client
      //
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && blank_line) {
          //
          // We have read the request of the client. Now send the page
          //
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>Test</h1></body></html>");  
          break;
        }
        if (c == '\n') {
          blank_line = true;
        } else if (c!= '\r') {
          blank_line = false;
        }
      }
    }  
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}

