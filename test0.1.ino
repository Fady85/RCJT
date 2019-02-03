/*Pinout
A0
A1
A2
10 Servo
*/

#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#include <math.h>

Servo name_servo;
 
#define max_dist "400cm"
#define speed_default 155
#define speed_max 255
NewPing sonar0(A0,A0,max_dist);
NewPing sonar1(A1,A1,max_dist);
NewPing sonar2(A2,A2,max_dist);

int servo_position = 0 ;

int isNotWithinRange(int range,int l1,int l2){
  if ((fabs(l1-l2)>range)){
    return 1;
  }
  return 0;

}

  
AF_DCMotor fleft(2, MOTOR12_64KHZ); //2
AF_DCMotor fright(1, MOTOR12_64KHZ); //4

AF_DCMotor bleft(3, MOTOR34_64KHZ); //1
AF_DCMotor bright(4, MOTOR34_64KHZ); //2

void setup(){
  name_servo.attach(10);
  pinMode(A8,INPUT_PULLUP);
  pinMode(A9,OUTPUT);
  digitalWrite(A9,0);

  Serial.begin(9600);
    setSpeeds(speed_default,speed_default,
      speed_default,speed_default);
  while (digitalRead(A8)==1){
    delay(50);
  }
  delay(1000);
  Serial.println("Starting...");

}
int l;
int f;
int r;

int weNeeddis;

void loopsOfAR(){
  while(isNotWithinRange(40,GetDist(sonar1),30)){
      drive_forward();
  }
  while(!isNotWithinRange(20,GetDist(sonar1),50)){
      drive_backward();
  }
  while(isNotWithinRange(40,GetDist(sonar0),GetDist(sonar2))){
      if (!isNotWithinRange(20,GetDist(sonar0),GetDist(sonar2))){
        weNeeddis=0;
      }else{
        weNeeddis=1;
      }
      if (weNeeddis){
        if(GetDist(sonar0)>GetDist(sonar2)){
         turn_left();
        }
        if(GetDist(sonar2)>GetDist(sonar0)){
          turn_right();
        }
      }
  }
 motor_stop();
}

void lop(){
  while(isNotWithinRange(40,GetDist(sonar1),30)){
      drive_forward();
  }
  while(!isNotWithinRange(20,GetDist(sonar1),30)){
      drive_backward();
  }

  while(isNotWithinRange(10,GetDist(sonar2),13)){
      turn_right();
  }
  while(isNotWithinRange(10,GetDist(sonar0),13)){
      turn_left();
  }
}
void losop(){
  
  drive_forward();
  delay(1000);
  
  turn_left();
  delay(400); //90
  motor_stop();
  delay(1000);

  turn_right();
  delay(400); //90
  motor_stop();
  delay(1000);

  drive_backward();
  delay(900);
  
  motor_stop();
  while (true){
      // statement
  }
}

int GetDist(NewPing sonarN){
    return sonarN.ping_cm();  
}

void sonarDebug(){
        Serial.print("Distance on A0: ");
         Serial.println(GetDist(sonar0));
         Serial.print("Distance on A1: ");
         Serial.println(GetDist(sonar1));
         Serial.print("Distance on A2: ");
         Serial.println(GetDist(sonar2));


}
/*void loop(){
  sonarDebug();
  delay(2000);
  }*/
/*
void loop(){

         drive_forward();

if(GetDist(sonar1)<=15){
    
  if(GetDist(sonar0)>GetDist(sonar2)){
    motor_stop();
    delay(500);
    turn_left();

    }
    
   else if (GetDist(sonar2)>GetDist(sonar0)){
 motor_stop();
    delay(500);
      turn_right();

      }
  }

  }                                           //sonar0=left,,sonar1=front,,sonar2=right
  */

void loop(){
  while(isNotWithinRange(8,GetDist(sonar1),6)){ // |sonar1-20|>31
      drive_forward();
  }
  while(!isNotWithinRange(4,GetDist(sonar1),5)){ // |sonar1-30|<51
      drive_backward();
      delay(100);
      turn_left();
      delay(100);
  }
  while(isNotWithinRange(3,GetDist(sonar0),GetDist(sonar2))){
/*      if (!isNotWithinRange(20,GetDist(sonar0),GetDist(sonar2))){
        weNeeddis=0;
      }else{
        weNeeddis=1;
      }*/
      //if (weNeeddis){
        if(GetDist(sonar0)>GetDist(sonar2)){
         turn_left();
         delay(50);
        }
        else if(GetDist(sonar2)>GetDist(sonar0)){
          turn_right();
          delay(50);
        }
      }
  //}
 motor_stop();
 }
