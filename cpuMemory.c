#include "cpu.h"

uint8_t* Mem(uint32_t address){
  return getByte(address);
}

uint8_t* MemA(uint32_t address, unsigned short size){
  if(!isAligned(address, size))
      exceptionEntry(EX_HARD_FAULT);

  return getByte(address);
}
