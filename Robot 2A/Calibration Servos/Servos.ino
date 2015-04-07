/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

int minPos=0;
int maxPos=0;
char* type = "bras_droit";
 
void setup() 
{ 
  if (!strcmp(type, "empileur")) {
    minPos=15;
    maxPos=105;
  } else if (!strcmp(type, "bras_droit")) {
    minPos=35;
    maxPos=170;
  } else if (!strcmp(type, "bras_gauche")) {
    minPos=15;
    maxPos=150;  
  } else if (!strcmp(type, "manege")) {
    minPos=40;
    maxPos=150;  
  }
  myservo.attach(0);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  for(pos = minPos; pos <= maxPos; pos++) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  }
  for(pos = maxPos; pos >= minPos; pos--)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  }
  delay(300);
} 

