#include <Servo.h>

Servo dispenseServo;
Servo tiltServo;

char inByte;

/* Pin assignments */
int motorPin = 2;
int dispenseServoPin = 5;
int tiltServoPin = 6;

/* Delays */
int motorOnDelay = 300; // time for the motors to power up before launching
int motorOffDelay = 150; // time to enable the motors for in ms
int dispenseDelay = 140; // time before returning the dispense servo to its original position in ms

/* Servo angles */
int dispenseServoDefaultAngle = 90;
int dispenseServoActivatedAngle = 50;
int tiltServoDefaultAngle = 150;
int tiltServoMaxAngle = 100;
int tiltServoCurrentAngle;

void setup()
{
  Serial.begin(9600);
  
  dispenseServo.attach(dispenseServoPin);
  tiltServo.attach(tiltServoPin);
  
  dispenseServo.write(dispenseServoDefaultAngle);
  tiltServo.write(tiltServoDefaultAngle);
  
  tiltServoCurrentAngle = tiltServoDefaultAngle;
  
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH);
}
 
void loop() 
{
  if(Serial.available() > 0)
  {
    inByte = Serial.read();
  }
  
  if(inByte == 'f')
  {
    fire();
    inByte = 'v';
  }
  else if(inByte == 'u')
  {
    tiltUp();
    inByte = 'v';
  }
  else if(inByte == 'd')
  {
    tiltDown();
    inByte = 'v';
  } 
}

void fire()
{
  digitalWrite(motorPin, LOW);
  delay(motorOnDelay);
  dispense();
  delay(motorOffDelay);
  digitalWrite(motorPin, HIGH);
}

void dispense()
{
  dispenseServo.write(dispenseServoActivatedAngle);
  delay(dispenseDelay);
  dispenseServo.write(dispenseServoDefaultAngle);
}

void tiltUp()
{
  if(tiltServoCurrentAngle > tiltServoMaxAngle) {
    tiltServoCurrentAngle -= 2;
    tiltServo.write(tiltServoCurrentAngle);
  }
  Serial.println(tiltServoCurrentAngle);
}

void tiltDown()
{
  if(tiltServoCurrentAngle < tiltServoDefaultAngle) {
    tiltServoCurrentAngle += 2;
    tiltServo.write(tiltServoCurrentAngle);
  }
  Serial.println(tiltServoCurrentAngle);
}


