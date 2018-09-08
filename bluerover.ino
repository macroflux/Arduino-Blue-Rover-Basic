#include <SoftwareSerial.h>
SoftwareSerial BT(7, 6); // RX | TX vales from arduino

//motor A shield interface directions to arduino port numbers
int pinI1=8;
int pinI2=11; 

//motor A shield interface throttle to arduino port number
int speedpinA=9;

//motor B shield interface directions to arduino port numbers
int pinI3=12;
int pinI4=13; 

//motor B shield interface throttle to arduino port number
int speedpinB=10;

//base throttle values for A and B motors (this sketch uses same throttle speed per motor on direction changes. may need to have different values per motor due to one motor used for steering, or physical differences between motor loads)
int Aspeed =127;
int Bspeed =500;

char a; // stores incoming character from other device
char leftrightstore = 'c'; //default left/center/state. this allows for both a left forward, straight forward, right forward, or left back, straight back, or right back steering method. this supports both servo steering or a hybrid skid steering without 'pivot in place' skid steering, since steering is in increment bursts
int movementincrement = 500; //each command F, B, on L, C, R is initiated for a length of time based on received character command. alter this value for longer or shorter milliseconds of movement per received character
void setup()
{
  delay(500);  
  // HC-06 default baud rate is 9600. set to different baud speed if your HC-06 is set differently
  BT.begin(9600);  
  //initialize Motor A arduino ports
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  //initialize Motor B arduino ports
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
}

void loop()
{
 if (BT.available())
  // if received character in serial
  {
    a=(BT.read());
        if (a=='f'){
          if (leftrightstore == 'c'){
            forward();
          }else if(leftrightstore == 'l'){
            leftfront();
          }else if(leftrightstore == 'r'){
            rightfront();
          }
        }
       
        if (a=='b'){
          if (leftrightstore == 'c'){
            backward();
            delay(100);
          }else if(leftrightstore == 'l'){
            leftback();
            delay(100);
          }else if(leftrightstore == 'r'){
            rightback();
            delay(100);
          }
        }
        
        if (a=='r'){
          leftrightstore = 'r';
        }
        if (a=='l'){
          leftrightstore = 'l';
        }
        if (a=='c'){
          leftrightstore = 'c';
        }
         if (a=='s'){
          stop();
        }
  }else{
    stop();
  }

  void forward()
  {
       digitalWrite(pinI4,LOW);
       digitalWrite(pinI3,LOW);
       digitalWrite(pinI2,HIGH);
       digitalWrite(pinI1,LOW);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  void backward()//
  {
       digitalWrite(pinI4,LOW);
       digitalWrite(pinI3,LOW);
       digitalWrite(pinI2,LOW);
       digitalWrite(pinI1,HIGH);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  void leftfront()//
  {
       digitalWrite(pinI4,HIGH);
       digitalWrite(pinI3,LOW);
       digitalWrite(pinI2,HIGH);
       digitalWrite(pinI1,LOW);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  void leftback()//
  {
       digitalWrite(pinI4,HIGH);
       digitalWrite(pinI3,LOW);
       digitalWrite(pinI2,LOW);
       digitalWrite(pinI1,HIGH);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  
  void rightfront()//
  {
       digitalWrite(pinI4,LOW);
       digitalWrite(pinI3,HIGH);
       digitalWrite(pinI2,HIGH);
       digitalWrite(pinI1,LOW);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  void rightback()//
  {
       digitalWrite(pinI4,LOW);
       digitalWrite(pinI3,HIGH);
       digitalWrite(pinI2,LOW);
       digitalWrite(pinI1,HIGH);
       analogWrite(speedpinA,Aspeed);
       analogWrite(speedpinB,Bspeed);
       delay(movementincrement);
  }
  void stop()//
  {
       digitalWrite(speedpinA,LOW);// Uneanble the pin, to stop the motor. this should be done to avid damaging the motor. 
       digitalWrite(speedpinB,LOW);
       delay(1000);
  }
}
