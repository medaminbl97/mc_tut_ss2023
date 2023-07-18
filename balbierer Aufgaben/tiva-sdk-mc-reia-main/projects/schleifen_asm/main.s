
    .syntax unified
    .thumb


    .text
    .align 2

    .global main
    .type main, %function
main:

/* If-then-else */
    mov r0, #6

    cmp r0, #5
    bne else
    add r0, #1
    b end
else:
    sub r0, #1
end:

/* For-Schleife */
@     mov r0, #10
@ loop:
@     cmp r0, #0
@     beq ende
@     /* Schleife */
@     nop
@     sub r0, #1
@     b loop
@ ende:

    bx lr

