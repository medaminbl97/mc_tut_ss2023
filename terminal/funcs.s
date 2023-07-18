    .syntax unified
    .arch armv7e-m
    .data

    .section .text
    .thumb_func
    
    .align 2
    .global reverse
    .global reverse_all


reverse:
    mov r1,r0

for:
    ldrb r2,[r1]
    cmp r2,#0
    beq begin
    add r1,#1
    b for
begin:
    sub r1,#1
    ldrb r3,[r1]
    ldrb r2,[r0]
    
    strb r3,[r0]
    strb r2,[r1]

    add r0,#1
    cmp r0,r1
    bne begin
    bx lr



reverse_all:
    mov r2,#0
    sub r1,#1
for1:
    cmp r2,r1
    beq finish
    bl reverse
    add r0,#1
    add r2,#1
    b for1

finish:
    bx lr

