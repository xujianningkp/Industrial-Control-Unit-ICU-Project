// pin mapping for SPI(2) on the Stellaris (also tiva??) using Rei Vilo's pinmap
// SDA  -  CS(2) -> PB_5 = pin 2 as an integer
// SCK  -  SCK(2) -> PB_4
// Mosi -  MOSI(2) -> PB_7
// Miso -  MISO(2) -> PB_6
// IRQ  - Not connected
// GND  - GND 
// RST  - reset -> PF_0
// VCC  - +3.3V = pin 1

#include <Mfrc522.h>
#include <SPI.h>
#include <Ethernet.h>
#include <LCD.h>

String txData ="";

byte mac[]     = { 0x00, 0x1A, 0xB6, 0x02, 0xAE, 0x37 };
byte ip[]      = { 10,100,120,53 }; // Must be unique on local network
byte gateway[] = { 10,100,120,1 };   // I left these in for reference in case you need them
byte subnet[]  = { 255,255,255,0 };   // I left these in for reference in case you need them
IPAddress server(10,100,120,171);   //the server we send the data to
int statusConfig = 0;
EthernetClient client;

int chipSelectPin1 = PA_4;
int chipSelectPin2 = PE_0;
int chipSelectPin3 = PE_1;
int chipSelectPin4 = PE_2;
int NRSTPD1 = PA_5;
int NRSTPD2 = PD_0;
int NRSTPD3 = PN_2;
int NRSTPD4 = PN_3;

int LED1 = PG_0;
int LED2 = PF_3;
int LED3 = PF_2;
int LED4 = PF_1;
int LED5 = PP_5;

int counter = 0;

unsigned char serNum[5];

String cardID1 = "1";
String location1 = "";
String last_cardID1 = "2";
boolean same_cardID1 = true;
boolean empty_cardID1 = true;

String cardID2 = "1";
String location2 = "";
String last_cardID2 = "2";
boolean same_cardID2 = true;
boolean empty_cardID2 = true;

String cardID3 = "1";
String location3 = "";
String last_cardID3 = "2";
boolean same_cardID3 = true;
boolean empty_cardID3 = true;

String cardID4 = "1";
String location4 = "";
String last_cardID4 = "2";
boolean same_cardID4 = true;
boolean empty_cardID4 = true;

void setup(){
  
  Serial.begin(115200);
  LCD.init(PP_4, PQ_0, PP_1, PP_0, PC_7, PC_6);
  LCD.print("ICU RFID TRACKER",1,1);
  LCD.print(" Connecting.... ",2,1);
  Ethernet.begin(0); //use default setting
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println();
  delay(1000);
  SPI.setModule(1); // using SPI module 2...

  pinMode(chipSelectPin1, OUTPUT); //moved this here from Mfrc522.cpp
  pinMode(chipSelectPin2, OUTPUT);
  pinMode(chipSelectPin3, OUTPUT);
  pinMode(chipSelectPin4, OUTPUT);

  pinMode(NRSTPD1, OUTPUT); //moved this here from Mfrc522.cpp
  pinMode(NRSTPD2, OUTPUT);
  pinMode(NRSTPD3, OUTPUT);
  pinMode(NRSTPD4, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  
  LCD.print("  System ready  ",2,1);
  digitalWrite(LED1, HIGH); delay(150); digitalWrite(LED2, HIGH); delay(150); digitalWrite(LED3, HIGH); delay(150); digitalWrite(LED4, HIGH); delay(150); digitalWrite(LED5, HIGH); delay(150);
  digitalWrite(LED5, LOW); delay(150); digitalWrite(LED4, LOW); delay(150); digitalWrite(LED3, LOW); delay(150); digitalWrite(LED2, LOW); delay(150); digitalWrite(LED1, LOW); delay(150);
  LCD.print("1:  2:  3:  4:  ",2,1);	 
}



void loop()
{
  for (int x=1; x<5; x++){
    switch(x){
      case 1:
        digitalWrite(chipSelectPin1, LOW);
        digitalWrite(chipSelectPin2, HIGH);
        digitalWrite(chipSelectPin3, HIGH);
        digitalWrite(chipSelectPin4, HIGH);
        digitalWrite(NRSTPD1, HIGH);
        digitalWrite(NRSTPD2, LOW);
        digitalWrite(NRSTPD3, LOW);
        digitalWrite(NRSTPD4, LOW);
        delay(100);
        getRFID(PA_4, PA_5, 1, "A", 1, 1, 1); // (chipSelectPin, NRSTPD, case, Section, Station, Rack, Shelf)
        break;
      case 2:
        digitalWrite(chipSelectPin1, HIGH);
        digitalWrite(chipSelectPin2, LOW);
        digitalWrite(chipSelectPin3, HIGH);
        digitalWrite(chipSelectPin4, HIGH);
        digitalWrite(NRSTPD1, LOW);
        digitalWrite(NRSTPD2, HIGH);
        digitalWrite(NRSTPD3, LOW);
        digitalWrite(NRSTPD4, LOW);
        delay(100);
        getRFID(PE_0, PD_0, 2, "B", 1, 1, 2);
        break;
      case 3:
        digitalWrite(chipSelectPin1, HIGH);
        digitalWrite(chipSelectPin2, HIGH);
        digitalWrite(chipSelectPin3, LOW);
        digitalWrite(chipSelectPin4, HIGH);
        digitalWrite(NRSTPD1, LOW);
        digitalWrite(NRSTPD2, LOW);
        digitalWrite(NRSTPD3, HIGH);
        digitalWrite(NRSTPD4, LOW);
        delay(100);
        getRFID(PE_1, PN_2, 3, "C", 1, 1, 3);
        break;
      case 4:
        digitalWrite(chipSelectPin1, HIGH);
        digitalWrite(chipSelectPin2, HIGH);
        digitalWrite(chipSelectPin3, HIGH);
        digitalWrite(chipSelectPin4, LOW);
        digitalWrite(NRSTPD1, LOW);
        digitalWrite(NRSTPD2, LOW);
        digitalWrite(NRSTPD3, LOW);
        digitalWrite(NRSTPD4, HIGH);
        delay(100);
        getRFID(PE_2, PN_3, 4, "D", 1, 1, 4);
        break;
        
    }
    delay(10);
    
  }   
}



void getRFID(int chipSelectPin, int NRSTPD, int case_number, char Section[], int Station, int Rack, int Shelf) {
  
  Mfrc522 Mfrc522(chipSelectPin, NRSTPD);
  Mfrc522.Init();
  unsigned char status;
  unsigned char status1;
  unsigned char str[MAX_LEN];
  unsigned char RC_size;
  unsigned char blockAddr;
  String mynum = "";
  
  status1 = Mfrc522.Request(PICC_REQIDL, str);	
  status = Mfrc522.Anticoll(str);
  memcpy(serNum, str, 5);
  
  switch(case_number){
    
    //------------------------------------------------------------------------------------------------------------
    case 1:
    for (int check=0; check<100; check++){
      
      location1 = String(Section)+String(Station)+String(Rack)+String(Shelf);
      
      if (status == MI_OK){
        
        cardID1 = String(serNum[0])+String(serNum[1])+String(serNum[2])+String(serNum[3])+String(serNum[4]);
        
        if (cardID1 != last_cardID1){
        
          
        
          Serial.print(cardID1);
          Serial.print(", ");
          Serial.println(location1);
       
          //delay(1000);
          digitalWrite(LED1, HIGH);
          sendPHP(cardID1, "", location1);
          
          last_cardID1 = cardID1;
          cardID1 = "";
          same_cardID1 = true;
        }
        else if (cardID1 == last_cardID1 && same_cardID1 == true){
          Serial.println("Same card detected!");
          LCD.print("AT",2,3);
          same_cardID1 = false;
        }
       
        empty_cardID1 = true;
        break;
      }
      else if (status != MI_OK && empty_cardID1 == true){
        
         if (status != MI_OK && status1 != MI_OK){
           counter++;
         }
        if (counter == 100){
          digitalWrite(LED1, LOW);
          sendPHP(last_cardID1, "EMPTY", location1);
          Serial.println("1 Empty!");
          LCD.print("ET",2,3);
          cardID1 = "1";
          location1 = "";
          last_cardID1 = "2";
          empty_cardID1 = false;
          counter = 0;
          break;
        }  
        } 
        
      }
      counter = 0;
      Mfrc522.Halt();
      break;
   
   
   
   //------------------------------------------------------------------------------------------------------------
   case 2:
   for (int check=0; check<100; check++){
     
     location2 = String(Section)+String(Station)+String(Rack)+String(Shelf);
     
     if (status == MI_OK){
        
        cardID2 = String(serNum[0])+String(serNum[1])+String(serNum[2])+String(serNum[3])+String(serNum[4]);
        
        if (cardID2 != last_cardID2){
        
          
        
          Serial.print(cardID2);
          Serial.print(", ");
          Serial.println(location2);
       
          //delay(1000);
          digitalWrite(LED2, HIGH);
          sendPHP(cardID2, "", location2);
          
          last_cardID2 = cardID2;
          cardID2 = "";
          same_cardID2 = true;
        }
        else if (cardID2 == last_cardID2 && same_cardID2 == true){
          Serial.println("Same card detected!");
          LCD.print("AT",2,7);
          same_cardID2 = false;
        }
        empty_cardID2 = true;
        break;
      }
      else if (status != MI_OK && empty_cardID2 == true){
        
         if (status != MI_OK && status1 != MI_OK){
           counter++;
         }
        if (counter == 100){
          digitalWrite(LED2, LOW);
          sendPHP(last_cardID2, "EMPTY", location2);
          Serial.println("2 Empty!");
          LCD.print("ET",2,7);
          cardID2 = "1";
          location2 = "";
          last_cardID2 = "2";
          empty_cardID2 = false;
          counter = 0;
          break;
        }  
        }  
      }
      counter = 0;
      Mfrc522.Halt();
      break;
      
   //------------------------------------------------------------------------------------------------------------   
   case 3:
   for (int check=0; check<100; check++){
     
     location3 = String(Section)+String(Station)+String(Rack)+String(Shelf);
     
     if (status == MI_OK){
        
        cardID3 = String(serNum[0])+String(serNum[1])+String(serNum[2])+String(serNum[3])+String(serNum[4]);
        
        if (cardID3 != last_cardID3){
        
          
        
          Serial.print(cardID3);
          Serial.print(", ");
          Serial.println(location3);
       
          //delay(1000);
          digitalWrite(LED3, HIGH);
          sendPHP(cardID3, "", location3);
          
          last_cardID3 = cardID3;
          cardID3 = "";
          same_cardID3 = true;
          
        }
        else if (cardID3 == last_cardID3 && same_cardID3 == true){
          Serial.println("Same card detected!");
          LCD.print("AT",2,11);
          same_cardID3 = false;
          
        }
        
        empty_cardID3 = true;
        break;
      }
      
      else if (status != MI_OK && empty_cardID3 == true){
        
         if (status != MI_OK && status1 != MI_OK){
           counter++;
         }
        if (counter == 100){
          digitalWrite(LED3, LOW);
          sendPHP(last_cardID3, "EMPTY", location3);
          Serial.println("3 Empty!");
          LCD.print("ET",2,11);
          cardID3 = "1";
          location3 = "";
          last_cardID3 = "2";
          empty_cardID3 = false;
          counter = 0;
          break;
        }  
        
        } 
      }
      counter = 0;
      Mfrc522.Halt();
      break;
    
    
    //------------------------------------------------------------------------------------------------------------   
   case 4:
   for (int check=0; check<100; check++){
     
     location4 = String(Section)+String(Station)+String(Rack)+String(Shelf);
     
     if (status == MI_OK){
        
        cardID4 = String(serNum[0])+String(serNum[1])+String(serNum[2])+String(serNum[3])+String(serNum[4]);
        
        if (cardID4 != last_cardID4){
        
          
        
          Serial.print(cardID4);
          Serial.print(", ");
          Serial.println(location4);
       
          //delay(1000);
          digitalWrite(LED4, HIGH);
          sendPHP(cardID4, "", location4);
          
          last_cardID4 = cardID4;
          cardID4 = "";
          same_cardID4 = true;
          
        }
        else if (cardID4 == last_cardID4 && same_cardID4 == true){
          Serial.println("Same card detected!");
          LCD.print("AT",2,15);
          same_cardID4 = false;
          
        }
        
        empty_cardID4 = true;
        break;
      }
      
      else if (status != MI_OK && empty_cardID4 == true){
        
         if (status != MI_OK && status1 != MI_OK){
           counter++;
         }
        if (counter == 100){
          digitalWrite(LED4, LOW);
          sendPHP(last_cardID4, "EMPTY", location4);
          Serial.println("4 Empty!");
          LCD.print("ET",2,15);
          cardID4 = "1";
          location4 = "";
          last_cardID4 = "2";
          empty_cardID4 = false;
          counter = 0;
          break;
        }  
        
        } 
      }
      counter = 0;
      Mfrc522.Halt();
      break;
  }
}





void sendPHP(String cardID, String status1, String location){
  
  digitalWrite(LED5, HIGH);
  
  txData = "RFID=" + String(cardID) + "&STATUS=" + String(status1) + "&LOCATION=" + String(location);
  
  if (client.connect(server,80)){
    
    Serial.println("Connected to yourwebsite..."); 

    client.print("POST /submit.php HTTP/1.1\n"); //php file directory in your server
    client.print("Host: 10.100.120.171\n");   //change it to your host
    client.println("User-Agent: energia-ethernet"); 
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(txData.length());    
    client.print("\n\n");
    client.print(txData);    // after all of the required, we send the data
    client.stop();
    Serial.println(txData);
    txData = "";
    digitalWrite(LED5, LOW);
  }
  else{
    Serial.println("Connection Failed."); // Again the Serial is for feedback.   
    Serial.println();
//    client.stop();
//    delay(1000);
//    client.connect(server,80);
//    delay(4000);
  }
  return;
}

