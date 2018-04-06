//Line Tracking IO define ---------------------------------
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo  

int Echo = A4;  
int Trig = A5; 

#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

// USER INPUTS --------------------------------------------

#define carSpeed1 150 // default 150
#define carSpeed2 150 // default 150
#define delay1 100
#define turnSpeed 250
#define turntime 500
#define forwardtime 2600
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

// Function Setup -----------------------------------------

void forward(){
  analogWrite(ENA, carSpeed1);  // Left side wheels
  analogWrite(ENB, carSpeed2);   // Left side wheels
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed1);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
}

//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  

// 

void setup(){
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
}

// Main Control Loop ------------------------------------------------

// Note: Black line = 1 or high
void loop() {
  unsigned long StartTime = millis();
  myservo.write(90);  //(initial 90/modified to 125)setservo position according to scaled value
  delay(500); 
  middleDistance = Distance_test();
  
  if(middleDistance <= 27) {     
      stop();
      delay(500);                         
      myservo.write(10);          
      delay(1000);      
      rightDistance = Distance_test();
      
      delay(500);
      myservo.write(90);     //initial 90/modified to 125         
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();
      
      delay(500);
      myservo.write(90);     //initial 90/modified to 125         
      delay(1000);
      if(rightDistance > leftDistance) {
        right();
        delay(turntime);
          forward();  //go forward
          delay(forwardtime);//delay 1000 ms
            left();     //turning left
            delay(turntime);
              forward();  //go forward
              delay(forwardtime);//delay 1000 ms
                left();     //turning left
                delay(turntime);
                  forward();  //go forward
                  delay(forwardtime);//delay 1000 ms
                    right();
                    delay(0);
      }
      else if(rightDistance < leftDistance) {
        left();
        delay(turntime);
          forward();  //go forward
          delay(forwardtime);//delay 1000 ms
            right();     //turning left
            delay(turntime);
              forward();  //go forward
              delay(forwardtime);//delay 1000 ms
                right();     //turning left
                delay(turntime);
                  forward();  //go forward
                  delay(forwardtime);//delay 1000 ms
                    left();
                    delay(0);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        back();
        delay(180);
      }
      }
      
  else if((LT_R==0 && LT_M==0 && LT_L==0) || (LT_R==1 && LT_M==1 && LT_L==1)){
    forward();
  }
  else if(LT_R==1 && LT_M==0 && LT_L==1){
    forward();
  }
  else if((LT_R==1 && LT_M==0 && LT_L==0) || (LT_R==1 && LT_M==1 && LT_L==0)) { 
    right();
    delay(delay1);
    //while(LT_R==1);                             
  }   
  else if((LT_R==0 && LT_M==0 && LT_L==1) || (LT_R==0 && LT_M==1 && LT_L==1)) {
    left();
    delay(delay1);
    //while(LT_L==1);  
  }
  else if(LT_R==0 && LT_M==1 && LT_L==0) {  
    right();
  }
  
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - StartTime;
  Serial.println(ElapsedTime);
  Serial.println(CurrentTime);
}
