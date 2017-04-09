/*
  Web  Server
 
 A simple web server that shows the value of the analog and digital input pins
 using a WiFi BoosterPack.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Circuit:
 * WiFi BoosterPack

 Created: October 16, 2013 by Robert Wessels (http://energia.nu)
 Derived from example Sketch by Hans Scharler (http://www.iamshadowlord.com)
 
 */
 
#include "Ethernet.h"
#include <Servo.h>
#include <LCD.h>

// Prototypes
void printConfig();
void printEthernetData();
void printIndex();
void printHelp();

EthernetServer server(80);
Servo myservo;  // create servo object to control a servo 
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5; 
Servo myservo6;
Servo myservo7;
Servo myservo8;

int LED1 = PG_0;
int LED2 = PF_3;
int LED3 = PF_2;
int LED4 = PF_1;
int LED5 = PP_5;

//int potpin = PE_4;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
int statusConfig = 0;
int counter1 = 30;
int counter2 = 20;
int counter3 = 50;
int counter4 = 15;
int counter5 = 100;
int counter6 = 15;
int counter7 = 85;
int counter8 = 45;
int x = 5;
int pos = 0;
int uppermargin = 160;
int lowermargin = 20;

void setup() {
  //delay(2000);
  Serial.begin(115200);    
  // delay(2000);
  LCD.init(PP_4, PQ_0, PP_1, PP_0, PC_7, PC_6);
  LCD.print("ICU Control Unit");
  LCD.print("  Connecting..  ",2,1);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
//  pinMode(PUSH1, INPUT_PULLUP); // released = HIGH, pressed = LOW
//  pinMode(PUSH2, INPUT_PULLUP);
  myservo.attach(PL_4);
  myservo2.attach(PL_5);
  myservo3.attach(PM_5);
  myservo4.attach(PM_4);// attaches the servo on Port F, pin 1 (Red LED pin) to the servo object 
  myservo5.attach(PA_6);
  myservo6.attach(PD_7);
  myservo7.attach(PD_3);
  myservo8.attach(PB_2);
  
  myservo.write(counter1);
  myservo2.write(counter2);
  myservo3.write(counter3);
  myservo4.write(counter4);
  myservo5.write(counter5);
  myservo6.write(counter6);
  myservo7.write(counter7);
  myservo8.write(counter8);
  
  Serial.println("Connecting to Ethernet....");  
  IPAddress ip = IPAddress(192,168,0,101);
  IPAddress dns = IPAddress(192,168,0,1);
  IPAddress gw = IPAddress(192,168,0,1);
  IPAddress mask = IPAddress(255,255,255,0);

   Ethernet.begin(0);
//     Ethernet.begin(0, ip, dns, gw);

  server.begin();

  printEthernetData();
  
  LCD.print(" System Ready!  ",2,1);
  digitalWrite(LED1, HIGH); delay(150); digitalWrite(LED2, HIGH); delay(150); digitalWrite(LED3, HIGH); delay(150); digitalWrite(LED4, HIGH); delay(150); digitalWrite(LED5, HIGH); delay(150);
  digitalWrite(LED5, LOW); delay(150); digitalWrite(LED4, LOW); delay(150); digitalWrite(LED3, LOW); delay(150); digitalWrite(LED2, LOW); delay(150); digitalWrite(LED1, LOW); delay(150);
}

EthernetClient client;

void loop() {
  client = server.available();
  
    
//  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 4095)   
//  val = map(val, 0, 100, 0, 10);     // scale it to use it with the servo (value between 0 and 180) 
//  myservo.write(val);    // sets the servo position according to the scaled value 

//  delay(15);                           // waits for the servo to get there 

  
  if (client) {                             // if you get a client,
    Serial.print("new client on port ");           // print a message out the serial port
    Serial.println(client.port());
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
    

      if (client.available()) {        // if there's bytes to read from the client,
  
        digitalWrite(LED1, HIGH);
            
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

        // Check to see if the client request was "GET /H" or "GET /L":
//        if (currentLine.endsWith("GET /RED_LED_H")) {digitalWrite(D1_LED, HIGH);printConfig();}         
//        if (currentLine.endsWith("GET /RED_LED_L")) {digitalWrite(D1_LED, LOW);printConfig();}     
//        if (currentLine.endsWith("GET /GREEN_LED_H")) {digitalWrite(D2_LED, HIGH);printConfig();}       
//        if (currentLine.endsWith("GET /GREEN_LED_L")) {digitalWrite(D2_LED, LOW);printConfig();}
       
       // Increment Control
       /////////////////////////////////////////////////////////////////
       if (currentLine.endsWith("GET /Inc5")){
          x = 5;
          uppermargin = 165-x;
          lowermargin = 15+x;
          printConfig();
       }
       if (currentLine.endsWith("GET /Inc10")){
          x = 10;
          uppermargin = 165-x;
          lowermargin = 15+x;
          printConfig();
       }
       if (currentLine.endsWith("GET /Inc15")){
          x = 15;
          uppermargin = 165-x;
          lowermargin = 15+x;
          printConfig();
       }
       
       
        // Servo 1
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /123"))
        {
          pos = counter1 + x;
          if (counter1 > uppermargin)
           {
             for(counter1; counter1 < 165; counter1 += 1)
             {                                           // in steps of 1 degree 
               myservo.write(counter1);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter1; counter1 < pos; counter1 += 1) 
             {                                            // in steps of 1 degree 
               myservo.write(counter1);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /456"))
        {
           pos = counter1 - x;
           if (counter1 < lowermargin)
           {
             for(counter1; counter1 > 15; counter1 -= 1) 
             {                                            // in steps of 1 degree 
               myservo.write(counter1);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter1; counter1 > pos; counter1 -= 1)
             {                                            // in steps of 1 degree 
               myservo.write(counter1);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 2
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /987"))
        {
          pos = counter2 + x;
          if (counter2 > uppermargin)
           {
             for(counter2; counter2 < 165; counter2 += 1)
             {                                           // in steps of 1 degree 
               myservo2.write(counter2);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter2; counter2 < pos; counter2 += 1) 
             {                                            // in steps of 1 degree 
               myservo2.write(counter2);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /789"))
        {
           pos = counter2 - x;
           if (counter2 < lowermargin)
           {
             for(counter2; counter2 > 15; counter2 -= 1) 
             {                                            // in steps of 1 degree 
               myservo2.write(counter2);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter2; counter2 > pos; counter2 -= 1)
             {                                            // in steps of 1 degree 
               myservo2.write(counter2);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 3
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /654"))
        {
          pos = counter3 + x;
          if (counter3 > uppermargin)
           {
             for(counter3; counter3 < 165; counter3 += 1)
             {                                           // in steps of 1 degree 
               myservo3.write(counter3);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter3; counter3 < pos; counter3 += 1) 
             {                                            // in steps of 1 degree 
               myservo3.write(counter3);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /321"))
        {
           pos = counter3 - x;
           if (counter3 < lowermargin)
           {
             for(counter3; counter3 > 15; counter3 -= 1) 
             {                                            // in steps of 1 degree 
               myservo3.write(counter3);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter3; counter3 > pos; counter3 -= 1)
             {                                            // in steps of 1 degree 
               myservo3.write(counter3);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 4
        /////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /147"))
        {
          pos = counter4 + x;
          if (counter4 > uppermargin)
           {
             for(counter4; counter4 < 165; counter4 += 1)
             {                                           // in steps of 1 degree 
               myservo4.write(counter4);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter4; counter4 < pos; counter4 += 1) 
             {                                            // in steps of 1 degree 
               myservo4.write(counter4);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /741"))
        {
           pos = counter4 - x;
           if (counter4 < lowermargin)
           {
             for(counter4; counter4 > 15; counter4 -= 1) 
             {                                            // in steps of 1 degree 
               myservo4.write(counter4);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter4; counter4 > pos; counter4 -= 1)
             {                                            // in steps of 1 degree 
               myservo4.write(counter4);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }

        // Servo 5
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /ABC"))
        {
          pos = counter5 + x;
          if (counter5 > uppermargin)
           {
             for(counter5; counter5 < 165; counter5 += 1)
             {                                           // in steps of 1 degree 
               myservo5.write(counter5);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter5; counter5 < pos; counter5 += 1) 
             {                                            // in steps of 1 degree 
               myservo5.write(counter5);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /CBA"))
        {
           pos = counter5 - x;
           if (counter5 < lowermargin)
           {
             for(counter5; counter5 > 15; counter5 -= 1) 
             {                                            // in steps of 1 degree 
               myservo5.write(counter5);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter5; counter5 > pos; counter5 -= 1)
             {                                            // in steps of 1 degree 
               myservo5.write(counter5);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 6
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /DEF"))
        {
          pos = counter6 + x;
          if (counter6 > uppermargin)
           {
             for(counter6; counter6 < 165; counter6 += 1)
             {                                           // in steps of 1 degree 
               myservo6.write(counter6);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter6; counter6 < pos; counter6 += 1) 
             {                                            // in steps of 1 degree 
               myservo6.write(counter6);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /FED"))
        {
           pos = counter6 - x;
           if (counter6 < lowermargin)
           {
             for(counter6; counter6 > 15; counter6 -= 1) 
             {                                            // in steps of 1 degree 
               myservo6.write(counter6);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter6; counter6 > pos; counter6 -= 1)
             {                                            // in steps of 1 degree 
               myservo6.write(counter6);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 7
        ////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /GHI"))
        {
          pos = counter7 + x;
          if (counter7 > uppermargin)
           {
             for(counter7; counter7 < 165; counter7 += 1)
             {                                           // in steps of 1 degree 
               myservo7.write(counter7);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter7; counter7 < pos; counter7 += 1) 
             {                                            // in steps of 1 degree 
               myservo7.write(counter7);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /IHG"))
        {
           pos = counter7 - x;
           if (counter7 < lowermargin)
           {
             for(counter7; counter7 > 15; counter7 -= 1) 
             {                                            // in steps of 1 degree 
               myservo7.write(counter7);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter7; counter7 > pos; counter7 -= 1)
             {                                            // in steps of 1 degree 
               myservo7.write(counter7);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        // Servo 8
        /////////////////////////////////////////////////////////////////
        if (currentLine.endsWith("GET /JKL"))
        {
          pos = counter8 + x;
          if (counter8 > uppermargin)
           {
             for(counter8; counter8 < 165; counter8 += 1)
             {                                           // in steps of 1 degree 
               myservo8.write(counter8);                  // tell servo to go to position in variable 'pos' 
               delay(25);                                // waits 15ms for the servo to reach the position
             }
           }  
           else
           {
             for(counter8; counter8 < pos; counter8 += 1) 
             {                                            // in steps of 1 degree 
               myservo8.write(counter8);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        if (currentLine.endsWith("GET /LKJ"))
        {
           pos = counter8 - x;
           if (counter8 < lowermargin)
           {
             for(counter8; counter8 > 15; counter8 -= 1) 
             {                                            // in steps of 1 degree 
               myservo8.write(counter8);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             } 
           }  
           else
           {
             for(counter8; counter8 > pos; counter8 -= 1)
             {                                            // in steps of 1 degree 
               myservo8.write(counter8);                   // tell servo to go to position in variable 'pos' 
               delay(25);                                 // waits 15ms for the servo to reach the position 
             }
           }
           printConfig();
        }
        
        
      }
    }
    // close the connection:
    client.stop();
    digitalWrite(LED1, LOW);
    LCD.clear();
    LCD.print(counter1,1,1);
    LCD.print(counter2,1,5);
    LCD.print(counter3,1,9);
    LCD.print(counter4,1,13);
    LCD.print(counter5,2,1);
    LCD.print(counter6,2,5);
    LCD.print(counter7,2,9);
    LCD.print(counter8,2,13);
    //Serial.println("client disonnected");
  }
}


void printConfig()
{
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:    
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println("<html><head><title>Stepper Motor Control</title></head><body align=center>");
  client.println("<h1 align=center><font color=\"red\">PLC Robotic Arm Control</font></h1>");
  
  
  // the content of the HTTP response follows the header:
  // Added: nicer buttons
//  client.print("<font color='green'>GREEN_LED</font> <button onclick=\"location.href='/GREEN_LED_H'\">HIGH</button>");
//  client.println(" <button onclick=\"location.href='/GREEN_LED_L'\">LOW</button><br>");
//  client.print("<font color='red'>RED_LED</font> <button onclick=\"location.href='/RED_LED_H'\">HIGH</button>");
//  client.println(" <button onclick=\"location.href='/RED_LED_L'\">LOW</button><br><br>");

  //client.print("<font color='green'>Increment by</font>");
//  client.println("<form action.asp/""/<font color='green'>Increment by: </font>");
//  client.println("<input type= \"radio\" name= \"inc\" value= \"5\">5  ");
//  client.println("<input type= \"radio\" name= \"inc\" value= \"10\">10  ");
//  client.println("<input type= \"radio\" name= \"inc\" value= \"15\">15 </form>");  
//  //client.print("<input type= \"submit\" value= \"Submit\"></form>");
//  client.println("<input type=\"button\" onclick=\"myFunction()\" value=\"Increment\"></form><br><br>");
//  client.println("<script>function myFunction(){var inc = document.forms[0].inc;var txt = /""/; var i;for(i = 0; i<inc.length; i++){if(inc[i].checked){txt = txt + inc[i].value + /" "/;}}}</script>");
//  
  client.print("<font color='black'>Increment degrees by: </font>");
  client.print("<button onclick=\"location.href='/Inc5'\"> 5 </button>");
  client.print("<button onclick=\"location.href='/Inc10'\"> 10 </button>");
  client.print("<button onclick=\"location.href='/Inc15'\"> 15 </button><br><br>");

  client.print("<font color='blue'>Move_Servo1</font> <button onclick=\"location.href='/123'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/456'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='green'>Move_Servo2</font> <button onclick=\"location.href='/987'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/789'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='blue'>Move_Servo3</font> <button onclick=\"location.href='/654'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/321'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='green'>Move_Servo4</font> <button onclick=\"location.href='/147'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/741'\">Counter-Clockwise</button><br>");

  client.print("<font color='blue'>Move_Servo5</font> <button onclick=\"location.href='/ABC'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/CBA'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='green'>Move_Servo6</font> <button onclick=\"location.href='/DEF'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/FED'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='blue'>Move_Servo7</font> <button onclick=\"location.href='/GHI'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/IHG'\">Counter-Clockwise</button><br>");
  
  client.print("<font color='green'>Move_Servo8</font> <button onclick=\"location.href='/JKL'\">Clockwise</button>");
  client.println("<button onclick=\"location.href='/LKJ'\">Counter-Clockwise</button><br>");


//  client.println("PUSH1 ");
//  if(digitalRead(PUSH1))client.print("is HIGH<br>");
//  else client.print("is LOW<br>");
//  client.println("PUSH2 ");
//  if(digitalRead(PUSH2))client.print("is HIGH<br>");
//  else client.print("is LOW<br>");  
  
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
