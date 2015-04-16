#include <Wire.h>
// servo pins
#define dc_servo1 16
#define dc_servo2 8
#define led 13
// Joystick pins
#define xAxisPin A0
#define yAxisPin A1
#define topTriggerPin = 11     
#define frontTriggerPin = 6
#define sideTriggerPin = 5
void setup(){
 
 Wire.begin();
//joystick button pins
  pinMode(topTriggerPin, INPUT);  
  pinMode(sideTriggerPin, INPUT);  
  pinMode(frontTriggerPin, INPUT); 

}


void loop(){
  
  
  
  
  
}
