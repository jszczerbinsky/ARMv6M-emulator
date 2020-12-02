#include "memory.h"
#include "cpuTypedefs.h"

Mode actualMode = THREAD_MODE;
Registers reg;

bool flag_C = false;        // Carry
bool flag_V = false;        // Overflow
bool flag_N = false;        // Negative
bool flag_Z = false;        // Zero

void blxWritePC(uint32_t address);
void bxWritePC(uint32_t address);

uint8_t* Mem(uint32_t address);
uint8_t* MemA(uint32_t address, unsigned short size);

uint8_t getExNum(Exception ex);
Exception getExceptionFromExNum(uint8_t num);
void exceptionEntry(Exception ex);
void exceptionReturn(uint32_t eReturn);
