    .syntax unified
    .arch armv7e-m
    .data



var:
    .word 0xffffffff

    .section .text
    .thumb_func
    
    .align 2
    .global main

    .equ clock, 0x400FE608
    .equ data, 0x400043fc
    .equ dir, 0x40004400
    .equ afsel, 0x40004420
    .equ den, 0x4000451C

main:
    ldr r0,=clock
    ldr r1,[r0]
    orr r1,(1 << 0)
    str r1,[r0]

    ldr r0,=afsel
    ldr r1,[r0]
    bic r1,(1 << 7)
    str r1,[r0]

    ldr r0,=dir
    ldr r1,[r0]
    orr r1,(1 << 7)
    str r1,[r0]

    ldr r0,=den
    ldr r1,[r0]
    orr r1,(1 << 7)
    str r1,[r0]

    ldr r0,=data
    ldr r1,[r0]
    orr r1,(1 << 7)
    str r1,[r0]

    ldr r1,[r0]
    bic r1,(1 << 7)
    str r1,[r0]
    












    






    b main 
