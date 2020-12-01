#include <stdint.h>
#include <stdbool.h>

#define SCS_VTOR 0xE000ED08

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


