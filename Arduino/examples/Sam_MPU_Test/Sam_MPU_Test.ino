/*
 Wombatics SAM01 MPU Test

 
 created 
 modified 08 Aug 2018
 by Thomas Chan

 This example code is in the public domain.
 */
#include <SoftwareSerial.h>
#include "mpu.h"

#define BUZZER 12
SoftwareSerial BTserial(10,9);  

void setup() 
{
  int error;
  uint8_t c;
  
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600); //change to fit your ble initial baud_rate
  BTserial.begin(9600);
  // Initialize the 'Wire' class for the I2C-bus.
  Wire.begin();
 
  delay(100);

  //Setup MPU
    // default at power-up:
  //    Gyro at 250 degrees second
  //    Acceleration at 2g
  //    Clock source at internal 8MHz
  //    The device is in sleep mode.
  //
   error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
  Serial.print(F("WHO_AM_I : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  // According to the datasheet, the 'sleep' bit
  // should read a '1'.
  // That bit has to be cleared, since the sensor
  // is in sleep mode at power-up.
  error = MPU6050_read (MPU6050_PWR_MGMT_1, &c, 1);
  Serial.print(F("PWR_MGMT_1 : "));
  Serial.print(c,HEX);
  Serial.print(F(", error = "));
  Serial.println(error,DEC);

  // Clear the 'sleep' bit to start the sensor.
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
  //end MPU
  delay(100);
  
  
}

void loop() 
{

  mpuTest();
  
  delay(1000);
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

void mpuTest()
{

  int error;
  double dT;
  accel_t_gyro_union accel_t_gyro;

 Serial.println(F(""));
  Serial.println(F("MPU-6050"));
 
  // Read the raw values.
  // Read 14 bytes at once,
  // containing acceleration, temperature and gyro.
  // With the default settings of the MPU-6050,
  // there is no filter enabled, and the values
  // are not very stable.
  error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));
  Serial.print(F("Read accel, temp and gyro, error = "));
  Serial.println(error,DEC);
 
 
  // Swap all high and low bytes.
  // After this, the registers values are swapped,
  // so the structure name like x_accel_l does no
  // longer contain the lower byte.
  uint8_t swap;
  #define SWAP(x,y) swap = x; x = y; y = swap
 
  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);
 
 
  // Print the raw acceleration values
 
  Serial.print(F("accel x,y,z: "));
  Serial.print(accel_t_gyro.value.x_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_accel, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_accel, DEC);
  Serial.println(F(""));
 
 
  // The temperature sensor is -40 to +85 degrees Celsius.
  // It is a signed integer.
  // According to the datasheet:
  //   340 per degrees Celsius, -512 at 35 degrees.
  // At 0 degrees: -512 - (340 * 35) = -12412
 
  Serial.print(F("temperature: "));
  dT = ( (double) accel_t_gyro.value.temperature + 12412.0) / 340.0;
  Serial.print(dT, 3);
  Serial.print(F(" degrees Celsius"));
  Serial.println(F(""));
 
 
  // Print the raw gyro values.
 
  Serial.print(F("gyro x,y,z : "));
  Serial.print(accel_t_gyro.value.x_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.y_gyro, DEC);
  Serial.print(F(", "));
  Serial.print(accel_t_gyro.value.z_gyro, DEC);
  Serial.print(F(", "));
  Serial.println(F(""));
 
  
}

