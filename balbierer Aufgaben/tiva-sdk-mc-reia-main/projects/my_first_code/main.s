
    .syntax unified
    .thumb


    .data

a: .word 42

b: .word 10

c: .word 0


    .text
    .align 2

    .global main
    .type main, %function
main:

    ldr r1, =a
    ldr r0, [r1]

    ldr r1, =b
    ldr r2, [r1]

    adds r1, r2, r0

    ldr r3, =c
    str r1, [r3]

    bx lr

