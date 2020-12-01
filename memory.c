#include "memory.h"

uint8_t bytes[UINT32_MAX];
uint32_t bytesCount;

void initializeBytes(uint32_t memSize){
  for(uint32_t i = 0; i < UINT32_MAX; i++)
    bytes[i] = 0;
}

uint8_t* getByte(uint32_t address){
  return &bytes[address];
}

bool isAligned(uint32_t address, unsigned short size){
  if(size != 1 && size != 2 && size != 4) printf("Illegal memory size!\n");
  uint32_t mask = size-1;
  return (mask & address) == 0;
}

MemParams getAddressParams(uint32_t address){
  MemParams params;
  if(address <= 0x1FFFFFFF){
    params.type = MEM_NORMAL;
    params.XN = false;
    params.shareable = false;
  }else if(address <= 0x3FFFFFFF){
    params.type = MEM_NORMAL;
    params.XN = false;
    params.shareable = false;
  }else if(address <= 0x5FFFFFFF){
    params.type = MEM_DEVICE;
    params.XN = true;
    params.shareable = false;
  }else if(address <= 0x7FFFFFFF){
    params.type = MEM_NORMAL;
    params.XN = false;
    params.shareable = false;
  }else if(address <= 0x9FFFFFFF){
    params.type = MEM_NORMAL;
    params.XN = false;
    params.shareable = false;
  }else if(address <= 0xBFFFFFFF){
    params.type = MEM_DEVICE;
    params.XN = true;
    params.shareable = true;
  }else if(address <= 0xDFFFFFFF){
    params.type = MEM_DEVICE;
    params.XN = true;
    params.shareable = false;
  }else if(address <= 0xE00FFFFF){
    params.type = MEM_STRONGLY_ORDERED;
    params.XN = true;
    params.shareable = false;
  }else{
    params.type = MEM_DEVICE;
    params.XN = true;
    params.shareable = false;
  }
  return params;
}
