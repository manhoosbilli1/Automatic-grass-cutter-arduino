#include <Arduino.h>
#include <Ultrasonic.h>
#include "Servo.h"
#include "SoftwareSerial.h"
Ultrasonic ultrasonic1(5, 4); // An ultrasonic sensor HC-04
SoftwareSerial s(2, 8);       //2 rx 8 tx
Servo horServo;               // create servo object to control a servo
Servo verServo;
#define leftm1 13 //need to change these pins as they are unreliable at startup
#define leftm2 12
#define rightm1 11
#define rightm2 10

#define LDRBOTRIGHT A0
#define LDRTOPLEFT A1
#define LDRBOTLEFT A2
#define LDRTOPRIGHT A3

#define cutterPin 6
#define relay2 7

int ldrTopLeft;
int ldrTopRight;
int ldrBotLeft;
int ldrBotRight;

int ldrTopLeftDef;
int ldrTopRightdef;
int ldrBotRightdef;
int ldrBotLeftDef;

char result;
bool automaticState = false;
int turnDelay = 1000; //will change
bool solarTrackingState = false;
bool makeCorrection = false;
//horizontal servo positions
int horAngle;
int horInit;
int horPos1;
int horPos2;

//horizontal servo positions
int verAngle;
int verInit = 0;
int verPos1 = 150;
int verPos2 = 0;
int vertDiff;
int absVertDiff;
int absHorDiff;
int horDiff;
//-----//
#define forward 1
#define reverse 2
#define STOP 3
#define automaticOn 4
#define automaticOff 5
#define incHorServoAngle 6
#define decHorServoAngle 7
#define incVerServoAngle 8
#define decVerServoAngle 9
#define cutterOn 10
#define cutterOff 11

void readSensors();
void obstacleAvoidance();
void solarTrackerHandler();

void setup()
{
  Serial.begin(9600);
  s.begin(9600);
  //horServo.attach(9);
  verServo.attach(3);
  verServo.write(90); //go to default pos
  horServo.write(90); //go to default pos
  pinMode(leftm1, OUTPUT);
  pinMode(leftm2, OUTPUT);
  pinMode(rightm1, OUTPUT);
  pinMode(rightm2, OUTPUT);
  pinMode(LDRTOPLEFT, INPUT);
  pinMode(LDRTOPRIGHT, INPUT);
  pinMode(LDRBOTLEFT, INPUT);
  pinMode(LDRBOTRIGHT, INPUT);
  pinMode(cutterPin, OUTPUT);
  digitalWrite(cutterPin, HIGH);
  digitalWrite(rightm1, LOW);
  digitalWrite(rightm2, LOW);
  digitalWrite(leftm1, LOW);
  digitalWrite(leftm2, LOW);
}

void loop()
{
  solarTrackerHandler();
  /*
  ultrasonic1.read(); // Prints the distance on the default unit (centimeters)
  if (solarTrackingState == true)
  {
    solarTrackerHandler();
  }

  if (s.available() > 0)
  {
    result = s.read();
    Serial.println(result);
    if (automaticState == true)
    {
      if (result != 'c' || result != 'd') //if result is not automatic on or if result is not automatic off then turn off automatic mode
      {
        automaticState = false; //if recieved char is something other than automatic then turn it off
      }
    }
  }

  switch (result)
  {
  case 'b':
    digitalWrite(leftm1, HIGH);
    digitalWrite(leftm2, LOW);
    digitalWrite(rightm1, HIGH);
    digitalWrite(rightm2, LOW);
    break;

  case 'f':
    digitalWrite(leftm1, LOW);
    digitalWrite(leftm2, HIGH);
    digitalWrite(rightm1, LOW);
    digitalWrite(rightm2, HIGH);
    break;

  case 's':
    digitalWrite(leftm1, LOW);
    digitalWrite(leftm2, LOW);
    digitalWrite(rightm1, LOW);
    digitalWrite(rightm2, LOW);
    break;

  case 'c':
    automaticState = true;
    digitalWrite(LED_BUILTIN, HIGH);

    break;

  case 'd':
    automaticState = false;
    digitalWrite(LED_BUILTIN, LOW);
    break;

  case 'e':
    horAngle = horServo.read();
    horAngle = horAngle + 10;
    horServo.write(horAngle);
    break;

  case 'a':
    horAngle = horServo.read();
    horAngle = horAngle - 10;
    horServo.write(horAngle);
    break;

  case 'g':
    verAngle = verServo.read();
    verAngle = verAngle + 10;
    verServo.write(verAngle);
    break;

  case 'h': //decrease servo angle by 5
    verAngle = verServo.read();
    verAngle = verAngle - 10;
    verServo.write(verAngle);
    break;

  case 'i': //turn cutter on
    digitalWrite(cutterPin, LOW);
    break;

  case 'j': //turn cutter off
    digitalWrite(cutterPin, HIGH);
    break;

  case 'k': //go left
    digitalWrite(leftm1, HIGH);
    digitalWrite(leftm2, LOW);
    digitalWrite(rightm1, LOW);
    digitalWrite(rightm2, HIGH);
    break;

  case 'l': //go right
    digitalWrite(leftm1, LOW);
    digitalWrite(leftm2, HIGH);
    digitalWrite(rightm1, HIGH);
    digitalWrite(rightm2, LOW);
    break;

  case 'm': //solar tracking on
    solarTrackingState = true;
    break;

  case 'n': //solar tracking off
    solarTrackingState = false;
    break;
  }
  result = NULL;

  if (automaticState == true)
  {
    solarTrackerHandler();
    if (ultrasonic1.read() <= 15) //object detected
    {
      //stop the motors
      digitalWrite(leftm1, LOW);
      digitalWrite(leftm2, LOW);
      digitalWrite(rightm1, LOW);
      digitalWrite(rightm2, LOW);
      delay(500); //stop delay

      //turn left
      //left side forward right side backward
      digitalWrite(leftm1, HIGH);
      digitalWrite(leftm2, LOW);
      digitalWrite(rightm1, LOW);
      digitalWrite(rightm2, HIGH);
      delay(turnDelay); //set delay based on experiment.

      if (ultrasonic1.read() >= 15)
      {
        //do nothing.
      }
      else
      {
        //go opposite or 180 degrees. so opposite motion but for longer delay
        digitalWrite(leftm1, LOW);
        digitalWrite(leftm2, HIGH);
        digitalWrite(rightm1, HIGH);
        digitalWrite(rightm2, LOW);
        delay((turnDelay * 2)); //will take 2x time to reach 180 degree
      }
    }
    else
    {
      digitalWrite(leftm1, LOW);
      digitalWrite(leftm2, HIGH);
      digitalWrite(rightm1, LOW);
      digitalWrite(rightm2, HIGH);
    }
  }
  */
}

void readSensors()
{
  int temp;
  int value = 0;
  temp = analogRead(LDRTOPLEFT);
  for (int i = 0; i < 10; i++)
  {
    value += analogRead(LDRTOPLEFT);
  }
  temp = analogRead(LDRTOPRIGHT);

  ldrTopLeft = value / 10;
  value = 0;
  for (int i = 0; i < 10; i++)
  {
    value += analogRead(LDRTOPRIGHT);
  }
  ldrTopRight = value / 10;
  value = 0;
  ldrBotLeft = analogRead(LDRBOTLEFT);
  for (int i = 0; i < 10; i++)
  {
    value += analogRead(LDRBOTLEFT);
  }
  ldrBotLeft = value / 10;
  value = 0;
  temp = analogRead(LDRBOTRIGHT);
  for (int i = 0; i < 10; i++)
  {
    value += analogRead(LDRBOTRIGHT);
  }
  ldrBotRight = value / 10;
  value = 0;
}

void solarTrackerHandler()
{
  readSensors();
  // do rest below

  int topRegion = (ldrTopRight + ldrTopLeft) / 2; //taking average of two
  int botRegion = (ldrBotRight + ldrBotLeft) / 2;
  int leftRegion = (ldrTopLeft + ldrBotLeft) / 2;
  int rightRegion = (ldrTopRight + ldrBotRight) / 2;

  Serial.print("topLeft:");
  Serial.print(ldrTopLeft);
  Serial.print(" topRight:");
  Serial.print(ldrTopRight);
  Serial.print(" botLeft:");
  Serial.print(ldrBotLeft);
  Serial.print(" botRight:");
  Serial.print(ldrBotRight);
  //difference of 300 when one side is fully  lit and the other is dark.. same for both regions

  vertDiff = botRegion - topRegion; //if difference is positive it will go upward other wise downward
  horDiff = leftRegion - rightRegion;
  absVertDiff = abs(vertDiff);
  absHorDiff = abs(horDiff);

  //vertical controller

  if (absVertDiff > 0 && absVertDiff < 50)
  {
    //do nothing
  }
  else if (vertDiff > 0 && verAngle <= 178)
  {
    verServo.read();
    verAngle = verAngle + 1;
    verServo.write(verAngle);
    delay(10);
  }
  else if (vertDiff < 0 && verAngle >= 0)
  {
    verAngle = verServo.read();
    verAngle = verAngle - 1;
    verServo.write(verAngle);
    delay(10);
  }

  //horizontal controller

  if (absVertDiff > 0 && absVertDiff < 50)
  {
    //do nothing
  }
  else if (vertDiff > 0 && verAngle <= 178)
  {
    verServo.read();
    verAngle = verAngle + 5;
    verServo.write(verAngle);
    delay(2);
  }
  else if (vertDiff < 0 && verAngle >= 0)
  {
    verAngle = verServo.read();
    verAngle = verAngle - 5;
    verServo.write(verAngle);
    delay(2);
  }

  Serial.print(" servoAngle: ");
  Serial.print(verAngle);
  Serial.print(" TopRegion: ");
  Serial.print(topRegion);
  Serial.print(" bottomRegion: ");
  Serial.print(botRegion);
}
