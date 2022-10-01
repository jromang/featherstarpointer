/* 
 * This file is part of the Feather Star Pointer distribution 
 * (https://github.com/jromang/featherstarpointer).
 * Copyright (c) 2022 Jean-Francois ROMANG.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <WS2812FX.h>
#include <BluetoothSerial.h>
#include <SimpleTimer.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#define VBATPIN A13

Adafruit_BNO055 bno = Adafruit_BNO055(55);
WS2812FX ws2812fx = WS2812FX(1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
BluetoothSerial SerialBT;

SimpleTimer batteryTimer(60000);

// Modulo working with negative numbers
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

// Calibration procedure at startup
/* 
  https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/device-calibration
  To generate valid calibration data, the following criteria should be met:

  Gyroscope: The device must be standing still in any position
  Magnetometer: In the past 'figure 8' motions were required in 3 dimensions, but with recent devices
  fast magnetic compensation takes place with sufficient normal movement of the device
  Accelerometer: The BNO055 must be placed in 6 standing positions for +X, -X, +Y, -Y, +Z and -Z.
  This is the most onerous sensor to calibrate, but the best solution to generate the calibration data
  is to find a block of wood or similar object, and place the sensor on each of the 6 'faces' of the block,
  which will help to maintain sensor alignment during the calibration process.  You should still be able to
  get reasonable quality data from the BNO055, however, even if the accelerometer isn't entirely
  or perfectly calibrated.
*/
void calibrate()
{
  Serial.println("Calibration start");
  SerialBT.println("Calibration start");
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;

  ws2812fx.setColor(GRAY);
  ws2812fx.service();

  while(system!=3 || gyro!= 3 || accel!=3 || mag!=3)
  {
    bno.getCalibration(&system, &gyro, &accel, &mag);
    if(system)
    {
      /* Display the individual values */
      Serial.print("Sys:");
      Serial.print(system, DEC);
      Serial.print(" G:");
      Serial.print(gyro, DEC);
      Serial.print(" A:");
      Serial.print(accel, DEC);
      Serial.print(" M:");
      Serial.println(mag, DEC);

      SerialBT.print("Sys:");
      SerialBT.print(system, DEC);
      SerialBT.print(" G:");
      SerialBT.print(gyro, DEC);
      SerialBT.print(" A:");
      SerialBT.print(accel, DEC);
      SerialBT.print(" M:");
      SerialBT.println(mag, DEC);
    }
    delay(200);
  }
  Serial.println("Calibration OK");
  SerialBT.println("Calibration OK");
}

void displayBatteryCharge()
{
      float measuredvbat = analogRead(VBATPIN);
      measuredvbat *= 2;    // we divided by 2, so multiply back
      //measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
      measuredvbat /= 1024; // convert to voltage
      Serial.print("VBat: " ); Serial.println(measuredvbat);
      ws2812fx.setColor(RED);
      if(measuredvbat>3.3)
       ws2812fx.setMode(FX_MODE_STATIC);
      else
       ws2812fx.setMode(FX_MODE_BLINK);     
}

void setup(void) 
{
  // set builtin LED to be an output pin
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  #if defined(NEOPIXEL_POWER)
    // If this board has a power control pin, we must set it to output and high
    // in order to enable the NeoPixels. We put this in an #if defined so it can
    // be reused for other boards without compilation errors
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
  #endif

  // Turn on the I2C power by pulling pin HIGH.
  pinMode(NEOPIXEL_I2C_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_I2C_POWER, HIGH);
  Serial.println("NEOPIXEL_I2C_POWER OK");

  Serial.begin(115200);

  // Wait for Serial port to open
  while (!Serial) {
    delay(10);
  }
  delay(500);
  Serial.println("Feather Star Pointer");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  ws2812fx.init();
  ws2812fx.setBrightness(32);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(BLUE);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();
  ws2812fx.service();

  delay(1000);
  bno.setExtCrystalUse(true);
  delay(1000);
  SerialBT.begin("Feather Star Pointer"); //Bluetooth device name
  calibrate();
  displayBatteryCharge();
}


void loop(void) 
{ 
  if (SerialBT.available()) {
    char command=SerialBT.read();
    char response[30];
    Serial.print(">");
    Serial.println(command);

    if(command=='Q') 
    {
      sensors_event_t event; 
      bno.getEvent(&event);
      
      int az=(int)((event.orientation.x)*8192.0/360.0);
      int alt=(int)((event.orientation.y)*8192.0/360.0);
      az=mod(az,8192)-4096;
      alt=mod(alt,8192)-4096;
      
      sprintf(response, "%i %i\n", az, alt);
      Serial.print("<");
      Serial.print(response);
      Serial.println(event.orientation.x);
      Serial.println(event.orientation.y);
      SerialBT.println(response);
      
    }
    if(command=='H')
    {
      snprintf(response, 20, "%u-%u\n", 8192, 8192);
      Serial.print("<");
      Serial.print(response);
      SerialBT.println(response);
    }
    if(command=='B')
    {
      float measuredvbat = analogRead(VBATPIN);
      measuredvbat *= 2;    // we divided by 2, so multiply back
      //measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
      measuredvbat /= 1024; // convert to voltage
      Serial.print("VBat: " ); Serial.println(measuredvbat);
      SerialBT.print("VBat: " ); SerialBT.println(measuredvbat);
    }
  }

  if(batteryTimer.isReady()) {
    displayBatteryCharge();
    batteryTimer.reset();
  }

  ws2812fx.service();
}
