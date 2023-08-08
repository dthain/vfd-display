/*
 * VFD Display Controller 
 * Copyright (C) 2023 by Douglas Thain
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 * https://creativecommons.org/licenses/by/4.0/ 
 */

#ifndef VFD_CONTROLLER_H
#define VFD_CONTROLLER_H

#include "MCP23008.h"

#define VFD_NDIGITS 16
#define VFD_NSEGMENTS 16
#define VFD_NBANKS 4

class VFDController {
public:
  void begin();
  void show_digit( int digit );
  void next_digit();
  void write_digit_raw( int digit, uint16_t data);
  void write_digit( int digit, char c );
  void write( char c );
  void write( const char *str );
  void clear();
  void rotateLeft();
    
private:
  MCP23008 bank[VFD_NBANKS];
  uint16_t digit_data[VFD_NDIGITS] = {0};
  int current_digit;
  int position;
};

#endif
