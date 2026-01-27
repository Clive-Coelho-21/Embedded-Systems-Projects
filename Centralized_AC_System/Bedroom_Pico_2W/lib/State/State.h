#ifndef STATE_H
#define STATE_H

#include"Lookup_Table.h"
#include<Arduino.h>

struct AC_State
{
    String Power;
    String Mode;
    String Temp;
    String Fan_Speed;
    bool Swing;
    bool Plasma;
    bool Auto_Clean;
};

bool isStateChanged(const AC_State& S);

extern AC_State currentState;

#endif 