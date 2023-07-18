
    .syntax unified
    .thumb


    .text
    .align 2

    .global main
    .type main, %function
main:
    push {lr}

    /* Clock-Gate für Port F aktivieren */
    ldr r0, =0x400fe608
    ldr r4, [r0]
    orr r4, (1 << 5)
    str r4, [r0]

    /* Pin 1 als normalen GPIO konfigurieren
       (AFSEL = 0) */
    ldr r0, =0x40025420
    ldr r4, [r0]
    //and r4, ~(1 << 1)
    bic r4, (1 << 1)
    str r4, [r0]

    /* Pin PF1 auf Output stellen */
    ldr r0, =0x40025400
    ldr r4, [r0]
    orr r4, (1 << 1)
    str r4, [r0]

    /* Pin PF1 Digital Enable */
    ldr r0, =0x4002551c
    ldr r4, [r0]
    orr r4, (1 << 1)
    str r4, [r0]

    /* Rote LED einschalten */
    ldr r0, =0x400253fc
    ldr r4, [r0]
    orr r4, (1 << 1)
    str r4, [r0]








    mov r0, #0
    pop {lr}
    bx lr

