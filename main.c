#include <stdint.h>

#define PLIC_BASE 0xc000000
#define PLIC_PRIORITY (PLIC_BASE)
#define PLIC_ENABLE_INT (PLIC_BASE + 0x002000)
#define PLIC_THRESHOLD_REG (PLIC_BASE + 0x200000)
#define PLIC_CLAIM_REG (PLIC_BASE + 4 + 0x200000)

#define UART_BASE 0x10000000
#define UART_IER 1
#define UART_FCR 2
#define UART_ISR 2
#define UART_LCR 3
#define UART_INT_ID 0x0a

void uart_init() {
    //disable interrupts
    *(volatile unsigned char*)(UART_BASE + UART_IER) = 0x0;
    
    //set word length
    *(volatile unsigned char*)(UART_BASE + UART_LCR) = 0x3;

    //enable T and R interrupts
    *(volatile unsigned char*)(UART_BASE + UART_IER) = 0x3;
}

void plic_init() {
    *(volatile uint32_t*)PLIC_THRESHOLD_REG = 0x0;
    *(volatile uint32_t*)(PLIC_PRIORITY + 40) = 0x1;
    *(volatile uint32_t*)(PLIC_ENABLE_INT) = 1 << 10;
}

void m_trap() {
    uart_put_char("interrupt");
}

int main() {

    //enable interrupt in mstatus register
    uint64_t misa, mstatus, mie;

    //setup trap vector or function
    asm volatile ("mv t1, %[reg]" : : [reg] "r" (m_trap));
    asm volatile ("slli t1, t1, 2");
    asm volatile ("csrw mtvec, t1");
    //asm volatile ("csrw mtvec, %[reg]" : : [reg] "r" (interrupt_handler) );

    //enable machine interrupts
    asm volatile ("csrrs x0, mstatus, 0x8");

    //enable interrupts
    asm volatile ("li t1, 0x800");
    asm volatile ( "csrrw x0, mie, t1");

    uart_init();
    uart_put_char("a\n");
    plic_init();

    while(1) {
    
    }
}