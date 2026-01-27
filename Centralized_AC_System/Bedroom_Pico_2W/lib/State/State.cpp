#include<Arduino.h>
#include"State.h"
#include"Lookup_Table.h"

bool isStateChanged(const AC_State& S)
{
    if(S.Power != currentState.Power || S.Mode != currentState.Mode || S.Temp != currentState.Temp || S.Fan_Speed != currentState.Fan_Speed || 
        S.Swing != currentState.Swing || S.Plasma != currentState.Plasma || S.Auto_Clean != currentState.Auto_Clean)
        return true;
    return false;
}
