#include <stdint.h>
#include <stddef.h>

unsigned char *n = (unsigned char *)0x10000000;
void putchar(char c) {
    *n = c;
    return;
}

void print(char *str) {
    while(*str !='\0') {
        putchar(*str);
        str++;
    }
    return;
}

void kmain(void) {
    print("Hello world\n");
    while(1) {
        //putchar(*n);
    }
    return;
}

