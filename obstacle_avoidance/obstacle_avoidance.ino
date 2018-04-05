
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;  
int Trig = A5; 

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define carSpeed 150
#define turnSpeed 250
#define turntime 500
#define forwardtime 2600
int rightDistance = 0, leftDistance = 0, middleDistance = 0;

void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 195);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
  Serial.println("Back");
}

void left() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255); 
  Serial.println("Left");
}

void right() {
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
  Serial.println("Right");
}

void stop() {
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

void setup() { 
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
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

void loop() { 
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
      else {
        forward();
      }
    }  
    else {
        forward();
    }                     
}
