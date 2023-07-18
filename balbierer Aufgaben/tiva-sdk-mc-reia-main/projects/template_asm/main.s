
    .syntax unified
    .thumb


    .text
    .align 2

    .global main
    .type main, %function
main:
    push {lr}

    mov r0, #0
    pop {lr}
    bx lr

