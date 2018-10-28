/*************************************************************
  SAM01 RC Car Connections Testing
 *************************************************************

  This example shows how to use SAM01 Arduino Robotics board
  to control a RC Car.

  This example code is in the public domain.
  https://github.com/wombatics/sam01/tree/master/Arduino/examples

 *************************************************************/
#define MA1 3
#define MA2 5
#define MB1 6
#define MB2 9
#define BOTTOM_LED 13
#define FRONT_LED 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);

  pinMode(BOTTOM_LED, OUTPUT);
  pinMode(FRONT_LED, OUTPUT);
}

void loop() {
  // right
  analogWrite(MA1, 255);
  analogWrite(MA2, 0);
  // forward
  analogWrite(MB1, 150);
  analogWrite(MB2, 0);
  
  delay(3000);
  // left
  analogWrite(MA1, 0);
  analogWrite(MA2, 255);
  // stop
  analogWrite(MB1, 0);
  analogWrite(MB2, 0);
  delay(3000);

  // middle
  analogWrite(MA1, 0);
  analogWrite(MA2, 0);
  // backward
  analogWrite(MB1, 0);
  analogWrite(MB2, 255);
  delay(3000);
  // Testing LEDs
  digitalWrite(BOTTOM_LED, HIGH);
  digitalWrite(FRONT_LED, HIGH);
  delay(100);
  digitalWrite(BOTTOM_LED, LOW);
  digitalWrite(FRONT_LED, LOW);
  delay(100);
  
}
