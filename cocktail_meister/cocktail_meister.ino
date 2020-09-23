#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int button = 5;

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
     pickUpCup();
     //returnCup();   
}


//Pakt bekertje op en giet inhoud in een tweede bekertje
void pickUpCup(){
  int stepdelay = 30;
  
  //(step delay, M1, M2, M3, M4, M5, M6);
  Braccio.ServoMovement(stepdelay,         80,  85, 90, 100,  0,   10);
  Braccio.ServoMovement(stepdelay,         80,  85, 180, 100, 0,  10);
  Braccio.ServoMovement(stepdelay,          80,  110, 180, 100, 0, 10);
  Braccio.ServoMovement(stepdelay,          80,  110, 180, 100, 30,10);
  
  //in front of cup 
  Braccio.ServoMovement(stepdelay,        80,  110, 180, 80,30, 10);

  //move in cup
  Braccio.ServoMovement(stepdelay,        80,  130, 160, 80, 30, 10);
 
  //grip cup
  Braccio.ServoMovement(stepdelay,        80,  130, 160, 80, 30, 70);

  //lift up 
  Braccio.ServoMovement(stepdelay,        80,  130, 130, 110, 30, 70);

  //draai basis
  Braccio.ServoMovement(stepdelay,        60,  130, 130, 110, 30, 70);
  
  //kiep beker
  Braccio.ServoMovement(stepdelay,        60,  130, 130, 110, 140, 70);

  
  delay(3000);
}


//zet bekertje terug op oorspronkelijke positie (WIP)
void returnCup(){
  
  int stepdelay = 30;
  //terug kiepen
  Braccio.ServoMovement(stepdelay,        60,  130, 130, 110, 30, 70);
  

  //terug draaien
  Braccio.ServoMovement(stepdelay,        80,  130, 130, 110, 30, 70);
  Braccio.ServoMovement(stepdelay,        80,  130, 130, 110, 25, 70);
 
  //naar omlaag & loslaten
  Braccio.ServoMovement(stepdelay,        80,  130, 160, 80, 25, 70);
  Braccio.ServoMovement(10,        80,  130, 160, 80, 25, 10);
  Braccio.ServoMovement(stepdelay,        80,  135, 160, 80, 25, 10);

  //beweeg arm naar achter (WIP)
  Braccio.ServoMovement(stepdelay,        80,  135, 160, 70, 25, 10);
  Braccio.ServoMovement(stepdelay,        80,  135, 180, 70, 25, 10);
  Braccio.ServoMovement(stepdelay,        80,  125, 180, 70, 25, 10);
  
  
  Braccio.ServoMovement(stepdelay,        80,  115, 180, 70, 25, 10);
  Braccio.ServoMovement(stepdelay,        80,  100, 180, 70, 25, 10);
}


void moveStraight(){
  Braccio.ServoMovement(20,           0,  85, 90, 100, 0,  10); 
}
