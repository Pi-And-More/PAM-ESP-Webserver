#include <ESP8266WiFi.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status()!=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  delay(10000);
  Serial.println("Web server running. The IP is:");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && blank_line) {
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

