/*
 * VFD Display Controller 
 * Copyright (C) 2023 by Douglas Thain
 * This work is licensed under a Creative Commons Attribution 4.0 International License.
 * https://creativecommons.org/licenses/by/4.0/ 
 */

#include "VFDController.h"
#include "Arduino.h"

void VFDController::begin()
{
  for(int i=0;i<VFD_NDIGITS;i++) write_digit_raw(i,0);
  current_digit = 0;

  for(int i=0;i<VFD_NBANKS;i++) {
    bank[i].begin(0x20+i);
    bank[i].set_direction(0);
  }
  show_digit(0);
}

void VFDController::show_digit( int d )
{
  uint16_t digit_mask = (1<<d);
  uint16_t data = digit_data[d];
  uint8_t  data_high = data>>8;
  uint8_t  digit_mask_high = digit_mask>>8;

  // First disable all grids
  bank[0].write(0,false);
  bank[3].write(0,true);

  // Then write the desired segments.
  bank[1].write(data,false);
  bank[2].write(data_high,true);

  // Then re-enable the proper grid.
  bank[0].write(digit_mask_high,false);
  bank[3].write(digit_mask,true);
}

void VFDController::write_digit_raw( int d, uint16_t data )
{
  digit_data[d] = data;
}

void VFDController::next_digit()
{
  current_digit++;
  if(current_digit>=VFD_NDIGITS) current_digit = 0;
  show_digit(current_digit);
}

/*
 --- ---
|\  |  /|
| \ | / |
 --- ---
| / | \ |
|/  |  \|
 --- ---
 */

/*
 HHH GGG
AI  N  LF
A I N L F
 PPP OOO
B J M K E
BJ  M  KE
 CCC DDD
*/

static uint16_t symbol_font[] =
{
//PONMLKJIHGFEDCBA
0b0000000000000000, // Space
0b0010000000001100, // !
0b0010000000100000, // ""
0b1100000011111111, // #
0b1111000011011101, // $
0b1111101010011001, // %
0b1111111111111111, // & FIXME
0b0000000000100000, // '
0b0000110000000000, // (
0b0000001100000000, // )
0b1111111100000000, // *
0b1111000000000000, // +
0b0000001000000000, // ,
0b1100000000000000, // -
0b0000000000000100, // .
0b0000101000000000, // /
0b0000000011111111, // 0
0b0011000010001100, // 1
0b1100000011101110, // 2
0b1100000011111100, // 3
0b1100000000110001, // 4
0b1100000011011101, // 5
0b1100000011011111, // 6
0b0000101011000000, // 7 
0b1100000011111111, // 8
0b1100000011111101, // 9
//:
//;
//<
//=
//>
//?
//@
};

static uint16_t uppercase_font[] =
{
//PONMLKJIHGFEDCBA
0b1100000011110011, // A
0b0111000011111100, // B
0b0000000011001111, // C
0b0011000011111100, // D (needs work)
0b1100000011001111, // E
0b1100000011000011, // F
0b0100000011011111, // G
0b1100000000110011, // H
0b0011000011001100, // I
0b0011000011000100, // J
0b0011110000000000, // K
0b0000000000001111, // L
0b0000100100110011, // M
0b0000010100110011, // N
0b0000000011111111, // O
0b1100000011100011, // P
0b0000010011111111, // Q
0b1100010011100011, // R
0b1100000011011101, // S
0b0011000011000000, // T
0b0000000000111111, // U
0b0000101000000011, // V
0b0000011000110011, // W
0b0000111100000000, // X
0b0001100100000000, // Y
0b0000101011001100, // Z
};

void VFDController::write_digit( int d, char c )
{
  if(c>='A' && c<='Z') {
    write_digit_raw(d,uppercase_font[c-'A']);
  } else if(c>='a' && c<='z') {
    write_digit_raw(d,uppercase_font[c-'a']);
  } else if(c>=' ' && c<='9') {
    write_digit_raw(d,symbol_font[c-' ']);    
  } else {
    write_digit_raw(d,0);
  }
}

int newline_pending = 1;

void VFDController::write( char c )
{
  if(position>=16) position=0;
  if(c==13) {
    newline_pending = 1;
  } else if(c==10) {
    newline_pending = 1;
  } else {
    if(newline_pending) {
       clear();
       position = 0;
       newline_pending = 0;
    }
    write_digit(position++,c);
  }
}

void VFDController::write( const char *s )
{
  while(*s) write(*s++);
}

void VFDController::clear()
{
  for(int i=0;i<16;i++) write_digit(i,' ');
  position = 0;
}

void VFDController::rotateLeft()
{
  digit_data[15] = digit_data[0];
  for(int i=0;i<15;i++) digit_data[i] = digit_data[i+1];
}
