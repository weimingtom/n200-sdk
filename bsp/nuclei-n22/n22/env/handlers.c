//See LICENSE for license details.
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "n22/drivers/riscv_encoding.h"
#include "n22/drivers/n22_func.h"

__attribute__((weak)) uintptr_t handle_trap(uintptr_t mcause, uintptr_t sp)
{
  write(1, "trap\n", 5);
  printf("In trap handler, the mcause is %d\n", mcause);
  printf("In trap handler, the mepc is 0x%x\n", read_csr(mepc));
  printf("In trap handler, the mtval is 0x%x\n", read_csr(mbadaddr));
  _exit(mcause);
  return 0;
}


/*Entry Point for PIC Interrupt Handler*/
__attribute__((weak)) uint32_t handle_irq(uint32_t int_num){
    // Enable interrupts to allow interrupt preempt based on priority
    set_csr(mstatus, MSTATUS_MIE);
  pic_interrupt_handlers[int_num]();
    // Disable interrupts 
    clear_csr(mstatus, MSTATUS_MIE);
  return int_num;
}


__attribute__((weak)) uintptr_t handle_nmi()
{
  write(1, "nmi\n", 5);
  _exit(1);
  return 0;
}


