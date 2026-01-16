#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include<Arduino.h>
#include"State.h"

struct AC_Val1
{
  const char* Power;
  const char* Mode; 
  const char* Temp;
  const char* Fan_Speed;
  uint16_t command;
};

struct AC_Val2
{
  const char* str;
  uint16_t command;
};

extern const AC_Val1 Toggle[];
extern const size_t ToggleSize;

extern const AC_Val1 LUT1[];
extern const size_t LUT1Size;

extern const AC_Val2 LUT2[];
extern const size_t LUT2Size;


#endif 