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
}

//zet de arm rechtop 
void moveStraight(){
  Braccio.ServoMovement(20,           0,  85, 90, 100, 180,  10); 
}

//beweegt de arm met gegeven hoeken voor m2,m3,m4
void moveTo(int angle_m2,int angle_m3,int angle_m4){
  Braccio.ServoMovement(20,           0,  angle_m2, angle_m3, angle_m4, 180,  10); 
}

//probeert de correcte hoeken te berekenen om de arm naar het gegeven punt in cartesische coordinaten te bewegen
//de y coordinaat wordt voorlopig nog genegeert
int moveToPoint(int x, int y, int z){
  
  //de hoeken krijgen een beginwaarde 
  int angle_m2 = 90;
  int angle_m3 = 90;
  int angle_m4 = 90;

  //hoe ver het punt mag afwijken van de gegeven coordinaten
  int margin = 2;
  
  //berekende coordinaten
  double _x = 0;
  double _z = 0;

  bool point_found = false;
  
  while(!point_found){
    //moveTo(angle_m2,angle_m3,angle_m4);

    //berekent coordinaten op basis van de hoeken 
    _x = getX(angle_m2,angle_m3,angle_m4);
    _z = getZ(angle_m2,angle_m3,angle_m4);

    //print deze coordinaten
    Serial.print(_x);
    Serial.print(" ");
    Serial.print(_z);
    Serial.println();

    //als de berekende coordinaten tussen de toegelaten marges ligt hebben we het punt gevonden en bewegen we de arm
    if( (x - margin) > _x && _x < (x + margin) && (z - margin) > _z && _z < (z + margin)){
      point_found = true;
      moveTo(angle_m2,angle_m3,angle_m4);
    }

    //anders passen we de hoeken aan met kleine wijzigingen op basis van de berekende coordinaten
    else{
      if(_x > (x + margin)){
        if(angle_m2 >= 90){
          angle_m2 = angle_m2 - 5;
        }
        if(angle_m2 < 90){
          angle_m2 = angle_m2 + 5;
        }
  
        if(angle_m3 >= 90){
          angle_m3 = angle_m3 - 5;
        }
        if(angle_m3 < 90){
          angle_m3 = angle_m3 + 5;
        }
  
        if(angle_m4 >= 90){
          angle_m4 = angle_m4 - 2;
        }
        if(angle_m4 < 90){
          angle_m4 = angle_m4 + 2;
        }
    }


    if(_x < (x - margin)){
        if(angle_m2 >= 90){
          angle_m2 = angle_m2 + 5;
        }
        if(angle_m2 < 90){
          angle_m2 = angle_m2 - 5;
        }
  
        if(angle_m3 >= 90){
          angle_m3 = angle_m3 + 5;
        }
        if(angle_m3 < 90){
          angle_m3 = angle_m3 - 5;
        }
  
        if(angle_m4 >= 90){
          angle_m4 = angle_m4 - 2;
        }
        if(angle_m4 < 90){
          angle_m4 = angle_m4 + 2;
        }
    }


    if(_z > (z + margin)){
        if(angle_m2 >= 90){
          angle_m2 = angle_m2 + 5;
        }
        if(angle_m2 < 90){
          angle_m2 = angle_m2 - 5;
        }
  
        if(angle_m3 >= 90){
          angle_m3 = angle_m3 + 5;
        }
        if(angle_m3 < 90){
          angle_m3 = angle_m3 - 5;
        }
  
        if(angle_m4 >= 90){
          angle_m4 = angle_m4 + 2;
        }
        if(angle_m4 < 90){
          angle_m4 = angle_m4 - 2;
        }
      }


    if(_z < (z - margin)){
        if(angle_m2 >= 90){
          angle_m2 = angle_m2 - 5;
        }
        if(angle_m2 < 90){
          angle_m2 = angle_m2 + 5;
        }
  
        if(angle_m3 >= 90){
          angle_m3 = angle_m3 - 5;
        }
        if(angle_m3 < 90){
          angle_m3 = angle_m3 + 5;
        }
  
        if(angle_m4 >= 90){
          angle_m4 = angle_m4 + 2;
        }
        if(angle_m4 < 90){
          angle_m4 = angle_m4 -2;
        }
    }
    }
    
    delay(3000);
    
  }
}

//gaat alle mogelijk hoeken af en kijkt of bij elke combinatie die coordinaten overeenkomen
//dit gaat heel lang duren 
void bruteforce(int x, int y, int z){
  double wrist_length = 11.2;
  double elbow_lenght = 12.2;
  double shoulder_lenght = 12.2;
  double base_length = 7;
  double radials = ((2*PI)/360);

  for(int angle_m2 = 15; angle_m2 <=165; angle_m2++){
    for(int angle_m3 = 0; angle_m3 <= 180; angle_m3++){
      for(int angle_m4 = 0; angle_m4 <= 180; angle_m4++){
        
        //hoeken omzetten in radialen want sin() & cos() functies werken met radialen
        double angle_m2_radial = angle_m2*radials;
        double angle_m3_radial = angle_m3*radials;
        double angle_m4_radial = angle_m4*radials;
        
        if( (x == (S*cos(angle_m2_radial) + E*cos(angle_m3_radial) + W*cos(angle_m4_radial))) && (z == (S*sin(angle_m2_radial) + E*sin(angle_m3_radial) + W*sin(angle_m4_radial) + Base))){
          Braccio.ServoMovement(20,           0,  a, b, c, 180,  10);
          return;
        }
      }
    }
  }
}

//berekent X coordinaat op basis van gegeven hoeken 
double getX(double angle_m2,double angle_m3,double angle_m4){
  
  double wrist_length = 11.2;
  double elbow_lenght = 12.2;
  double shoulder_lenght = 12.2;
  double radials = ((2*PI)/360);
  
  //hoeken omzetten in radialen want sin() & cos() functies werken met radialen
  double angle_m2_radial = angle_m2*radials;
  double angle_m3_radial = angle_m3*radials;
  double angle_m4_radial = angle_m4*radials;
        
  return (S*cos(angle_m2_radial) + E*cos(angle_m3_radial) + W*cos(angle_m4_radial));
}

//berekent Z coordinaat op basis van gegeven hoeken 
double getZ(double angle_m2,double angle_m3,double angle_m4){
  
  double wrist_length = 11.2;
  double elbow_lenght = 12.2;
  double shoulder_lenght = 12.2;
  double base_length = 7;
  double radials = ((2*PI)/360);

  //hoeken omzetten in radialen want sin() & cos() functies werken met radialen
  double angle_m2_radial = angle_m2*radials;
  double angle_m3_radial = angle_m3*radials;
  double angle_m4_radial = angle_m4*radials;
        
  return (S*sin(angle_m2_radial) + E*sin(angle_m3_radial) + W*sin(angle_m4_radial) + Base);
}
