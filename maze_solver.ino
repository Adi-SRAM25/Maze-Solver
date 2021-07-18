#include<Servo.h>

Servo myservo,s2;
int pos=0;
int pos1=0;

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5; // Echo Pin of Ultrasonic Sensor

void setup() {
  pinMode(10,OUTPUT);
  Serial.begin(9600); // Starting Serial Terminal
    
  myservo.attach(10);
  s2.attach(11);
}

void loop() {
  long duration, inches, cm;
  int array1 [65];
  int array2 [65];
  int max1=0,max2=0,maxin1=0,maxin2=0;
  
  for (pos = 0; pos <= 180; pos += 6) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
   delay(15);                       // waits 15ms for the servo to reach the position
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(5);
   array1[pos/6]= cm;

  }

 for(int i=0;i<31;i++)
  {
   if (max1<array1[i])
   { 
   if(i<1||i>29||(i<16&&i>14))
     {max1=array1[i];
       maxin1=i;}
   }
    
  }
    s2.write(maxin1*6);
    
  
for (pos = 180; pos >= 0; pos -= 6) { // goes from 180 degrees to 0 degrees
   myservo.write(pos);              // tell servo to go to position in variable 'pos'
   delay(15);                       // waits 15ms for the servo to reach the position
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.print(cm);
   Serial.print("cm");
   //Serial.print(pos);
   Serial.println();
   delay(5);
   
 array2[(180-pos)/6]=cm;
   
}

 for(int i=0;i<31;i++)
  {
   if (max2<array2[i])
   { 
   if(i<1||i>29||(i<16&&i>14))
  { max2=array2[i];
   maxin2=i;}
    }
    
  }
    s2.write(180-maxin2*6);
    
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
