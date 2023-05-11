    .syntax unified
    .arch armv7e-m
    .data



var:
    .word 0xffffffff

    .section .text
    .thumb_func
    
    .align 2
    .global main

    .equ rcgc, 0x400FE608
    .equ data, 0x400253fc
    .equ dir, 0x40025400
    .equ afsel, 0x40025420
    .equ den, 0x4002551C

main:
    ldr r0,=rcgc
    ldr r1,[r0]
    orr r1,(1 << 5)
    str r1,[r0]

    ldr r0,=afsel
    ldr r1,[r0]
    bic r1,(1 << 1)
    str r1,[r0]

    ldr r0,=dir
    ldr r1,[r0]
    orr r1,(1 << 1)
    str r1,[r0]

    ldr r0,=den
    ldr r1,[r0]
    orr r1,(1 << 1)
    str r1,[r0]

    ldr r0,=data
    ldr r1,[r0]
    orr r1,(1 << 1)
    str r1,[r0]

    ldr r1,[r0]
    bic r1,(1 << 1)
    str r1,[r0]
    




    b main 
