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
	
    .global init
	.type init, %function
init:
    push {lr}

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

    pop {lr}
    bx lr 
    .end
    
