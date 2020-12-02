#include "cpu.h"

Mode actualMode = THREAD_MODE;
Registers reg;

bool flag_C = false;        // Carry
bool flag_V = false;        // Overflow
bool flag_N = false;        // Negative
bool flag_Z = false;        // Zero


void initializeRegs(){
  for(uint8_t i = 0; i < 13; i++)
    reg.GPR[i] = 0;
  reg.SP_main = 0;
  reg.SP_process = 0;
  reg.LR = 0;
  reg.PC = 0;
  reg.CONTROL_SPSEL = false;
  reg.PM = false;
}

uint32_t alignInstruction(uint32_t address){
  uint32_t newAddr = address & (0 << 0);  
  return newAddr;
}

void branchWritePC(uint32_t address){
  reg.PC = alignInstruction(address);
}

void blxWritePC(uint32_t address){
     if((~(address >> 0)) & 1){                    // Address not aligned
      exceptionEntry(getExNum(EX_HARD_FAULT));
    }
     branchWritePC(address);                       // It will align it before writing to PC
}

void bxWritePc(uint32_t address){
  if(actualMode == HANDLER_MODE){
    bool startsWith1111 = true;
    for(short i = 28; i < 32; i++)
      if((~(address >> i)) & 1) startsWith1111 = false;

    if(startsWith1111){
      exceptionReturn(address); 
    }
  }
  else blxWritePC(address);
}

