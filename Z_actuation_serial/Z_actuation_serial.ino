#include <SoftwareSerial.h>
SoftwareSerial serialPort(0,1);
// 0.254 = 1 step
int pwmCoilOne = 3;
int pwmCoilTwo = 11;
int dirCoilOne = 12;
int dirCoilTwo = 13;
int brkCoilOne = 8;
int brkCoilTwo = 9;
char typeofmove;
float valueofmove;

void setup() {
  // put your setup code here, to run once:
  serialPort.begin(9600);
  pinMode(pwmCoilOne, OUTPUT);
  pinMode(pwmCoilTwo, OUTPUT);
  pinMode(dirCoilOne, OUTPUT);
  pinMode(dirCoilTwo, OUTPUT);
  pinMode(brkCoilOne, OUTPUT);
  pinMode(brkCoilTwo, OUTPUT);
  analogWrite(pwmCoilOne, 86);
  analogWrite(pwmCoilTwo,86);
  digitalWrite(dirCoilOne, LOW);
  digitalWrite(dirCoilTwo, LOW);
  digitalWrite(brkCoilOne, LOW);
  digitalWrite(brkCoilTwo, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  char rc;
  String recString = "";
  serialPort.listen();
  while (serialPort.available() > 0) {
    rc = Serial.read();
    if (rc != '\n'){
    recString = recString + serialPort.read();
    }
  }
  recString = recString.trim();
  recString[] = recString.c_str();
  parseData();
  valueofmove = valueofmove/1.27;
  if (String(typeofmove).trim() == "MR") {
  MoveRelative();
  
    
}
}    
void parseData() {

    // split the data into its parts
    
  char * strtokIndx; // this is used by strtok() as an index
  
  strtokIndx = strtok(recString,",");      // get the first part - the string
  strcpy(typeofmove, strtokIndx); // copy it to typeofmove
  
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  valueofmove = atof(strtokIndx);     // convert this part to an integer
}

void MoveRelative() {
      if (valueofmove < 0) {
      for (int i = 0, i >= valueofmove, i--) {
        j = i%4;
        if (j == 0) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, HIGH);
          delay(1);
        }
        else if (j == 1) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, HIGH);
          delay(1);
        }
        else if (j == 2) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, LOW);
          delay(1);
        }
        else if (j == 3) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, LOW);
          delay(1);
        }
     }  
  }
  else if (valueofmove > 0) {
      for (int i = 0, i <= valueofmove, i++) {
        int j = i%4;
        if (j == 0) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, LOW);
          delay(1);
        }
        else if (j == 1) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, HIGH);
          delay(1);
        }
        else if (j == 2) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, HIGH);
          delay(1);
        }
        else if (j == 3) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, LOW);
          delay(1);
        }
    }  
  }
}
}
