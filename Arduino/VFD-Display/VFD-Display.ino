/*
 * VFD Display Controller
 * Copyright (C) 2023 by Douglas Thain
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 * https://creativecommons.org/licenses/by/4.0/ 
 */
 
#include "Wire.h"
#include "VFDController.h"

VFDController control;

void setup()
{
  Wire.begin();

  // Set LED high briefly.
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  // Hold display reset line low briefly.
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);

  // Initialize the VFD display.
  control.begin();
  control.clear();

  // Wait one second before using the serial port,
  // to avoid difficulty with programming via bootloader.
  delay(1000);

  Serial.begin(9600);
  Serial.print("VFD Console Ready\n");

  control.write("YOUR NAME HERE\n");
  
  // LED back off to show reset complete.
  digitalWrite(13,LOW);
}

/*
 * In the main loop, rotate the next digit every 1ms.
 * If there is data available on the serial port, write it to the display.
 */

void loop()
{
  control.next_digit();
  while(Serial.available()) {
    char c = Serial.read();
    control.write(c);
  }
  delayMicroseconds(1);
}
