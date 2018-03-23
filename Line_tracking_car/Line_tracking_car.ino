

//Line Tracking IO define ---------------------------------

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

#define carSpeed 150

// Function Setup -----------------------------------------

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
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

// 

void setup(){
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}

// Main Control Loop ------------------------------------------------

// Note: Black line = 1 or high
void loop() {
  if(LT_R==0 && LT_M==0 && LT_L==0){
    forward();
  }
   if(LT_R==1 && LT_M==1 && LT_L==1){
    forward();
  }
    if(LT_R==1 && LT_M==0 && LT_L==1){
    forward();
  }
  else if(LT_R==1 || (LT_R==1 && LT_M==1)) { 
    right();
    //while(LT_R==1);                             
  }   
  else if(LT_L==1 || (LT_L==1 && LT_M==1)) {
    left();
    //while(LT_L==1);  
  }
    else if(LT_M==1) {  
    forward();
  }
}

