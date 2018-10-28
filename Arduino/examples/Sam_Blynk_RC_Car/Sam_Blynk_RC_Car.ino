/*************************************************************
  SAM01 RC Car with Blynk.
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet / 
  WiFi / Bluetooth.
  
 *************************************************************

  This example shows how to use SAM01 Arduino Robotics board
  to connect a RC Car to Blynk.

  NOTE: BLE support is in beta for Blynk. Too much data will
  cause errors in BLE with Blynk.

  This example code is in the public domain.
  https://github.com/wombatics/sam01/tree/master/Arduino/examples

 *************************************************************/
#define MA1 3
#define MA2 5
#define MB1 6
#define MB2 9
#define BOTTOM_LED 13
#define FRONT_LED 10

//#define BLYNK_USE_DIRECT_CONNECT

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial BLESerial(10, 9); // RX, TX

#define BLYNK_PRINT Serial

#include <BlynkSimpleSerialBLE.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "yourAuthToken";
bool turbo;

void forward(int speed)
{
  analogWrite(MB1, speed);
  analogWrite(MB2, 0);
 // Serial.println("Speed: ");
 // Serial.println(speed);
}

void backward(int speed)
{
  analogWrite(MB1, 0);
  analogWrite(MB2, -speed);
  // Serial.println("back speed: ");
  // Serial.println(speed);
}

void right(int speed)
{
  analogWrite(MA1, speed);
  analogWrite(MA2, 0);
}

void left(int speed)
{
  analogWrite(MA1, 0);
  analogWrite(MA2, speed);
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println(pinValue);

  if(pinValue >= 0)
  {
    if(turbo)
      forward(pinValue);
    else if (pinValue == 0)
      forward(0);
    else
      forward(pinValue * 0.7 + 30);
  }
  else
  {
    backward(pinValue * 0.7 - 30);
  }
  
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  //Serial.print("Left ");
  //Serial.println(pinValue);
  if(pinValue)
    left(255);
  else
    left(0);
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  //Serial.print("Right ");
  //Serial.println(pinValue);
  if(pinValue)
    right(255);
  else
    right(0);
} 

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if(pinValue)
    turbo = true;
  else
    turbo = false;
  
}

  
void setup()
{
  // Debug console
  Serial.begin(115200);

  Serial.println("Waiting for connections...");

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  BLESerial.begin(9600);
  
  Blynk.begin(BLESerial, auth);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);

  forward(0);

  turbo = false;
}

void loop()
{
  Blynk.run();
  
}

