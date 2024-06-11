.section .text


.global uart_put_char
.global uart_get_char

uart_get_char:
    .cfi_startproc
    addi sp,sp,-16
    sd s0,8(sp)
    addi s0,sp,16
    .cfi_endproc

uart_put_char:
    .cfi_startproc
    addi sp,sp,-32 
    sd fp,24(sp)
    addi fp,sp,32
    mv a5,a0
    sb a5,-17(s0)
    la s1, __uart_base_addr
    mv s2, a0
    addi s3, s2, 14

1:  
    lb s4, 0(s2)
    sb s4, 0(s1)
    addi s2, s2, 1
    blt s2, s3, 1b
    .cfi_endproc
    
.end 
