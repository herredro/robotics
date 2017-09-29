const int motorDirPin = 4;
const int motorSpeedPin = 3;
const int sensorPin = A0;

int motorSpeed = 0;
int motorDirection = HIGH;
int sensorValue = 0;
int currentPosition = 0;

unsigned long previousMillis = 0;
int interval = 10;

float Kp = 2; 
float Ki = 2;

int desiredLoc = 600;

int previousErrorI=0;



void setup() {
  // put your setup code here, to run once:
  pinMode(motorDirPin, OUTPUT);
  digitalWrite(motorDirPin, motorDirection); 
  analogWrite(motorSpeedPin, 0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:  
  unsigned long currentMillis = millis();
  
  if((currentMillis - previousMillis) > interval){
    
    previousMillis = currentMillis;

    //To control the error:
    sensorValue = analogRead(sensorPin);
    
   /* Serial.print("Current value: ");
    Serial.print(sensorValue);
    Serial.println();*/
    
    //Serial.write(sensorValue);
    
    int errorP = desiredLoc - sensorValue;


    if(errorP > 0 ){
      //Go right
      motorDirection = HIGH;
    }
    else if(errorP <0){
      //Go left
      motorDirection = LOW;
    }

    //Update the speed
    int motorSpeedP = Kp*errorP;

    ////////// Integral \\\\\\\\\\\\\\\\\\\\
    
    int currentErrorI = desiredLoc - sensorValue;
    float averageErrorI = (currentErrorI-previousErrorI)/2;
    float integral = averageErrorI * interval;
    previousErrorI = currentErrorI;
    int motorSpeedI = Ki * integral;

    //Add up the various elements
    motorSpeed = motorSpeedP + motorSpeedI;
    Serial.print("P: ");
    Serial.print(motorSpeedP);
    Serial.print(" ");
    Serial.print("I: ");
    Serial.print(motorSpeedI);
    Serial.println();
    Serial.println();

    digitalWrite(motorDirPin, motorDirection);
    analogWrite(motorSpeedPin, motorSpeed);
  }  
}
