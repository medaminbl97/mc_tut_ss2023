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
    mov r1,#0x67
    strb r1,[r0]
    bx lr;