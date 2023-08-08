/*
 * VFD Display Controller 
 * Copyright (C) 2023 by Douglas Thain
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 * https://creativecommons.org/licenses/by/4.0/ 
 */

#ifndef MCP23008_H
#define MCP23008_H

#include <stdint.h>
#include <Wire.h>

class MCP23008 {
  public:
    MCP23008();
    void begin( uint8_t i2c_addr );
    void set_direction( uint8_t data );
    uint8_t read();
    void write( uint8_t data, bool done=true );
  private:
    uint8_t i2c_addr;
    uint8_t read_reg( int reg );
    void write_reg( int reg, uint8_t value, bool done=true );
};

#endif
