    .syntax unified
    .arch armv7e-m
    .data

    .section .text
    .thumb_func
    
    .align 2
    .global str_length
    .global upper_case

str_length:
    mov r3,#0
for:
    ldrb r1,[r0]
    add r0,#1
    cmp r1,#0
    add r3,#1
    bne for
    sub r3,#1
    mov r0,r3

    bx lr

upper_case:
    mov r2,#0
for1:
    cmp r2,r1
    beq end

    ldrb r3,[r0],#1

    sub r3,#32
    strb r3,[r0,#-1]
    add r2,#1
    b for1

end:
    bx lr;