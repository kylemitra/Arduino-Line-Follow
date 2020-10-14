#include <Servo.h> 
#include <SoftwareSerial.h>

int mL;
int mR;
int R;
int L;
boolean shouldGoStraight;
boolean shouldVeerLeft;
boolean shouldVeerRight;
boolean stradel;
boolean shouldTurnRight;
boolean shouldTurnLeft;
boolean shouldStop;

int t = 70; //t has to be higher than value the sensor returns over a white surface and lower than the value the sensor returns over a black surface
// the value the QTI sensor returns when its hovering over a black or white surface is dependant on how high the QTI sensor is off the ground. 
//If you notice the robot is not working  correctly check the values the QTI sensors are returning on the Serial Port.

Servo left, right; 

void setup() {
  Serial.begin(9600);
  left.attach(12); // replace this with the pin you attatched the WHITE wire of the LEFT motor controller too
  right.attach(13); // replace this with the pin you attatched the WHITE wire of the RIGHT motor controller too
}

void loop() {
  mL = RCTime(5); // replace this with the pin you attatched the WHITE wire of the LEFT qti sensor too
  mR = RCTime(6); // replace this with the pin you attatched the WHITE wire of the RIGHT qti sensor too
  R  = RCTime(7);
  L  = RCTime(4);
 
  
 //Serial.println();
 //Serial.println(R);
 //Serial.println(mR);
 //Serial.println(mL);
 //Serial.println(L);

  stradel = (R < t && L < t);
  shouldGoStraight = (stradel && mL > t && mL > t); //considered on the line if the outside are white and inside are black
  shouldVeerLeft = (stradel && mL < t && mR > t); 
  shouldVeerRight = (stradel && mL > t && mR < t);
  shouldTurnRight = (L < t && R > t && mR > t && mL > t);
  shouldTurnLeft = (L < t && R > t && mR > t && mL > t);
  shouldStop = (R > t && L > t);
 
  if(shouldStop){ //if outers are black, STOP
    right.write(1500); 
    left.write(1500); 
    Serial.println("stop");
  }
  else if(shouldVeerRight){ //VEER RIGHT 
    right.write(1490);
    left.write(1550); 
    Serial.println("veer right");
  }
  else if(shouldVeerLeft){ //VEER LEFT
    right.write(1450);
    left.write(1510); 
    Serial.println("veer left");
  }
  
  else if(shouldGoStraight){ //if they are both white, go forward
    right.write(1450);
    left.write(1550); 
    Serial.println("straight");
  }
  else if(shouldTurnLeft){
    right.write(1480);
    left.write(1480);
   Serial.println("turn left");
  }
  else if(shouldTurnRight){
    right.write(1510);
    left.write(1510);
    Serial.println("turn right");
  }
}
long RCTime(int sensorIn){
   long duration = 0;
   pinMode(sensorIn, OUTPUT);     
   digitalWrite(sensorIn, HIGH);  
   delay(1);                      
   pinMode(sensorIn, INPUT);      
   digitalWrite(sensorIn, LOW);   
   while(digitalRead(sensorIn)){  
      duration++;
   }
   return duration;
}
