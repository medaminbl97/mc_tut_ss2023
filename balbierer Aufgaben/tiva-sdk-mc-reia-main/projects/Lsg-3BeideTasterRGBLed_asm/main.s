	.syntax unified

	/*
	Two slightly different syntaxes are support for ARM and THUMB instructions. The default, divided, uses the old style where ARM and THUMB instructions had their own, separate syntaxes. The new, unified syntax, which can be selected via the .syntax directive,
	and has the following main features:

    Immediate operands do not require a # prefix.
    The IT instruction may appear, and if it does it is validated against subsequent conditional affixes. In ARM mode it does not generate machine code, in THUMB mode it does.
    For ARM instructions the conditional affixes always appear at the end of the instruction. For THUMB instructions conditional affixes can be used, but only inside the scope of an IT instruction.
    All of the instructions new to the V6T2 architecture (and later) are available. (Only a few such instructions can be written in the divided syntax).
    The .N and .W suffixes are recognized and honored.
    All instructions set the flags if and only if they have an s affix. 
*/
	

	/* Das, was folgt, soll in den Programm-
	   speicher (.text); Das Alignment soll
	   16-Bit sein (2 Byte) */
	.text
	.align 2
/* Symbolische Namen für Registeradressen; 
	   Die .equ-Direktive sagt dem Assembler, er
	   soll alle Instanzen des Symbols durch den
	   nachfolgenden Wert ersetzen
	 */
	.equ	GPIORCGC, 0x400FE608
	.equ 	GPIOFLOCK, 0x40025520
	.equ	GPIOFCR, 0x40025524
	.equ 	GPIOFDIR, 0x40025400
	.equ	GPIOFPUR, 0x40025510
	.equ 	GPIOFDEN, 0x4002551C
	.equ 	GPIOFODR, 0x4002550C
	.equ	GPIOFDATA, 0x400253FC // 
	.equ 	GPIOFDATAPIN0, 0x40025004
	

	/* Das Symbol 'main' ist der Einsprungpunkt;
	   Durch .global ist es im ganzen Programm sichtbar */
	.global main
	.type main, %function
	/* Hier beginnt die Funktion 'main' */
main:

    /*  Clock für Port F einschalten  */
	ldr	r5, =GPIORCGC
	ldr	r6, [r5]
	orr	r6, #0x20
	str	r6, [r5]

	/*  Unlocksequence Lock Register */
	ldr	r5, =GPIOFLOCK
	ldr r6, =0x4C4F434B
	str r6, [r5]

	
	/*  Commit Register */
	ldr r5, =GPIOFCR	
	ldr r6, [r5]
	orr r6,  #0x11
	str r6, [r5]

	
	/*  Direction Register */
	ldr r5, =GPIOFDIR
	ldr r6, [r5]
	orr r6,  #0x0E	
	bic r6,  #0x11
	str r6, [r5]


	/*  Pull Up Widerstand */
	ldr r5, =GPIOFPUR
	ldr r6, [r5]
	orr r6, #0x11
	str r6, [r5]
	
	
	/*  Digital Enable  */
	ldr r5, =GPIOFDEN	
	ldr r6, [r5]
	orr r6,  #0x1F
	str r6, [r5]
	

	ldr	r5, =GPIOFDATA
	ldr	r6, [r5]
	orr r6, #0x08
	str r6, [r5] 

	
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

	//bl wait
	/* Und zurück nach loop */
//	b loop


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

