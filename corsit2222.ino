#include<SoftwareSerial.h>
#define en1 6
#define en2 7
int trig_front=8; //trigger pin for front
int echo_front=9; //echo pin for front
int trig_right=10;//trigger pin for right
int echo_right=11;//echo pin for right

double duration1,duration2;           
double distance_front,distance_right;
double distparam_front=50;             
double distparam_right=50;              
double dist_move_before_right_turn=5;  
double dist_move_after_right_turn=5;   

int turn_left_time=500;               
int turn_right_time=500;              

int leftWheelForward=5;
int rightWheelForward=3;
int leftWheelBackward=4;
int rightWheelBackward=2;

void turnLeft(){
  digitalWrite(leftWheelForward, LOW);
  digitalWrite(leftWheelBackward, HIGH);
  digitalWrite(rightWheelForward, HIGH);
  digitalWrite(rightWheelBackward, LOW);
  delay(turn_left_time);
  digitalWrite(leftWheelBackward, LOW);
  digitalWrite(rightWheelForward, LOW);
}

void turnRight(){
  digitalWrite(leftWheelForward, HIGH);
  digitalWrite(leftWheelBackward, LOW);
  digitalWrite(rightWheelForward, LOW);
  digitalWrite(rightWheelBackward, HIGH);
  delay(turn_right_time);
  digitalWrite(leftWheelBackward, LOW);
  digitalWrite(rightWheelForward, LOW);
}

void forward(int del){
  digitalWrite(leftWheelForward, HIGH);
  digitalWrite(leftWheelBackward, LOW);
  digitalWrite(rightWheelForward, HIGH);
  digitalWrite(rightWheelBackward, LOW);
  delay(del);
  digitalWrite(leftWheelForward, LOW);
  digitalWrite(rightWheelForward, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(leftWheelForward,OUTPUT);
  pinMode(leftWheelBackward,OUTPUT);
  pinMode(rightWheelForward,OUTPUT);
  pinMode(rightWheelBackward,OUTPUT);
  pinMode(trig_front,OUTPUT);
  pinMode(trig_right,OUTPUT);
  pinMode(echo_front,INPUT);
  pinMode(echo_right ,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // trig is trigger pin.
  // echo is trigger echo pin.
  digitalWrite(trig_front, LOW);                     
  delayMicroseconds(2);
  digitalWrite(trig_front, HIGH);
  delayMicroseconds(10);  
  duration1 =  pulseIn(echo_front, HIGH,8000);
  distance_front = (duration1 / 2) / 29.1;             
  
  digitalWrite(trig_right, LOW);                     
  delayMicroseconds(2);
  digitalWrite(trig_right, HIGH);
  delayMicroseconds(10);  
  duration2 =  pulseIn(echo_right, HIGH,8000);
  distance_right = (duration2 / 2) / 29.1;             
  
  if(distance_right<distparam_right && distance_front>=distparam_front){
    forward(10); 
  }
  else if(distance_front>=distparam_front && distance_front>=distparam_front){
    forward(dist_move_before_right_turn);
    turnRight();                         
    forward(dist_move_after_right_turn); 
  }  
}
