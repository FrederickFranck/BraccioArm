#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int button = 13;

void setup() {
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base            (M1): 0 degrees
  //Shoulder        (M2): 40 degrees
  //Elbow           (M3): 180 degrees
  //Wrist vertical  (M4): 0 degrees
  //Wrist rotation  (M5): 180 degrees
  //gripper         (M6): 73 degrees
  Serial.begin(9600);
  pinMode(button,INPUT);
  Braccio.begin();
  moveStraight();
}


void loop() {
  
   /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees.               Allowed values from 0 to 180 degrees
   M2=shoulder degrees.           Allowed values from 15 to 165 degrees
   M3=elbow degrees.              Allowed values from 0 to 180 degrees
   M4=wrist vertical degrees.     Allowed values from 0 to 180 degrees
   M5=wrist rotation degrees.     Allowed values from 0 to 180 degrees
   M6=gripper degrees.            Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  /*
                       //(step delay, M1, M2, M3, M4, M5, M6);
  Braccio.ServoMovement(20,           0,  40, 180, 0, 180,  73);

  Braccio.ServoMovement(20,           0,  40, 180, 180, 180,  73);
  */
  
   
}

void pickUpCup(){

}



void moveStraight(){
  Braccio.ServoMovement(20,           0,  85, 90, 100, 180,  10); 
}

void moveTo(int a,int b,int c){
  Braccio.ServoMovement(20,           0,  a, b, c, 180,  10); 
}
