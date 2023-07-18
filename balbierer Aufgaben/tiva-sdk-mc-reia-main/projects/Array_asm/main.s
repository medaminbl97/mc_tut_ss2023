
	.syntax unified
	
	
/* Das, was folgt, soll in den Programm-
speicher (.text); Das Alignment soll
16-Bit sein (2 Byte) */	
	.section .data
	.align 2

/*Array: Bezeichnung "numArray" als Label, Datentyp .word (=32Bit), Werte: 1, 2, 3, 4, 5*/	
numArray:
.word 1, 2, 3, 4, 5

werte:
.word 45, 37, 96, 7, 27, 1, 122, 7, 9, 68, 43, 32, 45, 65, 87, 98	

//hex: 0x2D, 0x25, 0x60, 0x07, 0x1b, 0x01, 0x7A, 0x07, 0x09, 0x44

short:
.word 1, 2, 3, 4, 5, 6, 7, 8, 9

/*Variable: Bezeichnung "anzahl_Werte" ganz Links*/
anzahl_werte:
.word 16

negVar: 
.word -1


	
/* Das, was folgt, soll in den Arbeits-
speicher (.text)//  Das Alignment soll
16-Bit sein (2 Byte) */	
	.section .text
	.align 2


/* Symbolische Namen für Registeradressen; 
Die .equ-Direktive sagt dem Assembler, er
soll alle Instanzen des Symbols durch den
nachfolgenden Wert ersetzen
C/C++: #define Anweisungen  */


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

	ldr r0, =numArray
	ldr r1, [r0]
	adds r1, r1, #1
	str r1, [r0]
	add r0, #4
	ldr r1, [r0]
	subs r1, r1, #2
	str r1, [r0]
	add r0, #4
	ldr r1, [r0]
	cmp r1, #3
	add r0, #4
	ldr r1, [r0]
	subs r1, r1, #5
	str r1, [r0]
	add r0, #4
	ldr r1, [r0]
	adds r1, r1, #0xfffffffc



	ldr r0, = 0x12345678
	ldr r1, = 0x0abcdef0

	ldr r2, =werte
	ldr r3, [r2]
	add r3, r3, #4
	add r2, #4
	ldr r4, [r2]
	add r4, #2
	str r4, [r2]
	ldr r5, [r2]
	add r2, r2, #4
	ldr r5, [r2]
	add r2, r2, #4
	ldr r6, [r2]


/* Offset-Varianten des LDR-Befehls
LDR{type}{cond} Rt, [Rn {, #offset}] ; immediate offset
LDR{type}{cond} Rt, [Rn, #offset]! ; pre-indexed
LDR{type}{cond} Rt, [Rn], #offset ; post-indexed */


	ldr r7, [r2, #4] //immediatiate offset
	add r2, r2, #4
	ldr r8, [r2, #4]! // pre-indexed offset
	ldr r9, [r2], #4 //post-indexed offset
	ldr r10, [r2]


/*Move Befehl */
	mov r4, r0
	mov r4, #1
	movw r5, #0xBEEF
	movt r6, #0xDEAD
	mvns r7, r4
	mov r8, #-1
/*Varianten der ADD Instruktion*/
	add r3, r4, r5 	// r3= r4+r5
	add r3, r4 		// r3= r3+r4
	add r3, r4, #5 	// r3= r4 +5
	add r3, r3, #15		// r3=r3+15

/*Average Funktion in ASM
Schreiben Sie eine Funktion in assembler, welche den Mittelwert eines Arrays berechnet:
Der erste Übergabeparameter ist ein Pointer auf das Array, der zweite
Übergabeparameter ist die Anzahl der Array Werte.
Zurückgegeben wird der Mittelwert der Array Werte.
Ergänzen Sie zusätzlich dazu im Programm den Funktionsaufruf und ggf. erforderlichen
Schritte zur Übergabe der Werte an die Funtion. */

	ldr r0, =werte	
	ldr r2, =anzahl_werte
	ldr r1, [r2]
	bl avarray



/*--------------------------------------------------------------------------------------------------------------
										while(1)
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



	.global wait
	.type wait, %function
	.align
wait:
	push {r0}

	ldr r0, =12

	.align
wloop:
	sub r0, #1
	cmp r0, #0
	bne wloop

	pop {r0}
	bx lr


    .global avarray
	.type avarray, %function
	.align 2
 avarray:
	push {lr}
	push {r3}
	push {r4}

	mov r4, r0
	mov r3, r1

	ldr r0, =0x00

goon:

	ldr r5, [r4]
	add r0, r5
	add r4, #0x04
	sub r3, #0x01
	cmp r3, #0x00
	beq endreached
	bne goon

endreached:

	udiv r0, r0, r1
	pop {r4}
	pop {r3}
	pop {lr}
	bx lr


    .end