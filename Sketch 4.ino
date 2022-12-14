/*
 * Creation & Computation - Digital Futures, OCAD University
 * Kate Hartman / Nick Puckett
 * 
 * Multi Servo Sweep
 * Based on basic Sweep example, but updated to use a timer 
 * 
 * 
 */

#include <Servo.h>

int servoPin1 = 2;           //Pin that the servo is attached to.
int moveRate = 5;        //the time between updates in milliseconds
int minAngle = 0;     //sets the low point of the movement range
int maxAngle = 100;   //sets the high point of the movement range
int moveIncrement = 1;    // how much to move the motor each cycle 
int servoAngle1;

long lastTimeYouMoved1;

Servo servo1;  // create the Servo object

int potPin = A6;
int potValue;

int LDRpin = A7;
int LDRvalue;

int ledPins[] = {A0,A1,A2,A3}; //define the pin numbers
int blinkRates[] = {400,300,200,1000};  //define the blinking Rates
boolean ledStates[] = {false,false,false,false};  //define the current states
long lastTimeYouBlinked[] ={0,0,0,0};   //define the stored time value

int ledTotal = sizeof(ledPins) / sizeof(int); 

void setup() {
servo1.attach(servoPin1);  //attach the servo to the corresponding control pin
servoAngle1=minAngle;

for(int i=0;i<ledTotal;i++)
{
pinMode(ledPins[i],OUTPUT);  
} 

Serial.begin(9600);

}

void loop() 
{
//read from potentiometer
potValue = analogRead(potPin);
maxAngle = map(potValue,1023,0,0,90);


LDRvalue = analogRead(LDRpin);
moveRate = map(LDRvalue,200,900,10,100);

Serial.println(LDRvalue);
Serial.println(moveRate);

for(int i=0;i<ledTotal;i++)                             //another loop to check the values for each of the pins
{                                                       //the loop/array let us write the function only once and letting the compiler run through the list of values
  if(millis()-lastTimeYouBlinked[i]>=blinkRates[i])
  {
  ledStates[i] = !ledStates[i];
  lastTimeYouBlinked[i] = millis();
  }

digitalWrite(ledPins[i],ledStates[i]);
}

 if(millis()-lastTimeYouMoved1>=moveRate) //this very simple statement is the timer,
{                                          //it subtracts the value of the moment in time the last blink happened, and sees if that number is larger than your set blinking value
servo1.write(servoAngle1);

servoAngle1 += moveIncrement;

  if (servoAngle1 <= minAngle || servoAngle1 >= maxAngle) 
  {
    moveIncrement = -moveIncrement;
  }

lastTimeYouMoved1 = millis();            //save the value in time that this switch occured, so we can use it again.
   
}

}
