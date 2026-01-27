#include"Lookup_Table.h"

const AC_Val1 Toggle[] =
{
    {"ON","COOL","24","Medium",0x92},
    {"OFF","--","--","--",0xC005} 
};
const size_t ToggleSize = sizeof(Toggle) / sizeof(Toggle[0]);

const AC_Val1 LUT1[] = 
{
    {"ON","COOL","18","Low",0x830},
    {"ON","COOL","19","Low",0x840},
    {"ON","COOL","20","Low",0x850},
    {"ON","COOL","21","Low",0x860},
    {"ON","COOL","22","Low",0x870},
    {"ON","COOL","23","Low",0x880},
    {"ON","COOL","24","Low",0x890},
    {"ON","COOL","25","Low",0x8A0},
    {"ON","COOL","26","Low",0x8B0},
    {"ON","COOL","27","Low",0x8C0},
    {"ON","COOL","28","Low",0x8D0},
    {"ON","COOL","29","Low",0x8E0},
    {"ON","COOL","30","Low",0x8F0},
    {"ON","COOL","18","Medium",0x832},
    {"ON","COOL","19","Medium",0x842},
    {"ON","COOL","20","Medium",0x852},
    {"ON","COOL","21","Medium",0x862},
    {"ON","COOL","22","Medium",0x872},
    {"ON","COOL","23","Medium",0x882},
    {"ON","COOL","24","Medium",0x892},
    {"ON","COOL","25","Medium",0x8A2},
    {"ON","COOL","26","Medium",0x8B2},
    {"ON","COOL","27","Medium",0x8C2},
    {"ON","COOL","28","Medium",0x8D2},
    {"ON","COOL","29","Medium",0x8E2},
    {"ON","COOL","30","Medium",0x8F2},
    {"ON","COOL","18","High",0x834},
    {"ON","COOL","19","High",0x844},
    {"ON","COOL","20","High",0x854},
    {"ON","COOL","21","High",0x864},
    {"ON","COOL","22","High",0x874},
    {"ON","COOL","23","High",0x884},
    {"ON","COOL","24","High",0x894},
    {"ON","COOL","25","High",0x8A4},
    {"ON","COOL","26","High",0x8B4},
    {"ON","COOL","27","High",0x8C4},
    {"ON","COOL","28","High",0x8D4},
    {"ON","COOL","29","High",0x8E4},
    {"ON","COOL","30","High",0x8F4},
    {"ON","COOL","18","Auto",0x835},
    {"ON","COOL","19","Auto",0x845},
    {"ON","COOL","20","Auto",0x855},
    {"ON","COOL","21","Auto",0x865},
    {"ON","COOL","22","Auto",0x875},
    {"ON","COOL","23","Auto",0x885},
    {"ON","COOL","24","Auto",0x895},
    {"ON","COOL","25","Auto",0x8A5},
    {"ON","COOL","26","Auto",0x8B5},
    {"ON","COOL","27","Auto",0x8C5},
    {"ON","COOL","28","Auto",0x8D5},
    {"ON","COOL","29","Auto",0x8E5},
    {"ON","COOL","30","Auto",0x8F5},
    {"ON","HEAT","2L","--",0xB05},
    {"ON","HEAT","1L","--",0xB15},
    {"ON","HEAT","0","--",0xB25},
    {"ON","HEAT","1H","--",0xB35},
    {"ON","HEAT","2H","--",0xB45},
    {"ON","DRY","--","Low",0x980},
    {"ON","DRY","--","Medium",0x982},
    {"ON","DRY","--","High",0x984},
    {"ON","DRY","--","Auto",0x985},
    {"ON","FAN","--","Low",0xA30},
    {"ON","FAN","--","Medium",0xA32},
    {"ON","FAN","--","High",0xA34},
    {"ON","FAN","--","Auto",0xA35}
};
const size_t LUT1Size = sizeof(LUT1) / sizeof(LUT1[0]);  

const AC_Val2 LUT2[] = 
{
    {"Swing ON",0x1000},
    {"Swing OFF",0x1300},
    {"Plasma ON",0xC000},
    {"Plasma OFF",0xC008},
    {"Start Autoclean",0xC00C},
    {"Stop Autoclean",0xC00B}
};
const size_t LUT2Size = sizeof(LUT2) / sizeof(LUT2[0]);