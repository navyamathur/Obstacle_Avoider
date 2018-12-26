#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);

//L293 Connection   
  const int motorA1  = 2;  // Pin  2 of L293
  const int motorA2  = 3;  // Pin  7 of L293
  const int motorB1  = 4;  // Pin 10 of L293
  const int motorB2  = 5;  // Pin 15 of L293

//SR04 Connection
  const int trigPin = 9;
  const int echoPin = 10;

  int i=0;
  int j=0;
  long duration;
  int distance;
  char state;

void setup() {
    // Set pins as outputs:
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);

    // Sets the trigPin as an Output
    pinMode(trigPin, OUTPUT); 
    // Sets the echoPin as an Input
    pinMode(echoPin, INPUT); 

    // Starts the serial communication
    Serial.begin(9600); 
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  state='F';
  //Move car right when distance is less than 10 cm otherwise move forward
     if(distance < 20) { state='RE'; }
     else { state='F'; }

  /***********************Forward****************************/
  //If state is equal with letter 'F', car will go forward
    if (state == 'F') {
      digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); 
  //    analogWrite(motorA1, 200); analogWrite(motorA2, 0);
  //    analogWrite(motorB1, 200); analogWrite(motorB2, 0); 
    }
  /**********************Forward Left************************/
  //If state is equal with letter 'L', car will turn left
    else if (state == 'L') {
      digitalWrite(motorA1, HIGH); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW ); digitalWrite(motorB2, LOW); 
  //  	analogWrite(motorA1, 200); analogWrite(motorA2, 0);  
  //    analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
    }
  /***************************Right*****************************/
  //If state is equal with letter 'R', car will turn right
    else if (state == 'R') {
      digitalWrite(motorA1, LOW ); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, HIGH); digitalWrite(motorB2, LOW); 
  //  	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
  //    analogWrite(motorB1, 200); analogWrite(motorB2, 0); 		
    }
  //If state is equal with letter 'S', stop the car
    else if (state == 'S'){
      digitalWrite(motorA1, LOW); digitalWrite(motorA2, LOW);
      digitalWrite(motorB1, LOW); digitalWrite(motorB2, LOW); 
  //      analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
  //      analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }
  //If state is equal with letter 'RE', reverse and turn the car 
    else if(state == 'RE'){
      digitalWrite(motorA1, LOW); digitalWrite(motorA2, HIGH);
      digitalWrite(motorB1, LOW); digitalWrite(motorB2, LOW);
  //      analogWrite(motorA1, 0);  analogWrite(motorA2, 200); 
  //      analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    
    }

  Serial.print(distance);
  Serial.print(" cm, ");
  Serial.println(state);

  delay(500);
}



