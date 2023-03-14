#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* WIFI Information */
const char* ssid = "ChessNet";
const char* password = "abelort123"; 

char chessposition[8][8] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
    {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

const int testBtn = 4;

int buttonState = 0;
int testMove = 0;

void setup() {
    pinMode(testBtn, INPUT);
  
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
    
    server.on("/", handle_OnConnect);

    server.on("/update", handle_update);

    server.on("/move", handle_move);
    
    server.onNotFound(handle_NotFound);
    
    server.begin();
    Serial.println("HTTP blev startet");

}
void loop() {
    server.handleClient();

    buttonState = digitalRead(testBtn);
 

    if (buttonState == HIGH) {
        if (testMove == 0) {
            
            Move("e2", "e4");
            testMove = 1;
        }
        
    } 
}

void handle_OnConnect() {
  
    server.send(200, "text/html", SendHTML(get_position_string())); 
}

void handle_NotFound(){
    server.send(404, "text/plain", "Ikke fundet");
}

void handle_update() {
    server.send(200, "text/plain", get_position_string());
}

void handle_move() {
  String from = server.arg("from");
      String to = server.arg("to");

    
    
      Move(from, to);
}

String get_position_string(){
  String pos = "";
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pos += chessposition[i][j];
        }
    }

   return pos;
}


int GetIndexFromLetter(char l) {
   int x;
    if (l == 'a') {
        x = 0;
    } else if (l == 'b') {
        x = 1;
    } else if (l == 'c') {
        x = 2;
    } else if (l == 'd') {
        x = 3;
    } else if (l == 'e') {
        x = 4;
    } else if (l == 'f') {
        x = 5;
    } else if (l == 'g') {
        x = 6;
    } else if (l == 'h') {
        x = 7;
    }

    
    return x;
}

int GetIndexFromNumber(char n) {
    int y;
    if (n == '1') {
        y = 7;
    } else if (n == '2') {
        y = 6;
    } else if (n == '3') {
        y = 5;
    } else if (n == '4') {
        y = 4;
    } else if (n == '5') {
        y = 3;
    } else if (n == '6') {
        y = 2;
    } else if (n == '7') {
        y = 1;
    } else if (n == '8') {
        y = 0;
    }

    
    return y;
}



void Move(String from, String to) {
  
    int x = GetIndexFromLetter(from[0]);
    int y = GetIndexFromNumber(from[1]);
    
    char current_piece = chessposition[y][x];

    chessposition[y][x] = 'e';

    int x_1 = GetIndexFromLetter(to[0]);
    int y_1 = GetIndexFromNumber(to[1]);
 

    chessposition[y_1][x_1] = current_piece;
    
    update_position();
}


void update_position(){
    server.send(200, "text/html", SendHTML(get_position_string()));
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
    body +="<div id='root' class='content'><p id='position'>" + pos + "</p><span id='content'> </span></div>\n";
    body +="</body>\n";
    body +="</html>\n";

    return body;
}
