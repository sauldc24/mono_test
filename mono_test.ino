#include <Stepper.h>

#define lowLimitPin 6
#define highLimitPin 7
#define lowDirection 0
#define highDirection 1
#define stepsPerRevolution 400

int motorPins[4] = {2,3,4,5};
Stepper motor = Stepper(stepsPerRevolution, 2, 3, 4, 5);
String command = "";
//
char availableCommands[][3]= {"INI", "!GW", "?PW", "!CH", "?PG"};
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
  Serial.print("entered command is ");
  Serial.println(command);
  if (command == "high"){
    Serial.println("moving in the high direction");
    moveToLimit(highDirection);
  }
  else if (command == "low"){
    Serial.println("moving in the low direction");
    moveToLimit(lowDirection);
  }
}

void moveToLimit (bool direction){
  if (direction){
    while (digitalRead(highLimitPin)){
      motor.step(1);
      delay(1);
    }
    Serial.println("limit sensor detected");
  }
  else {
    while (digitalRead(lowLimitPin)){
      motor.step(-1);
      delay(1);
    }
    Serial.println("limit sensor detected");
  }
}