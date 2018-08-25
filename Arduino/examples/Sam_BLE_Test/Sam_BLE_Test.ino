/*
  Wombatics SAM01 BLE Test

 Receives from the bluetooth software serial, sends to hardware serial.
 
 * RX is digital pin 10 
 * TX is digital pin 9 

 created 
 modified 08 Aug 2018
 by Thomas Chan

 This example code is in the public domain.
 */
 
#include <SoftwareSerial.h>

#define BUZZER 12

SoftwareSerial BTserial(10,9);  


void setup() 
{
  int error;
  uint8_t c;
  
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600); //change to fit your ble initial baud_rate
  BTserial.begin(9600);
  
  Serial.println("\nHello, This is SAM01!");
  startupTone();
}

void loop() {
 
  while (BTserial.available()) 
  {     
    tone(BUZZER, 200, 200);
    Serial.write(BTserial.read());    
  }

  while (Serial.available()) 
  {     
    tone(BUZZER, 100, 200);
    BTserial.write(Serial.read());    
  }

  
  delay(100);
}

void startupTone()
{
  tone(BUZZER, 3520,100); //A
  delay(100);
  tone(BUZZER, 3136,100); //G
  delay(100);
  tone(BUZZER, 2637,100); //E
  delay(100);
  tone(BUZZER, 2093,100); //C
  delay(100);
}
