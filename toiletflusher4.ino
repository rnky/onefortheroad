#include <AccelStepper.h>
#include <IRLibAll.h>

#define motorPin1 9
#define motorPin2 11
#define motorPin3 10
#define motorPin4 6

#define MotorInterfaceType 8

#define MY_PROTOCOL NEC
#define POWER_BUTTON 0xFB04F


int LED = 13; // Use the onboard Uno LED
IRrecv myReceiver(2);
IRdecode myDecoder;
uint32_t Previous;

  AccelStepper stepper = AccelStepper(MotorInterfaceType, 
  motorPin1, motorPin3, motorPin2, motorPin4);

  
void setup() {
  pinMode(LED, OUTPUT);
  myReceiver.enableIRIn();
  Serial.begin(9600);  
  stepper.setMaxSpeed(1000);  
}

void loop() {

stepper.setCurrentPosition(0);
  
  if (myReceiver.getResults())
  {
    myDecoder.decode();
    if(myDecoder.protocolNum == MY_PROTOCOL)
    {
      if(myDecoder.value==0xFFB04F)
      {
        Serial.println("Flush Sequence Engaged");
      while (stepper.currentPosition() != 4096)
        {
        stepper.setSpeed(4000);
        stepper.runSpeed();
       
        }
        delay(1000);
        stepper.setCurrentPosition(0);
            while (stepper.currentPosition() != -4096)
        {
        stepper.setSpeed(-4000);
        stepper.runSpeed();
        }
        
      }
    }
            myReceiver.enableIRIn();
      Serial.println("Flush Sequence Stand-By");        
  }
 /*   Serial.println("Flush Sequence Engaged");
    digitalWrite(LED, HIGH);
    
    
      stepper.setCurrentPosition(0);
  
  while (stepper.currentPosition() != 4096) {
    stepper.setSpeed(4000);
    stepper.runSpeed();

    
  }
  delay(300);
  
  stepper.setCurrentPosition(0);

  while (stepper.currentPosition() !=-4096) {
    stepper.setSpeed(-4000);
    stepper.runSpeed();*/
   
  }
    
    
 
  

  

  
