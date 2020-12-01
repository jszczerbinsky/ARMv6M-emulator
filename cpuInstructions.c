#include <string.h>
#include <cpu.h>

bool checkPattern(uint16_t* opcode, const char* pattern){
  for(short i = 0; i < 16; i++)
    if(pattern[16-i-1] == 'x') continue;
    else if(((*opcode >> i) & 1) && pattern[16-i-1] == '0') return false;
    else if((~(*opcode >> i) & 1) && pattern[16-i-1] == '1') return false;
  return true;
}

bool checkPattern32(uint32_t* opcode, const char* pattern){
  for(short i = 0; i < 32; i++)
    if(pattern[32-i-1] == 'x') continue;
    else if(((*opcode >> i) & 1) && pattern[32-i-1] == '0') return false;
    else if((~(*opcode >> i) & 1) && pattern[32-i-1] == '1') return false;
  return true;
}

Instruction findPattern(uint16_t* opcode){
  if(checkPattern(opcode, "00000xxxxxxxxxxx")) return OP_LSL_I;
  if(checkPattern(opcode, "00001xxxxxxxxxxx")) return OP_LSR_I;
  if(checkPattern(opcode, "00010xxxxxxxxxxx")) return OP_ASR_I;
  if(checkPattern(opcode, "0001100xxxxxxxxx")) return OP_ADD_R;
  if(checkPattern(opcode, "0001101xxxxxxxxx")) return OP_SUB_R;
  if(checkPattern(opcode, "0001110xxxxxxxxx")) return OP_ADD_3I;
  if(checkPattern(opcode, "0001111xxxxxxxxx")) return OP_SUB_3I;
  if(checkPattern(opcode, "00100xxxxxxxxxxx")) return OP_MOV_I;
  if(checkPattern(opcode, "00101xxxxxxxxxxx")) return OP_CMP_I;
  if(checkPattern(opcode, "00110xxxxxxxxxxx")) return OP_ADD_8I;
  if(checkPattern(opcode, "00111xxxxxxxxxxx")) return OP_SUB_8I;

  if(checkPattern(opcode, "0100000000xxxxxx")) return OP_AND_R;
  if(checkPattern(opcode, "0100000001xxxxxx")) return OP_EOR_R;
  if(checkPattern(opcode, "0100000010xxxxxx")) return OP_LSL_R;
  if(checkPattern(opcode, "0100000011xxxxxx")) return OP_LSR_R;
  if(checkPattern(opcode, "0100000100xxxxxx")) return OP_ASR_R;
  if(checkPattern(opcode, "0100000101xxxxxx")) return OP_ADC_R;
  if(checkPattern(opcode, "0100000110xxxxxx")) return OP_SBC_R;
  if(checkPattern(opcode, "0100000111xxxxxx")) return OP_ROR_R;
  if(checkPattern(opcode, "0100001000xxxxxx")) return OP_TST_R;
  if(checkPattern(opcode, "0100001001xxxxxx")) return OP_RSB_I;
  if(checkPattern(opcode, "0100001010xxxxxx")) return OP_CMP_R;
  if(checkPattern(opcode, "0100001011xxxxxx")) return OP_CMN_R;
  if(checkPattern(opcode, "0100001100xxxxxx")) return OP_ORR_R;
  if(checkPattern(opcode, "0100001101xxxxxx")) return OP_MUL;
  if(checkPattern(opcode, "0100001110xxxxxx")) return OP_BIC_R;
  if(checkPattern(opcode, "0100001111xxxxxx")) return OP_MVN_R;

  if(checkPattern(opcode, "01000100xxxxxxxx")) return OP_ADD_R;
  if(checkPattern(opcode, "0100010101xxxxxx")) return OP_CMP_R;
  if(checkPattern(opcode, "010001011xxxxxxx")) return OP_CMP_R;
  if(checkPattern(opcode, "01000110xxxxxxxx")) return OP_MOV_R;
  if(checkPattern(opcode, "010001100xxxxxxx")) return OP_BX;
  if(checkPattern(opcode, "010001111xxxxxxx")) return OP_BLX_R;
  
  if(checkPattern(opcode, "0101000xxxxxxxxx")) return OP_STR_R;
  if(checkPattern(opcode, "0101001xxxxxxxxx")) return OP_STRH_R;
  if(checkPattern(opcode, "0101010xxxxxxxxx")) return OP_STRB_R;
  if(checkPattern(opcode, "0101011xxxxxxxxx")) return OP_LDRSB_R;
  if(checkPattern(opcode, "0101100xxxxxxxxx")) return OP_LDR_R;
  if(checkPattern(opcode, "0101101xxxxxxxxx")) return OP_LDRH_R;
  if(checkPattern(opcode, "0101110xxxxxxxxx")) return OP_LDRB_R;
  if(checkPattern(opcode, "0101111xxxxxxxxx")) return OP_LDRSH_R;
  if(checkPattern(opcode, "01100xxxxxxxxxxx")) return OP_STR_I;
  if(checkPattern(opcode, "01101xxxxxxxxxxx")) return OP_LDR_I;
  if(checkPattern(opcode, "01110xxxxxxxxxxx")) return OP_STRB_I;
  if(checkPattern(opcode, "01111xxxxxxxxxxx")) return OP_LDRB_I;
  if(checkPattern(opcode, "10000xxxxxxxxxxx")) return OP_STRH_I;
  if(checkPattern(opcode, "10001xxxxxxxxxxx")) return OP_LDRH_I;
  if(checkPattern(opcode, "10010xxxxxxxxxxx")) return OP_STR_I_rel;
  if(checkPattern(opcode, "10011xxxxxxxxxxx")) return OP_LDR_I_rel;

  if(checkPattern(opcode, "101100000xxxxxxx")) return OP_ADD_SP_I;
  if(checkPattern(opcode, "101100001xxxxxxx")) return OP_SUB_SP_I;
  if(checkPattern(opcode, "1011001000xxxxxx")) return OP_SXTH;
  if(checkPattern(opcode, "1011001001xxxxxx")) return OP_SXTB;
  if(checkPattern(opcode, "1011001010xxxxxx")) return OP_UXTH;
  if(checkPattern(opcode, "1011001011xxxxxx")) return OP_UXTB;
  if(checkPattern(opcode, "1011010xxxxxxxxx")) return OP_PUSH;
  if(checkPattern(opcode, "10110110011xxxxx")) return OP_CPS;
  if(checkPattern(opcode, "1011101000xxxxxx")) return OP_REV;
  if(checkPattern(opcode, "1011101001xxxxxx")) return OP_REV16;
  if(checkPattern(opcode, "1011101011xxxxxx")) return OP_REVSH;
  if(checkPattern(opcode, "1011110xxxxxxxxx")) return OP_POP;
  if(checkPattern(opcode, "10111110xxxxxxxx")) return OP_BKPT;
  if(checkPattern(opcode, "1011111100000000")) return OP_NOP;
  if(checkPattern(opcode, "1011111100010000")) return OP_YIELD;
  if(checkPattern(opcode, "1011111100100000")) return OP_WFE;
  if(checkPattern(opcode, "1011111100110000")) return OP_WFI;
  if(checkPattern(opcode, "1011111101000000")) return OP_SEV;

  if(checkPattern(opcode, "11011110xxxxxxxx")) return OP_UDF;
  if(checkPattern(opcode, "11011111xxxxxxxx")) return OP_SVC;
  if(checkPattern(opcode, "1101xxxxxxxxxxxx")) return OP_B;

  if(checkPattern32((uint32_t*)opcode, "11110011100xxxxx10x0xxxxxxxxxxxx")) return OP_MSR_R;
  if(checkPattern32((uint32_t*)opcode, "111100111011xxxx10x0xxxx0100xxxx")) return OP_DSB;
  if(checkPattern32((uint32_t*)opcode, "111100111011xxxx10x0xxxx0101xxxx")) return OP_DMB;
  if(checkPattern32((uint32_t*)opcode, "111100111011xxxx10x0xxxx0110xxxx")) return OP_ISB;
  if(checkPattern32((uint32_t*)opcode, "11110011111xxxxx10x0xxxxxxxxxxxx")) return OP_MRS;
  if(checkPattern32((uint32_t*)opcode, "111101111111xxxx1010xxxxxxxxxxxx")) return OP_UDF;
  if(checkPattern32((uint32_t*)opcode, "11110xxxxxxxxxxx11x1xxxxxxxxxxxx")) return OP_BL;

  printf("Unknown opcode in %04X", reg.PC);
  return OP_UDF;
}

void executeNextInstruction(){
  uint16_t* opcode = (uint16_t*)MemA(reg.PC, 2);
  reg.PC += 2;

  Instruction inst = findPattern(opcode);
  if(inst >= OP_MSR_R){
    reg.PC += 2;
    MemA(reg.PC-4, 4);
  }



}
