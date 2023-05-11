    .syntax unified
    .arch armv7e-m
    .data

var:
    .word 0xffffffff



    .section .text
    .thumb_func
    
    .align 2
    .global main


func2:


myadd:
    push {r5}
    add r5,r0,r1
    mov r0,r5
    pop {r5}
    bx lr


main:
    mov r5,#5
    mov r6,#10

    mov r0,r5
    mov r1,r6
    bl myadd
    mov r7,r0



    


    
    



    

















    b main