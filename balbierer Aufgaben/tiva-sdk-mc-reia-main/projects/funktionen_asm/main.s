
    .syntax unified
    .thumb


    .text
    .align 2

    .global main
    .type main, %function
main:
    push {lr}

    mov r0, #42
    mov r1, #10
    bl my_function

    pop {lr}
    bx lr

    .global my_function
    .type my_function, %function
my_function:

    push {lr}

    add r0, r0, r1

    push {r0}
    bl other_function

    
    pop {r0}

    pop {lr}
    bx lr

    .global other_function
    .type other_function, %function
other_function:
    
    push {r4}

    mov r4, #1000
    
    pop {r4}
    bx lr

    .end

