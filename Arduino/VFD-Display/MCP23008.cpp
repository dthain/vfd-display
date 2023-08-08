/*
 * VFD Display Controller
 * Copyright (C) 2023 by Douglas Thain 
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 * https://creativecommons.org/licenses/by/4.0/ 
 */

#include "MCP23008.h"

// I/O Direction 1=input, 0=output
#define MCP_IODIR 0x00

// Input Polarity, 0=normal 1=inverted
#define MCP_IPOL 0x01 

// Interrupt-on-change enable, 1=enable
#define MCP_GPINTEN 0x02

// Default comparison value for interrupt on change.
#define MCP_DEFVAL 0x03

// Interrupt control.  0=change 1=compare to DEFVAL.
#define MCP_INTCON 0x04

// I/O Configuration Register.
#define MCP_IOCON 0x05

// 100K Pull-ups on output pins: 1=enabled, 0=disabled
#define MCP_GPPU 0x06

// Interrupt flag register: 1=pin caused interrupt.
#define MCP_INTF 0x07

// Interrupt capture register: stores values from interruipt.
#define MCP_INTCAP 0x08

// GPIO register for read and write.
#define MCP_GPIO 0x09

// Output latch register.
#define MCP_OLAT 0x0A

#define MCP_IOCON_SEQP (1<<<5)  // 0 = sequential operation enabled
#define MCP_IOCON_DISSLW (1<<4) // 0 = slew rate enabled
#define MCP_IOCON_ODR (1<<2) // 1 = open-drain, 0=active driver
#define MCP_IOCON_INTPOL (1<<1) // 1 = INT pin active high, 0=active low

MCP23008::MCP23008()
{
}

void MCP23008::begin( uint8_t addr )
{
  i2c_addr = addr;
  set_direction(0);
  write(0);
}

void MCP23008::set_direction( uint8_t data )
{
  write_reg(MCP_IODIR,data);
}

uint8_t MCP23008::read()
{
  return read_reg(MCP_GPIO);
}

void MCP23008::write( uint8_t data, bool done )
{
  write_reg(MCP_GPIO,data,done);
}


void MCP23008::write_reg( int reg, uint8_t value, bool done )
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission(done);
}

uint8_t MCP23008::read_reg( int reg )
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(i2c_addr,1);
  return Wire.read();
}
