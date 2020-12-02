#include <time.h>
#include "cpu.h"

int main(int argc, char* argv[]){
  initializeRegs();
  initializeBytes();     

  while(true){
    executeNextInstruction(); 
    nanosleep((const struct timespec[]){{0,1250L}}, NULL);
  }
}
