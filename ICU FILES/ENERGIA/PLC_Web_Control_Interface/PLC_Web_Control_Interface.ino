
#include "Ethernet.h"
#include "LCD.h"

#define GREENLED     PG_0
#define YELLOWLED    PF_3
#define REDLED1      PF_2
#define REDLED2      PF_1
#define BLUELED      PP_5

#define BUTTON1      PQ_1
#define BUTTON2      PP_3
#define BUTTON3      PQ_3
#define BUTTON4      PQ_2

#define OUT1         PK_7
#define OUT2         PK_6
#define OUT3         PH_1
#define OUT4         PH_0
#define OUT5         PM_2
#define OUT6         PM_1

#define IN1          PM_0
#define IN2          PK_5
#define IN3          PK_4
#define IN4          PG_1

#define RELAY1       PL_3
#define RELAY2       PL_2
#define SSR          PP_2

void printConfig();
void printEthernetData();

EthernetServer server(80);
int statusConfig = 0;

void setup() {
  Serial.begin(115200);
  LCD.init(PP_4, PQ_0, PP_1, PP_0, PC_7, PC_6);  
  LCD.print("ICU Control Unit",1,1);
  LCD.print(" Connecting.....",2,1);
  
  pinMode(GREENLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(REDLED1, OUTPUT);
  pinMode(REDLED2, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  pinMode(OUT5, OUTPUT);
  pinMode(OUT6, OUTPUT);
  
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
  pinMode(IN3, INPUT);
  pinMode(IN4, INPUT);
  
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(SSR, OUTPUT);
  
  Serial.println("Connecting to Ethernet....");  
  IPAddress ip = IPAddress(146,252,242,129);
  IPAddress dns = IPAddress(146,252,242,12);
  IPAddress gw = IPAddress(146,252,242,254);
  IPAddress mask = IPAddress(255,255,255,0);

  Ethernet.begin(0);
//  Ethernet.begin(0, ip, dns, gw);

  server.begin();

  printEthernetData();
  delay(1000);
  LCD.print("System is ready.",2,1);
}

EthernetClient client;

void loop() {
  client = server.available();
  
  if (client) {                             // if you get a client,
    Serial.print("new client on port ");           // print a message out the serial port
    Serial.println(client.port());
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected

      if (client.available()) {             // if there's bytes to read from the client,    
        char c = client.read();             // read a byte, then
                                            // This lockup is because the recv function is blocking.
        Serial.print(c);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {  
            break;         
          } 
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }     
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        if (currentLine.endsWith("GET / ")) {
          printConfig();
        }
       
            
        if (currentLine.endsWith("GET /GREEN_LED_H")) {digitalWrite(GREENLED, HIGH);printConfig();}       
        if (currentLine.endsWith("GET /GREEN_LED_L")) {digitalWrite(GREENLED, LOW);printConfig();}
        if (currentLine.endsWith("GET /YELLOW_LED_H")) {digitalWrite(YELLOWLED, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /YELLOW_LED_L")) {digitalWrite(YELLOWLED, LOW);printConfig();} 
        if (currentLine.endsWith("GET /RED_LED1_H")) {digitalWrite(REDLED1, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /RED_LED1_L")) {digitalWrite(REDLED1, LOW);printConfig();} 
        if (currentLine.endsWith("GET /RED_LED2_H")) {digitalWrite(REDLED2, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /RED_LED2_L")) {digitalWrite(REDLED2, LOW);printConfig();}
        if (currentLine.endsWith("GET /BLUE_LED_H")) {digitalWrite(BLUELED, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /BLUE_LED_L")) {digitalWrite(BLUELED, LOW);printConfig();}
        
        if (currentLine.endsWith("GET /OUT1_H")) {digitalWrite(OUT1, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT1_L")) {digitalWrite(OUT1, LOW);printConfig();}
        if (currentLine.endsWith("GET /OUT2_H")) {digitalWrite(OUT2, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT2_L")) {digitalWrite(OUT2, LOW);printConfig();}
        if (currentLine.endsWith("GET /OUT3_H")) {digitalWrite(OUT3, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT3_L")) {digitalWrite(OUT3, LOW);printConfig();}
        if (currentLine.endsWith("GET /OUT4_H")) {digitalWrite(OUT4, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT4_L")) {digitalWrite(OUT4, LOW);printConfig();}
        if (currentLine.endsWith("GET /OUT5_H")) {digitalWrite(OUT5, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT5_L")) {digitalWrite(OUT5, LOW);printConfig();}
        if (currentLine.endsWith("GET /OUT6_H")) {digitalWrite(OUT6, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /OUT6_L")) {digitalWrite(OUT6, LOW);printConfig();}
        
        if (currentLine.endsWith("GET /RELAY1_H")) {digitalWrite(RELAY1, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /RELAY1_L")) {digitalWrite(RELAY1, LOW);printConfig();}
        if (currentLine.endsWith("GET /RELAY2_H")) {digitalWrite(RELAY2, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /RELAY2_L")) {digitalWrite(RELAY2, LOW);printConfig();}
        if (currentLine.endsWith("GET /SSR_H")) {digitalWrite(SSR, HIGH);printConfig();}         
        if (currentLine.endsWith("GET /SSR_L")) {digitalWrite(SSR, LOW);printConfig();}
        
        if (currentLine.endsWith("GET /LCD_H")){
          LCD.print("Hello World!    ",2,1);
          printConfig();
        }
        if (currentLine.endsWith("GET /LCD_L")){
          LCD.print("Bye Bye World!  ",2,1);
          printConfig();
        }
         
      }
    }
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
  }
}


void printConfig()
{
    
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><head><title>PLC | Web</title></head><body align=center>");
  client.println("<h1 align=center><font color=\"red\">PLC Web Control Interface</font></h1>");
  
  client.print("<font color='green'>GREEN_LED</font> <button onclick=\"location.href='/GREEN_LED_H'\">HIGH</button>");
  client.println(" <button onclick=\"location.href='/GREEN_LED_L'\">LOW</button><br>");
  client.print("<font color='yellow'>YELLOW_LED</font> <button onclick=\"location.href='/YELLOW_LED_H'\">HIGH</button>");
  client.println(" <button onclick=\"location.href='/YELLOW_LED_L'\">LOW</button><br>");
  client.print("<font color='red'>RED_LED1</font> <button onclick=\"location.href='/RED_LED1_H'\">HIGH</button>");
  client.println(" <button onclick=\"location.href='/RED_LED1_L'\">LOW</button><br>");
  client.print("<font color='red'>RED_LED2</font> <button onclick=\"location.href='/RED_LED2_H'\">HIGH</button>");
  client.println(" <button onclick=\"location.href='/RED_LED2_L'\">LOW</button><br>");
  client.print("<font color='blue'>BLUE_LED</font> <button onclick=\"location.href='/BLUE_LED_H'\">HIGH</button>");
  client.println(" <button onclick=\"location.href='/BLUE_LED_L'\">LOW</button><br><br>");
  

  client.println("BUTTON1 ");
  if(digitalRead(BUTTON1))client.print("is HIGH<br>");
  else client.print("is LOW<br>");
  client.println("BUTTON2 ");
  if(digitalRead(BUTTON2))client.print("is HIGH<br>");
  else client.print("is LOW<br>"); 
  client.println("BUTTON3 ");
  if(digitalRead(BUTTON3))client.print("is HIGH<br>");
  else client.print("is LOW<br>");
  client.println("BUTTON4 ");
  if(digitalRead(BUTTON4))client.print("is HIGH<br><br>");
  else client.print("is LOW<br><br>");
   
  
  client.print("<font color='blue'>OUTPUT_1</font> <button onclick=\"location.href='/OUT1_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT1_L'\">OFF</button><br>");
  client.print("<font color='blue'>OUTPUT_2</font> <button onclick=\"location.href='/OUT2_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT2_L'\">OFF</button><br>");
  client.print("<font color='blue'>OUTPUT_3</font> <button onclick=\"location.href='/OUT3_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT3_L'\">OFF</button><br>");
  client.print("<font color='blue'>OUTPUT_4</font> <button onclick=\"location.href='/OUT4_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT4_L'\">OFF</button><br>");
  client.print("<font color='blue'>OUTPUT_5</font> <button onclick=\"location.href='/OUT5_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT5_L'\">OFF</button><br>");
  client.print("<font color='blue'>OUTPUT_6</font> <button onclick=\"location.href='/OUT6_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/OUT6_L'\">OFF</button><br><br>");
  
  client.println("INPUT1 ");
  if(digitalRead(IN1))client.print("is LOW<br>");
  else client.print("is HIGH<br>");
  client.println("INPUT2 ");
  if(digitalRead(IN2))client.print("is LOW<br>");
  else client.print("is HIGH<br>");
  client.println("INPUT3 ");
  if(digitalRead(IN3))client.print("is LOW<br>");
  else client.print("is HIGH<br>");
  client.println("INPUT4 ");
  if(digitalRead(IN4))client.print("is LOW<br><br>");
  else client.print("is HIGH<br><br>");
  
  client.print("<font color='blue'>RELAY1</font> <button onclick=\"location.href='/RELAY1_H'\">POS1</button>");
  client.println(" <button onclick=\"location.href='/RELAY1_L'\">POS2</button><br>");
  client.print("<font color='blue'>RELAY2</font> <button onclick=\"location.href='/RELAY2_H'\">POS1</button>");
  client.println(" <button onclick=\"location.href='/RELAY2_L'\">POS2</button><br>");
  client.print("<font color='blue'>SSR</font> <button onclick=\"location.href='/SSR_H'\">ON</button>");
  client.println(" <button onclick=\"location.href='/SSR_L'\">OFF</button><br><br>");
  
  client.print("<font color='red'>LCD Display</font> <button onclick=\"location.href='/LCD_H'\">Becky</button>");
  client.println(" <button onclick=\"location.href='/LCD_L'\">Bacon</button><br><br>");
  
  client.println("</body></html>");
  // The HTTP response ends with another blank line:
  client.println();
  // break out of the while loop:
}


void printEthernetData() {
  // print your IP address:
  Serial.println();
  Serial.println("IP Address Information:");  
  IPAddress ip = Ethernet.localIP();
    Serial.print("IP Address:\t");
  Serial.println(ip);
  
  // print your MAC address:
  
  IPAddress subnet = Ethernet.subnetMask();
  Serial.print("NetMask:\t");
  Serial.println(subnet);

  // print your gateway address:
  IPAddress gateway = Ethernet.gatewayIP();
  Serial.print("Gateway:\t");
  Serial.println(gateway);

  // print your gateway address:
  IPAddress dns = Ethernet.dnsServerIP();
  Serial.print("DNS:\t\t");
  Serial.println(dns);

}
