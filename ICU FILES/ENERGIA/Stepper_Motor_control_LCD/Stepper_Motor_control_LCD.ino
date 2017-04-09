#include <LCD.h>

#define GREENLED     PG_0
#define YELLOWLED    PF_3
#define REDLED1      PF_2
#define REDLED2      PF_1
#define BLUELED      PP_5

#define BUTTON1      PQ_1
#define BUTTON2      PP_3
#define BUTTON3      PQ_3
#define BUTTON4      PQ_2

int BUTTON2_state = 0;
int BUTTON2_last = 0;

int BUTTON3_state = 0;
int BUTTON3_last = 0;

int BUTTON4_state = 0;
int BUTTON4_last = 0;

int steps = PB_2;
int dir = PB_3;

int Step = 10;
int Speed = 0;
int Speed_delay = 5;
int Dire = true;

void setup(){
  
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
  
  pinMode(GREENLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(REDLED1, OUTPUT);
  pinMode(REDLED2, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  
  LCD.init(PP_4, PQ_0, PP_1, PP_0, PC_7, PC_6);  
  LCD.print("ICU Control Unit",1,1);
  digitalWrite(GREENLED, HIGH); delay(200); digitalWrite(YELLOWLED, HIGH); delay(200); digitalWrite(REDLED1, HIGH); delay(200); digitalWrite(REDLED2, HIGH); delay(200);
  digitalWrite(REDLED2, LOW); delay(200); digitalWrite(REDLED1, LOW); delay(200); digitalWrite(YELLOWLED, LOW); delay(200); digitalWrite(GREENLED, LOW); delay(200);
  LCD.clear();
  LCD.print("STEP DIREC SPEED",1,1);
  LCD.print("10   CW    LOW  ",2,1);
  digitalWrite(BLUELED, HIGH);
  digitalWrite(GREENLED, HIGH);
}

void loop(){
  
  
  if (digitalRead(BUTTON1) == HIGH){
    delay(300);
    Step = Step + 10;
    if (Step > 500){
      Step = 10;
    }
    LCD.print("   ",2,1);
    LCD.print(Step,2,1);
  }
  
  
  
  
  BUTTON2_state = digitalRead(BUTTON2);
  if (BUTTON2_state != BUTTON2_last){
    if (BUTTON2_state == HIGH){
      if (Dire == false){
        digitalWrite(dir, HIGH);
        LCD.print("CW ",2,6);
      }
      if (Dire == true){
        digitalWrite(dir, LOW);
        LCD.print("CCW ",2,6);
      }
      Dire =! Dire;
    }
  }
  BUTTON2_last = BUTTON2_state;
  
  
  
    
  BUTTON3_state = digitalRead(BUTTON3);
  if (BUTTON3_state != BUTTON3_last){
    if (BUTTON3_state == HIGH){
      if (Speed == 3){
        Speed_delay = 5;
        LCD.print("LOW ",2,12);
      }
      if (Speed == 2){
        Speed_delay = 3;
        LCD.print("MID ",2,12);
      }
      if (Speed == 1){
        Speed_delay = 1;
        LCD.print("HIGH",2,12);
      }
      if (Speed == 0){
        Speed_delay = 100;
        LCD.print("STEP",2,12);
      }
      
      Speed++;
      if (Speed == 4){
        Speed = 0;
      }
    }
  }
  BUTTON3_last = BUTTON3_state;
   
  
  
  BUTTON4_state = digitalRead(BUTTON4);
  if (BUTTON4_state != BUTTON4_last){
    if (BUTTON4_state == HIGH){
      digitalWrite(GREENLED, LOW);
      digitalWrite(REDLED2, HIGH);
      for (int x = 0; x < Step; x++){
        digitalWrite(steps, HIGH);
        delay(1);
        digitalWrite(steps, LOW);
        delay(Speed_delay);
      }
      digitalWrite(REDLED2, LOW);
      digitalWrite(GREENLED, HIGH);
    } 
  }
  BUTTON4_last = BUTTON4_state;
}












