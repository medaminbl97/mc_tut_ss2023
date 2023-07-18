	.syntax unified

	
	.text
	.align 2

	.equ	GPIORCGC, 0x400FE608
	.equ 	GPIOFLOCK, 0x40025520
	.equ	GPIOFCR, 0x40025524
	.equ 	GPIOFDIR, 0x40025400
	.equ	GPIOFPUR, 0x40025510
	.equ 	GPIOFDEN, 0x4002551C
	.equ	GPIOFDATA, 0x400253FC
	

	/* Das Symbol 'main' ist der Einsprungpunkt;
	   Durch .global ist es im ganzen Programm sichtbar */
	.global main
	.type main, %function
	
	/* Hier beginnt die Funktion 'main' */
main:
	bl init

loop:



	ldr	r5, =GPIOFDATA
	ldr	r6, [r5]
	and r6, #0x01
	cmp r6, #0
	bne chechsw1

	ldr	r6, [r5]
	eor r6, (1 << 1)
	str r6, [r5]
	bl wait
	b chechsw1

chechsw1:
	ldr	r5, =GPIOFDATA
	ldr	r6, [r5]
	and r6, #0x10
	cmp r6, #0
	bne loop

	ldr	r6, [r5]
	eor r6, (1 << 2)
	str r6, [r5]
	bl wait
	b loop




	.global wait
	.type wait, %function
	.align
wait:
	push {r0}

	ldr r0, =1200000

	.align
wloop:
	sub r0, #1
	cmp r0, #0
	bne wloop

	pop {r0}
	bx lr

    /* Ende der Datei */
    .end

