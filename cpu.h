#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "cpuTypedefs.h"

extern Mode actualMode;
extern Registers reg;

extern bool flag_C;        // Carry
extern bool flag_V;        // Overflow
extern bool flag_N;        // Negative
extern bool flag_Z;        // Zero

void initializeRegs();
void blxWritePC(uint32_t address);
void bxWritePC(uint32_t address);

void executeNextInstruction();

uint8_t* Mem(uint32_t address);
uint8_t* MemA(uint32_t address, unsigned short size);

uint8_t getExNum(Exception ex);
Exception getExceptionFromExNum(uint8_t num);
void exceptionEntry(Exception ex);
void exceptionReturn(uint32_t eReturn);

#endif //CPU_H
