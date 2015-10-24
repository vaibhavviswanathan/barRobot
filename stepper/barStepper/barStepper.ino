

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
  if (Serial.available()){ //checks to see if there is a reading from the pid
    // read in from serial
    char piRead = Serial.read(); 
    // check if reset
    if (piRead == 69){
       reset(); 
    }
    // check if state changing
    else if (piRead == (1 | 2 | 3 | 4 | 5 | 6 )){
       changeState(piRead);
    }
    }
  }
}

//moves the turntable to given state
void changeState(int newState){
  // number of states to rotate
  int stateSwitch = state - newState;
  // number of steps to next step
  int numSteps = (stepsPerBigRevolution/6)*stateSwitch;
  // Rotate to next state
  myStepper.step(numSteps);
  // Set the state
  state = newState;
  // Notify the Pi
  Serial.println(state);
}

//resets the turntable
void reset(){
  //correct later
  changeState(0);  
 //sets the state
 state = 0; 
}
