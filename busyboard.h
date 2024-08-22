#pragma once
#include "publishedVar.h"

namespace bb
{
    char rxByte;
    char prevByte = '\0';
    uint8_t rxIndex = 0;
    enum : byte {RESET,TYPE,MSG};
    uint8_t state = RESET;
    uint8_t activeTopic = -1;
    
    bool receiveMessage(uint8_t &topic, char * rxBytes)
    {
        bool newMessage = false;
        if(Serial.available())
        {
          rxByte = Serial.read();
          if(prevByte == '$' and rxByte == '{')
          {
            state = TYPE;
            rxIndex = 0;
            rxBytes[0] = '\0';
          }
          else if(rxByte == '}')
          {
            state = RESET;
            rxBytes[rxIndex] = '\0';
            topic = activeTopic;
            rxIndex = 0;
            newMessage = true;
          }
          else if(state == TYPE)
          {
            if(isDigit(rxByte))
            {
              activeTopic = String(rxByte).toInt();
              state = MSG;
            }
            else
              state = RESET;
          }
          else if(state == MSG)
          {
            if(rxByte != ',')
            {
              rxBytes[rxIndex] = rxByte;
              rxIndex += 1;
            }
          }
        }
        prevByte = rxByte;
        return newMessage;
    }
}
