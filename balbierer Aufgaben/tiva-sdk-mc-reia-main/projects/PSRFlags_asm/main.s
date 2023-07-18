
	.syntax unified

	/* Das, was folgt, soll in den Programm-
	   speicher (.text); Das Alignment soll
	   16-Bit sein (2 Byte) */
	
	
	/* Das, was folgt, soll in den Arbeits-
	   speicher (.text)//  Das Alignment soll
	   16-Bit sein (2 Byte) */
	
	.section .data
	.align 2

numArray:
.word 1, 2, 3, 4, 5

werte:
.word 45, 37, 96, 7, 27, 1, 122, 7, 9, 68, 43, 32, 45, 65, 87, 98	

//hex: 0x2D, 0x25, 0x60, 0x07, 0x1b, 0x01, 0x7A, 0x07, 0x09, 0x44

short:
.word 1, 2, 3, 4, 5, 6, 7, 8, 9

anzahl_werte:
.word 16

negVar: 
.word -1


	
	
	
	.section .text
	.align 2

	/* Symbolische Namen für Registeradressen; 
	   Die .equ-Direktive sagt dem Assembler, er
	   soll alle Instanzen des Symbols durch den
	   nachfolgenden Wert ersetzen

*/

	 
	.equ	myConstData, 0xFFFF3333
	.equ	konst1, 0xabcdefba
	.equ 	short1, 0x1111
	.equ 	short2, 0x2222

	/* Das Symbol 'main' ist der Einsprungpunkt;
	   Durch .global ist es im ganzen Programm sichtbar */
	.global main
	.type main, %function
	/* Hier beginnt die Funktion 'main' */
main:
/*Program Status Register Flags (Application Program Status Regiser) */

/*S-Suffix bei Arithmetischen Befehlen */
	adds r4, #1 // to reset previous flags
	ldr r8, =0x7FFFFFFF 
	adds r8, #2 // Overflow
	adds r8, #1 // Reset Overflow
	adds r4, #1 // to reset previous flags
	ldr r7, =0x0
	ldr r6, =0x80000000
	subs r7, r6
	adds r4, #1 // to reset previous flags
	ldr r9, =0xFFFFFFFF
	adds r9, #1// Carry

	adds r10, r10, #-1
	adds r7, r7, #-8
	adds r4, #1 
	ldr r9, =0x9
	subs r9, #1

	/*add{cond}: Konditionaler arithmetischer Befehl --> add*/ 
	IT  EQ  // next instruction is conditional
	addeq r9, r9,  #42

	adds r8, r8, #2 
	mov r8, #0xffffffff
	adds r8, r8, #0x42


	/*Do-While Schleife in asm mit konditionalem branch */
	mov r0, #3
do: sub r0, #1
	cmp r0, #0
	bne do

	mov r0, #7




	/*Aufgabe 1*/
	ldr r0, =0x0f0f0f0f0f
	ldr r1, =0xfedcba98
	/*Finden Sie heraus, was nach der Ausführung der einzelnen Befehle in R3 steht*/
	eor r3, r1, r0 	//(1a)
	orr r3, r1, r0	//(1b)
	and r3, r1, r0	//(1c)
	bic r3, r1, r0	//(1d)
	mvn r3, r1		//(1e)
	mvn r3, r0		//(1f)
	mvn r3, r0		//(1g)
	add r3, r1, r3	//(1h)


	/*Aufgabe 2*/
	ldr r0, =0xffffffff
	ldr r1, =0x00000001
	ldr r2, =0x00000000

	/*Wann werden welche Flags (N, Z, C, V) gesetzt?*/

	add  r3, r0, r2 	//(2a)
	subs r3, r0, r0		//(2b)
	adds r3, r0, r2		//(2c)
	lsl  r3, r0, #1		//(2d)
	lsrs r3, r1, #1		//(2e)
	ands r3, r0, r2		//(2f)
	adds r3, r0, r1		//(2g)
	subs r3, r0, r1		//(2h)
	eor  r3, r0, r1		//(2i)
	ands r3, r1, r1		//(2j)

	ldr r5, =0x2
	ldr r6, =0x1
	add r5, r5, r6, lsl #2 




	ldr r0, =short
	ldr r1, =0x00000000
	ldr r1, [r0]
	add r0, r0, #2
	ldr r2, [r0]
	add r0, r0, #2
	ldr r3, [r0]


/*--------------------------------------------------------------------------------------------------------------
										while(1) in ASM
--------------------------------------------------------------------------------------------------------------*/


loop:

	ldr r0, =0xffffffff
	ldr r1, =0x00000001
	ldr r2, =0x00000000
	adds r0, #1
	subs r1, #1
	subs r2, #1
	bl wait
	b loop


/*Warte Schleife in ASM */
	.global wait
	.type wait, %function
	.align
wait:
	push {r0}

	ldr r0, =12

	.align
/*for-Schleife in ASM */
wloop:
	sub r0, #1
	cmp r0, #0
	bne wloop

	pop {r0}
	bx lr



    .end