//-----------------------------------------------------------------
//-- SAM01 BLE Remote Control for Otto 
//-----------------------------------------------------------------
#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
#include <SoftwareSerial.h>

#define SAM01_Buzzer 12

/*
                 --------------- 
                |     O   O     |
                |---------------|
RIGHT LEG 3==>  |               | <== LEFT LEG 2
                 --------------- 
                    ||     ||
RIGHT FOOT 5==>   -----   ------  <== LEFT FOOT 4
                 |-----   ------|
*/

// Start with PIN 3, as PIN 2 is used for MPU6050 on SAM01
#define PIN_LEFT_LEG   3   
#define PIN_RIGHT_LEG  4  
#define PIN_LEFT_FOOT  5  
#define PIN_RIGHT_FOOT 6 
 

#define TRIM_LEFT_LEG   0 
#define TRIM_RIGHT_LEG  0
#define TRIM_LEFT_FOOT  0 
#define TRIM_RIGHT_FOOT 0

Otto Otto;  //This is Otto!

// BLE module is connect pin 10 & 9 on SAM01 
SoftwareSerial BTserial(10,9);  

void setup()  
{

  Serial.begin(9600);
  BTserial.begin(9600);   // Setup the serial port at 9600 bps. This is the BLE Shield default baud rate.
 
  Serial.println("Hello");

   //Set the servo pins
  Otto.init(PIN_LEFT_LEG,PIN_RIGHT_LEG,PIN_LEFT_FOOT,PIN_RIGHT_FOOT,true,PIN_NoiseSensor,SAM01_Buzzer);
  Otto.setTrims(TRIM_LEFT_LEG,TRIM_RIGHT_LEG, TRIM_LEFT_FOOT, TRIM_RIGHT_FOOT);

  Otto.sing(S_connection); // Otto wake up!
  Otto.home();

}


void loop()  // Continuous loop
{
    char c = ' ';
   
    if (BTserial.available())
    {  
        
        c = BTserial.read();
        Serial.write(c);

        
        switch(c)
        {
          case '1':
            Otto.sing(S_happy);
            break;
 
          case '2':
            Otto.sing(S_superHappy);
            break;

          case '3':
            Otto.sing(S_OhOoh);
            break;
            
          case 'H':
            Otto.home();
            break;   
                          
          case 'f':
            move_forward(1,1000);
            break;
            
          case 'b':
            move_backward(1,1000);
            break;
            
          case 'l':
            move_turn_left(1,1000);
            break;
            
          case 'r':
            move_turn_right(1,1000);
            break;

            
          default:
            break;
        }
      Serial.println("");    
    }
    
  

}


void move_forward(int time, int speed)
{
    Serial.println("forward");
    
    Otto.walk(time, speed, FORWARD);
    
    delay(time);
}

void move_backward(int time, int speed)
{

    Serial.println("backward");

    Otto.walk(time, speed, BACKWARD);


    delay(time);
}

void move_turn_right(int time, int speed)
{
    Serial.println("right");

    Otto.turn(time,speed,RIGHT); 
    delay(time);
}

void move_turn_left(int time, int speed)
{
    Serial.println("left");
    Otto.turn(time,speed,LEFT); 
    delay(time);
}


