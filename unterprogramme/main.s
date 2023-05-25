    .syntax unified
    .arch armv7e-m
    .data

    .section .text
    .thumb_func
    
    .align 2
    .global main

func:
    mul r0,r0
    mul r1,r1
    add r0,r1,r0
    bx lr


main:
    mov r4,#4
    mov r5,#2
    mov r0,r4
    mov r1,r5
    bl func
    
    











    b main