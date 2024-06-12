.section .text


.global uart_put_char
.global uart_get_char

uart_get_char:
    .cfi_startproc
    addi sp,sp,-16
    sd s0,8(sp)
    addi s0,sp,16

    la s1, __uart_base_addr
    
    .cfi_endproc

uart_put_char:
    .cfi_startproc
    #prologue
    addi sp,sp,-32 
    sd fp,24(sp)
    addi fp,sp,32

    mv a5,a0
    sb a5,-17(s0)
    la s1, __uart_base_addr
    mv s2, a0
    #addi s3, s2, 14

1:  
    lb s3, 0(s2)
    sb s3, 0(s1)
    addi s2, s2, 1
    lb t1, 0(s2)
    bne t1, zero, 1b

    #epilogue
    ld s0, 24(sp)
    addi sp, sp, 32
    ret    

    .cfi_endproc
    
.end 