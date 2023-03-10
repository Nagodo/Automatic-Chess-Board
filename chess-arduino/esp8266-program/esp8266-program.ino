#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* WIFI Information */
const char* ssid = "ChessNet";
const char* password = "abelort123"; 

char[] chessposition = [
    ["r","n","b","q","k","b","n","r"],
    ["p","p","p","p","p","p","p","p"],
    ["/","/","/","/","/","/","/","/"],
    ["/","/","/","/","/","/","/","/"],
    ["/","/","/","/","/","/","/","/"],
    ["/","/","/","/","/","/","/","/"],
    ["P","P","P","P","P","P","P","P"],
    ["R","N","B","Q","K","B","N","R"]
   
]

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
  
    server.send(200, "text/html", SendHTML()); 
}

void handle_NotFound(){
    server.send(404, "text/plain", "Ikke fundet");
}

void update_position(){
    String pos = "";
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pos += chessposition[i][j];
        }
    }

    server.send(200, "text/html", SendHTML(pos));
}

String SendHTML(String pos){
    return HTMLHead() + HTMLBody(pos);
}

String HTMLHead(){
    String head = "<!DOCTYPE html> <html>\n";
    head +="<head>\n";
    head +="<title>ChessNetwork</title>\n";
    head +="</head>\n";

    return head;
}

String HTMLBody(String pos){
    String body = "<body>\n";
    body +="<div id='root' class='content'><p id='position'>" + pos + "</p></div>\n";
    body +="</body>\n";
    body +="</html>\n";

    return body;
}
