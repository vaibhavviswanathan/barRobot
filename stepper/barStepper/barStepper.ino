

#include <Stepper.h>

const int stepsPerLittleRevolution = 200;  //rotates the little gear one revolution
const int stepsPerBigRevolution = 400; //rotates the big gear one revolution

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8,9,10,11);

// set global state
int state;

void setup(){
  // set the speed at 30 rpm
  myStepper.setSpeed(30);
  //initialize serial port
  Serial.begin(9600);
  //define pins  
  reset();
  
  
}



void loop(){
  
}


void changeState(int newState){
  
}

void reset(){
  
 state = 0; 
}
