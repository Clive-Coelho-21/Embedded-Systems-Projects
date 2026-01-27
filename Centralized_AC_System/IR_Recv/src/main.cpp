#include<Arduino.h>
#include<IRremote.h>
#include"Lookup_Table.h"

#define IR_PIN 2  

void setup() 
{
  Serial.begin(115200);
  IrReceiver.begin(IR_PIN,ENABLE_LED_FEEDBACK);
  Serial.println(F("IR Receiver ready..."));
}

void loop() 
{
  bool found = false;
  if(IrReceiver.decode()) 
  {
    if(IrReceiver.decodedIRData.protocol == LG && IrReceiver.decodedIRData.address == 0x88)
    {
      for(int i = 0;i < sizeof(Toggle)/sizeof(Toggle[0]);i++)
      {
        AC_Val1 entry;
        memcpy_P(&entry,&Toggle[i],sizeof(AC_Val1));

        if (entry.command == IrReceiver.decodedIRData.command) 
        {
          Serial.print("Power: ");
          Serial.println(entry.Power);
          Serial.print("Mode: ");
          Serial.println(entry.Mode);
          Serial.print("Temperature Set: ");
          Serial.println(entry.Temp);
          Serial.print("Fan Speed: ");
          Serial.println(entry.Fan_Speed);
          found = true;
          break;
        }
      }
      
      for(int i = 0;i < sizeof(LUT1)/sizeof(LUT1[0]);i++)
      {
        AC_Val1 entry;
        memcpy_P(&entry,&LUT1[i],sizeof(AC_Val1));

        if (entry.command == IrReceiver.decodedIRData.command) 
        {
          Serial.print("Power: ");
          Serial.println(entry.Power);
          Serial.print("Mode: ");
          Serial.println(entry.Mode);
          Serial.print("Temperature Set: ");
          Serial.println(entry.Temp);
          Serial.print("Fan Speed: ");
          Serial.println(entry.Fan_Speed);
          found = true;
          break;
        }
      }

      for(int i = 0;i < sizeof(LUT2)/sizeof(LUT2[0]);i++)
      {
        AC_Val2 entry;
        memcpy_P(&entry,&LUT2[i],sizeof(AC_Val2));

        if (entry.command == IrReceiver.decodedIRData.command) 
        {
          Serial.print("Button Pressed: ");
          Serial.println(entry.str);
          found = true;
          break;
        }
      }

      if(!found)
      {
        Serial.print(F("Unknown code: 0x"));
        Serial.println(IrReceiver.decodedIRData.command,HEX);
      }

      Serial.println("=========================================================================================================================");
    }

    IrReceiver.resume();  
  }
}
