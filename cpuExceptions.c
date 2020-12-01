#include "cpu.h"

bool activeExceptions[UINT8_MAX];

Exception getExceptionFromExNum(uint8_t num){
  if(num == 1) return EX_RESET;
  if(num == 2) return EX_NMI;
  if(num == 3) return EX_HARD_FAULT;
  if(num == 11) return EX_SV_CALL;
  if(num == 14) return EX_PEND_SV;
  if(num == 15) return EX_SYS_TICK;
  if(num >= 16) return EX_EXTERNAL_INPUT;
  return EX_RESERVED; 
}

uint8_t getExNum(Exception ex){
  if(ex == EX_RESET) return 1;
  if(ex == EX_NMI) return 2;
  if(ex == EX_HARD_FAULT) return 3;
  if(ex == EX_SV_CALL) return 11;
  if(ex == EX_PEND_SV) return 14;
  if(ex == EX_SYS_TICK) return 15;
  if(ex == EX_EXTERNAL_INPUT) return 16;
  return 4; 
}

void exceptionTaken(uint8_t exNum){
  for(short i = 0; i < 4; i++){
    reg.GPR[i] = 0;
  }
  reg.GPR[12] = 0;
  
  flag_C = false;
  flag_V = false;
  flag_Z = false;
  flag_N = false;

  actualMode = HANDLER_MODE;

  reg.IPSR = exNum;
  reg.CONTROL_SPSEL = false;
  activeExceptions[exNum] = true; 
  
  uint32_t vtorVal = *((uint32_t*)Mem(SCS_VTOR));
  uint32_t start = *MemA(vtorVal+4*exNum,4);
  blxWritePC(start); 
}

void popStack(uint32_t address, uint8_t ReturningExNum){
  reg.GPR[0] = *((uint32_t*)MemA(address, 4));
  reg.GPR[1] = *((uint32_t*)MemA(address+4, 4));
  reg.GPR[2] = *((uint32_t*)MemA(address+8, 4));
  reg.GPR[3] = *((uint32_t*)MemA(address+12, 4));
  reg.GPR[12] = *((uint32_t*)MemA(address+16, 4));
  reg.LR = *((uint32_t*)MemA(address+20, 4));
  reg.PC = *((uint32_t*)MemA(address+24, 4));
  uint32_t psr = *((uint32_t*)MemA(address+24, 4));
  bool ptrAlign = (psr >> 9) & 1;
  
  // 0001
  if(~ReturningExNum & (1<<0) && ~ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    reg.SP_main = (reg.SP_main + 0x20);
    if(ptrAlign) reg.SP_main = reg.SP_main | 4;
  }
  // 1001
  else if(ReturningExNum & (1<<0) && ~ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    reg.SP_main = (reg.SP_main + 0x20);
    if(ptrAlign) reg.SP_main = reg.SP_main | 4;
  }
  // 1101
  else if(ReturningExNum & (1<<0) && ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    reg.SP_process = (reg.SP_process + 0x20);
    if(ptrAlign) reg.SP_process = reg.SP_process | 4;
  }

  flag_N = (psr >> 31) & 1;
  flag_Z = (psr >> 30) & 1;
  flag_C = (psr >> 29) & 1;
  flag_V = (psr >> 28) & 1;

  reg.IPSR = 0;
  for(short i = 0; i < 5; i++)
    if((psr >> i) & 1)
      reg.IPSR = reg.IPSR | (1 << i);
}

void exceptionReturn(uint32_t eReturn){
  if(actualMode != HANDLER_MODE) return;
  uint8_t ReturningExNum = reg.IPSR;
  
  uint32_t addr;

  // 0001
  if(~ReturningExNum & (1<<0) && ~ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    addr = reg.SP_main;
    actualMode = HANDLER_MODE;
    reg.CONTROL_SPSEL = false;
  }
  // 1001
  else if(ReturningExNum & (1<<0) && ~ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    addr = reg.SP_main;
    actualMode = THREAD_MODE;
    reg.CONTROL_SPSEL = false;
  }
  // 1101
  else if(ReturningExNum & (1<<0) && ReturningExNum & (1<<1) && ~ReturningExNum & (1<<2) && ReturningExNum & (1<<3)){
    addr = reg.SP_process;
    actualMode = THREAD_MODE;
    reg.CONTROL_SPSEL = true;
  }
  else{
    printf("Illegal exception return\n");
    return;
  }

  activeExceptions[ReturningExNum] = false;
  popStack(addr, ReturningExNum);
}


void pushStack(uint32_t returnAddr){
  uint32_t addr;
  bool ptrAlign;
  if(reg.CONTROL_SPSEL == true && actualMode == THREAD_MODE){
    ptrAlign = (reg.SP_process >> 2) & 1;
    reg.SP_process = (reg.SP_process - 0x20) & (~4); 
    addr = reg.SP_process;
  }else{
    ptrAlign = (reg.SP_main >> 2) & 1;
    reg.SP_main = (reg.SP_main - 0x20) & (~4); 
    addr = reg.SP_main;

    
  }

  uint32_t exNum32 = reg.IPSR;
  uint32_t psr = 0;
  psr = psr | (flag_N << 31);
  psr = psr | (flag_Z << 30);
  psr = psr | (flag_C << 29);
  psr = psr | (flag_V << 28);
  psr = psr | (1 << 24);        //Thumb state (always 1)
  psr = psr | exNum32;
  psr = psr | (ptrAlign << 9);

  *((uint32_t*)MemA(addr, 4)) = reg.GPR[0];
  *((uint32_t*)MemA(addr+4, 4)) = reg.GPR[1];
  *((uint32_t*)MemA(addr+8, 4)) = reg.GPR[2];
  *((uint32_t*)MemA(addr+12, 4)) = reg.GPR[3];
  *((uint32_t*)MemA(addr+16, 4)) = reg.GPR[12];
  *((uint32_t*)MemA(addr+20, 4)) = reg.LR;
  *((uint32_t*)MemA(addr+24, 4)) =  returnAddr;
  *((uint32_t*)MemA(addr+28,4)) = psr;
  
  
  if(actualMode == HANDLER_MODE)
    reg.LR = 0xFFFFFFF1;
  else if(reg.CONTROL_SPSEL == 0)
    reg.LR = 0xFFFFFFF9;
  else
    reg.LR = 0xFFFFFFFD;
}

void exceptionEntry(Exception ex){
  uint32_t returnAddr = reg.PC;
  uint8_t exNum = getExNum(ex);

  printf("Reported exception %d in %04X", exNum, reg.PC);

  pushStack(returnAddr);
  exceptionTaken(exNum);
}

