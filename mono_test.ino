#include <Stepper.h>

#define lowLimitPin 7
#define highLimitPin 8
#define lowDirection 0
#define highDirection 1
#define stepsPerRevolution 400

int motorPins[4] = {3,4,5,6};
Stepper motor = Stepper(stepsPerRevolution, 3, 4, 5, 6);
String command = "";
char newChar = "";
//
char availableCommands[][3]= {"INI", "!GW", "?PW", "!CH", "?PG"};
//
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++){
    pinMode(motorPins[i], OUTPUT);
  }
  pinMode(lowLimitPin, INPUT);
  pinMode(highLimitPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), void (*userFunc)(void), int mode)
}

void loop() {
  Serial.println("enter command");
  command = "";
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

void deEnergizeCoils(){
  for (int i = 0; i < 4; i++){
    digitalWrite(motorPins[i], LOW);
  }
}

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