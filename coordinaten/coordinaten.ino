#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

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
  Braccio.begin();
  moveStraight();
}


void loop() {
  moveToPoint(10,0,10);
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
//zet de arm rechtop
void moveStraight(){
  Braccio.ServoMovement(20,           0,  85, 90, 100, 180,  10); 
}
//verplaats de arm met de gegeven hoeken
void moveTo(int a,int b,int c){
  Braccio.ServoMovement(20,           0,  a, b, c, 180,  10); 
}

//beweeg naar een gevraagd punt (werkt niet)
//gebruikt beginhoeken en past deze aan om zo dichter bij het gegeven punt te geraken 
//maak de gegeven hoeken telkens kleiner/groter om zo in de buurt van het gegeven punt te bereiken
int moveToPoint(int x, int y, int z){
  int a = 90;
  int b = 90;
  int c = 90;
  int margin;
  double _x = 0;
  double _z = 0;
  
  while(true){
    moveTo(a,b,c);
    _x = getX(a,b,c);
    _z = getZ(a,b,c);
    
    Serial.print(_x);
    Serial.print(" ");
    Serial.print(_z);
    Serial.println();

    if(_x > (x + margin)){
      if(a >= 90){
        a = a - 5;
      }
      if(a < 90){
        a = a + 5;
      }

      if(b >= 90){
        b = b - 5;
      }
      if(b < 90){
        b = b + 5;
      }

      if(c >= 90){
        c = c - 2;
      }
      if(c < 90){
        c = c + 2;
      }
    }


    if(_x < (x - margin)){
      if(a >= 90){
        a = a + 5;
      }
      if(a < 90){
        a = a - 5;
      }

      if(b >= 90){
        b = b + 5;
      }
      if(b < 90){
        b = b - 5;
      }

      if(c >= 90){
        c = c - 2;
      }
      if(c < 90){
        c = c + 2;
      }
    }


    if(_z > (z + margin)){
      if(a >= 90){
        a = a + 5;
      }
      if(a < 90){
        a = a - 5;
      }

      if(b >= 90){
        b = b + 5;
      }
      if(b < 90){
        b = b - 5;
      }

      if(c >= 90){
        c = c + 2;
      }
      if(c < 90){
        c = c - 2;
      }
    }


    if(_z < (z - margin)){
      if(a >= 90){
        a = a - 5;
      }
      if(a < 90){
        a = a + 5;
      }

      if(b >= 90){
        b = b - 5;
      }
      if(b < 90){
        b = b + 5;
      }

      if(c >= 90){
        c = c + 2;
      }
      if(c < 90){
        c = c -2;
      }
    }

    delay(3000);
    
  }
}

//gaat alle mogelijk hoeken af en kijkt of bij elke combinatie die coordinaten overeenkomen
//dit gaat heel lang duren 
void bruteforce(int x, int y, int z){
  double W = 11.2;
  double E = 12.2;
  double S = 12.2;
  double Base = 7;
  double r = ((2*PI)/360);

  for(int a = 15; a <=165; a++){
    for(int b = 0; b <= 180; b++){
      for(int c = 0; c <= 180; c++){
        double A = a*r;
        double B = b*r;
        double C = c*r;
        if( (x == (S*cos(A) + E*cos(B) + W*cos(C))) && (z == (S*sin(A) + E*sin(B) + W*sin(C) + Base))){
          Braccio.ServoMovement(20,           0,  a, b, c, 180,  10);
          return;
        }
      }
    }
  }
}

//berekent X coordinaat met gegeven hoeken
double getX(double a,double b,double c){
  double W = 11.2;
  double E = 12.2;
  double S = 12.2;
  
  double r = ((2*PI)/360);
  double A = a*r;
  double B = b*r;
  double C = c*r;
  return (S*cos(A) + E*cos(B) + W*cos(C));
}

berekent Z coordinaat met gegeven hoeken
double getZ(double a,double b,double c){
  double W = 11.2;
  double E = 12.2;
  double S = 12.2;
  double Base = 7;
  double r = ((2*PI)/360);
  double A = a*r;
  double B = b*r;
  double C = c*r;
  return (S*sin(A) + E*sin(B) + W*sin(C) + Base);
}
