.section .text


.global uart_put_char
.global uart_get_char

uart_get_char:
    .cfi_startproc
    addi sp,sp,-16
    sd ra, 8(sp)
    sd s0,0(sp)
    addi s0,sp,16

    la s1, __uart_base_addr
    lw a0, 0(s1)
    call uart_put_char

    ld ra, 8(sp)
    ld s0, 0(sp)
    addi sp, sp , 16
    ret
    .cfi_endproc

uart_put_char:
    .cfi_startproc
    #prologue
    addi sp,sp,-32 
    sd s0, 0(sp)
    addi s0,sp,32

    mv a5,a0
    sb a5,-17(s0)
    la s1, __uart_base_addr
    mv s2, a0
    
    li t1, 255
    bgt s2, t1, str
    sb s2, 0(s1)
    j end

str:  
    lb s3, 0(s2)
    sb s3, 0(s1)
    addi s2, s2,1
    lb t1, 0(s2)
    bne t1, zero, str

end:    #epilogue
    ld s0, 0(sp)
    addi sp, sp, 32
    ret    

    .cfi_endproc
    
.end 