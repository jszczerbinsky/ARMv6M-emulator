#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum MemType_{
  MEM_NORMAL,
  MEM_DEVICE,
  MEM_STRONGLY_ORDERED
}MemType;

typedef enum MemOperation_{
  MEMOP_READ,
  MEMOP_WRITE
}MemOperation;

typedef struct MemParams_{
  MemType type;
  bool XN;
  bool shareable;
}MemParams;

void initializeBytes();
uint8_t* getByte(uint32_t address);
bool isAligned(uint32_t address, unsigned short size);
MemParams getAddressParams(uint32_t address);

#endif //MEMORY_H
