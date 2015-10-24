

#include <Stepper.h>

const int stepsPerLittleRevolution = 200;  //rotates the little gear one revolution
const int stepsPerBigRevolution = 400; //rotates the big gear one revolution


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerLittleRevolution, 8,9,10,11);

// set global state
int state;

void setup(){
  // set the speed at 10 rpm
  myStepper.setSpeed(7.5);
  //initialize serial port
  Serial.begin(9600);
  //define pins  
  pinMode(7, INPUT);
  Serial.println("start");
  //sends to reset state
//  reset();  
}

void loop(){
  if (Serial.available()){ //checks to see if there is a reading from the pid
    // read in from serial
    int piRead = Serial.read()-'0'; 
    // check if reset
    Serial.println(piRead);
    if (piRead == 7){
       reset(); 
    }
    // check if state changing
    else if (piRead > 0 && piRead < 7)
    {
       changeState(piRead);
    }
    }
  }


//moves the turntable to given state
void changeState(int newState){
  // number of states to rotate
  int stateSwitch = state - newState;
  // number of steps to next state
  int numSteps = (stepsPerBigRevolution/6)*stateSwitch;
  // Rotate to next state
  myStepper.step(-numSteps);
  // Set the state
  state = newState;
  // Notify the Pi
  Serial.println(state);
}

//resets the turntable
void reset(){
  //correct later
  changeState(6);
  
  boolean inStateZero;
  int switchRead = digitalRead(7);
  
  while (switchRead != HIGH){
    switchRead = digitalRead(7);
    myStepper.step(1);
    delay(50); //control speed of arduino (approx 7.5 RPM)
    }
 //sets the state
 state = 1; 
}
