#include <Stepper.h>

#define lowLimitPin 6
#define highLimitPin 7
#define lowDirection 0
#define highDirection 1
#define stepsPerRevolution 400

//the next defines specify the characteristics of the installed gratings, change accordingly
#define G1lowerLimit 101
#define G1UpperLimit 200
#define G2lowerLimit 201
#define G1UpperLimit 300
#define G3lowerLimit 301
#define G3UpperLimit 401
#define G1stepsPerNm 1
#define G2stepsPerNm 1
#define G3stepsPerNm 1


int motorPins[4] = {2,3,4,5};
Stepper motor = Stepper(stepsPerRevolution, 2, 3, 4, 5);
String command = "";
String instruction = "";
float argument;
int separatorIndex;
float currentWL;


//
char availableCommands[][3]= {"INI", "!GW", "?PW"};
//
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10000);
  for (int i = 0; i < 4; i++){
    pinMode(motorPins[i], OUTPUT);
  }
  pinMode(lowLimitPin, INPUT);
  pinMode(highLimitPin, INPUT);
}

void loop() {
  Serial.println("enter command");
  command = readCommand();
  Serial.print("entered command is ");
  Serial.println(command);
  separatorIndex = command.indexOf(" ");
  instruction = command.substring(0, separatorIndex);
  argument = command.substring(separatorIndex + 1).toFloat()
  if (command == "!GW"){
    //code to calculate direction and number of steps to get the desired wavelength
  }
  else if (command == "!PW"){
    Serial.println(currentWL);
  }
  else if (command == "INI"){
    
  }
}




//Helper Functions
//function to read a CR or LF terminated commands
String readCommand(){
  String command = "";
  char newChar = "";
  while (true) {
    if (Serial.available()){
      newChar = Serial.read();
      if ((newChar == '\n') || (newChar == '\r' )) break;
      else {
        command.concat(newChar);
      }        
    }
  }
  return command;
}
//function to deenergize coils after moving
void deEnergizeCoils(){
  for (int i = 0; i < 4; i++){
    digitalWrite(motorPins[i], LOW);
  }
}
//function to move motor until limit sensor is detected
void moveToLimit (bool direction){
  if (direction){
    while (digitalRead(highLimitPin)){
      motor.step(1);
      delay(1);
    }
  }
  else {
    while (digitalRead(lowLimitPin)){
      motor.step(-1);
      delay(1);
    }
  }
  deEnergizeCoils();
  Serial.println("limit sensor detected");
}
//function to chnge grating
int changeGrating(){
  moveToLimit(lowDirection);
  moveToLimit(highDirection);
}