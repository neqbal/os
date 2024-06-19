#include <stdint.h>

#define PLIC_BASE 0xc000000
#define PLIC_ENABLE_INT (PLIC_BASE + 0x002000)
#define PLIC_THRESHOLD_REG (PLIC_BASE + 0x200000)
#define PLIC_CLAIM_REG (PLIC_BASE + 4 + 0x200000)

#define UART_BASE 0x10000000
#define UART_INT_ENABLE_REG (UART_BASE + 0x01)
#define UART_INT_ID 0x0a

void plic_init() {
    *(volatile uint32_t *)PLIC_THRESHOLD_REG = 0;
    *(volatile uint32_t *)PLIC_ENABLE_INT = (1 << UART_INT_ID);
}

void handle_uart_interrupt () {
    uint32_t claim = *(volatile uint32_t *)(PLIC_CLAIM_REG);

    if(claim == UART_INT_ID) {
        uart_get_char();
    }
    *(volatile uint32_t *)(PLIC_CLAIM_REG) = claim;
}

void uart_enable_interrupt() {
    *(volatile uint32_t *)UART_INT_ENABLE_REG = 0x01;
}

int main() {

    plic_init();
    uart_enable_interrupt();

    uart_put_char("abc");
    while(1) {
        handle_uart_interrupt();
    }
}