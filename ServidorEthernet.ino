#include <SPI.h>
#include <Ethernet.h>

int rele1 = 2;
int rele2 = 3;
int rele3 = 4;
int rele4 = 5;
String readString;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 0, 0, 170);

EthernetServer server(7778);

void setup() {
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  
  Ethernet.begin(mac, ip);
  Ethernet.setRetransmissionTimeout(50);
  server.begin();
}


void loop() {
  EthernetClient client = server.available();
  if(!client){
    return;
  }
  while(!client.available()){
    delay(1);
  }
  client.setConnectionTimeout(500);
  char c = client.read();
    if (readString.length() < 100){
        readString += c;
    }  
    if (c == '\n') {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta charset=\"utf-8\">");
  client.println("<title>Julie</title>");
  client.println("<style rel='stylesheet' type='text/css'>body{background-color:gray;}</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("</body>");
  client.println("</html>");
  delay(1);
  client.stop();

  if (readString.indexOf("rele1") > 0){
  int valorAtual1 = digitalRead(rele1);
  if (valorAtual1 == 0){digitalWrite(rele1, HIGH);}else{digitalWrite(rele1, LOW);}
  }
  if (readString.indexOf("rele2") > 0){
  int valorAtual1 = digitalRead(rele2);
  if (valorAtual1 == 0){digitalWrite(rele2, HIGH);}else{digitalWrite(rele2, LOW);}
  }
  if (readString.indexOf("rele3") > 0){
  int valorAtual1 = digitalRead(rele3);
  if (valorAtual1 == 0){digitalWrite(rele3, HIGH);}else{digitalWrite(rele3, LOW);}
  }
  if (readString.indexOf("rele4") > 0){
  int valorAtual1 = digitalRead(rele4);
  if (valorAtual1 == 0){digitalWrite(rele4, HIGH);}else{digitalWrite(rele4, LOW);}
  }
  readString="";
}
}
