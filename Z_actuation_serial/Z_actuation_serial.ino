//#include <SoftwareSerial.h>
//SoftwareSerial serialPort(0,1);
// 0.254 = 1 step
int pwmCoilOne = 3;
int pwmCoilTwo = 11;
int dirCoilOne = 12;
int dirCoilTwo = 13;
int brkCoilOne = 8;
int brkCoilTwo = 9;
String typeofmove;
float valueofmove;
int posCounter = 0;
String recString;
char recCString[] = "";
char moverel[] = "MR";
char moveabs[] = "MA";
char movehome[] = "MH";
char sethome[] = "SH";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pwmCoilOne, OUTPUT);
  pinMode(pwmCoilTwo, OUTPUT);
  pinMode(dirCoilOne, OUTPUT);
  pinMode(dirCoilTwo, OUTPUT);
  pinMode(brkCoilOne, OUTPUT);
  pinMode(brkCoilTwo, OUTPUT);
  analogWrite(pwmCoilOne, 255);
  analogWrite(pwmCoilTwo,255);
  digitalWrite(dirCoilOne, LOW);
  digitalWrite(dirCoilTwo, LOW);
  digitalWrite(brkCoilOne, LOW);
  digitalWrite(brkCoilTwo, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  char rc;
  recString = "";
  typeofmove = "";
  valueofmove = NULL;
  if (Serial.available()) {
    typeofmove = Serial.readStringUntil(',');
    valueofmove = Serial.readStringUntil('\n').toInt();
    Serial.print(typeofmove);
    Serial.print(valueofmove);
    
  }
  
  recString.trim();
  recString.toCharArray(recCString, recString.length());
  //recCString = recString.c_str();
  //parseData();
  
  if (typeofmove == "MR") {
    Move(valueofmove);
    Serial.print("a");
  }
  else if (typeofmove == "MA") {
    Move(valueofmove - posCounter);
  }
  else if (typeofmove == "MH") {
    Move(-posCounter);
  }
  else if (typeofmove == "SH") {
    posCounter = 0;
  }
    
}





    
//void parseData() {
//
    // split the data into its parts
    
//  char * strtokIndx; // this is used by strtok() as an index
  
  //strtokIndx = strtok(recCString,",");      // get the first part - the string
  //strcpy(typeofmove, strtokIndx); // copy it to typeofmove
  
  //strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  //valueofmove = atoi(strtokIndx);     // convert this part to an integer
//}

void Move(int movecount) {
      if (movecount < 0) {
      movecount*=-1;
      for (int i = 0; i < movecount; i++) {
        int j = i%4;
        if (j == 0) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, HIGH);
          --posCounter;
          delay(19);
          
        }
        else if (j == 1) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, HIGH);
          --posCounter;
          delay(19);
          
        }
        else if (j == 2) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, LOW);
          --posCounter;
          delay(19);
         
        }
        else if (j == 3) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, LOW);
          --posCounter;
          delay(19);
          
        }
     }  
  }
  else if (movecount > 0) {
      for (int i = 0; i <= movecount; i++) {
        int j = i%4;
        if (j == 0) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, LOW);
          ++posCounter;
          delay(19);
          
        }
        else if (j == 1) {
          digitalWrite(dirCoilOne, HIGH);
          digitalWrite(dirCoilTwo, HIGH);
          ++posCounter;
          delay(19);
          
        }
        else if (j == 2) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, HIGH);
          ++posCounter;
          delay(19);
          
        }
        else if (j == 3) {
          digitalWrite(dirCoilOne, LOW);
          digitalWrite(dirCoilTwo, LOW);
          ++posCounter;
          delay(19);
          
        }
    }  
  }
}
