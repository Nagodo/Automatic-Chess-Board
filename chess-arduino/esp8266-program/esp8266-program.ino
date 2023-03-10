#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* WIFI Information */
const char* ssid = "ChessNet";
const char* password = "abelort123"; 

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP blev startet");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  return HTMLHead() + HTMLBody();
}

String HTMLHead(){
  String head = "<!DOCTYPE html> <html>\n";
  head +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  head +="<title>ChessNetwork</title>\n";
  head +="</head>\n";

  return head;
}

String HTMLBody(){
  String body = "<body>\n";
  body +="<div id='root' class='content'></div>\n";
  body +="</body>\n";

  return body;
}
