#ifndef CPU_TYPEDEFS_H
#define CPU_TYPEDEFS_H

#include <stdint.h>
#include <stdbool.h>

#define SCS_VTOR 0xE000ED08

typedef enum Instruction_{
  OP_LSL_I,
  OP_LSR_I,
  OP_ASR_I,
  OP_ADD_R,
  OP_SUB_R,
  OP_ADD_3I,
  OP_SUB_3I,
  OP_MOV_I,
  OP_CMP_I,
  OP_ADD_8I,
  OP_SUB_8I,

  OP_AND_R,
  OP_EOR_R,
  OP_LSL_R,
  OP_LSR_R,
  OP_ASR_R,
  OP_ADC_R,
  OP_SBC_R,
  OP_ROR_R,
  OP_TST_R,
  OP_RSB_I,
  OP_CMP_R,
  OP_CMN_R,
  OP_ORR_R,
  OP_MUL,
  OP_BIC_R,
  OP_MVN_R,

  OP_MOV_R,
  OP_BX,
  OP_BLX_R,

  OP_STR_R,
  OP_STRH_R,
  OP_STRB_R,
  OP_LDRSB_R,
  OP_LDR_R,
  OP_LDRH_R,
  OP_LDRB_R,
  OP_LDRSH_R,
  OP_STR_I,
  OP_LDR_I,
  OP_STRB_I,
  OP_LDRB_I,
  OP_STRH_I,
  OP_LDRH_I,
  OP_STR_I_rel,
  OP_LDR_I_rel,

  OP_ADD_SP_I,
  OP_SUB_SP_I,
  OP_SXTH,
  OP_SXTB,
  OP_UXTH,
  OP_UXTB,
  OP_PUSH,
  OP_CPS,
  OP_REV,
  OP_REV16,
  OP_REVSH,
  OP_POP,
  OP_BKPT,
  OP_NOP,
  OP_YIELD,
  OP_WFE,
  OP_WFI,
  OP_SEV,

  OP_B,
  OP_UDF,
  OP_SVC,

  OP_MSR_R,
  OP_DSB,
  OP_DMB,
  OP_ISB,
  OP_MRS,
  OP_BL
} Instruction;

typedef enum Exception_{
  EX_RESET,
  EX_NMI,
  EX_HARD_FAULT,
  EX_SV_CALL,
  EX_PEND_SV,
  EX_SYS_TICK,
  EX_EXTERNAL_INPUT,
  EX_RESERVED
} Exception;

typedef enum Mode_{
  THREAD_MODE,
  HANDLER_MODE
}Mode;

typedef struct Registers_{
  uint32_t GPR[13];         // General purpose registers
  uint32_t SP_main;         // Main stack pointer
  uint32_t SP_process;      // Process stack pointer
  uint32_t LR;              // Link register (stores return value)
  uint32_t PC;              // Program counter (current executed memory position)
  bool PM;                  // Priority mask
  bool CONTROL_SPSEL;       // If false - use main stack pointer, else user program stack pointer
  uint8_t IPSR;             // Actual exception number
} Registers;

#endif //CPU_TYPEDEFS_H
