/* 
   Startup code for TI TM4C123GH6PM Tiva
   <norbert.balbierer@oth-regensburg.de>
 */
    .syntax unified
    .thumb

    .text
    .align 2

/* Reset handler
 */
    .global Reset_Handler
    .type Reset_Handler, %function

Reset_Handler:
    /* Initialize Stack */
    ldr r0, =__stack
    mov sp, r0

    /* Copy .data initializers from flash to RAM */
    ldr	r0, =_start_data
	ldr	r1, =_end_data
	ldr	r2, =_sidata

copy_loop:
    cmp r0, r1
    beq zero_bss

    ldr r4, [r2], #4
    str r4, [r0], #4
    b copy_loop

zero_bss:
    /* Fill .bss with zero */
    ldr r0, =_start_bss
    ldr r1, =_end_bss
    mov r2, #0

zero_loop:
    cmp r0, r1
    beq sys_init

    str r2, [r0], #4
    b zero_loop

sys_init:

    /* Call system initialization.*/
    bl  SystemInit
    /* Call static constructors initialization */
    bl __libc_init_array
    /*  Go to main */
	bl	main

    /* Halt after main returns */
    b .


/* NMI handler
 */
    .global NMI_Handler
    .weak NMI_Handler
    .type NMI_Handler, %function

NMI_Handler:
    
    /* Halt */
    b .


/* Hard fault handler
 */
    .global HardFault_Handler
    .weak HardFault_Handler
    .type HardFault_Handler, %function

HardFault_Handler:
    
    /* Halt */
    b .


/* Default handler
 */
    .global Default_Handler
    .type HardFault_Handler, %function

Default_Handler:
    
    /* Halt */
    b .


/* --------------------------------------------
   INTERRUPT VECTOR TABLE
 */
	.section .vectors
	.align 2
	.global __Vectors

__Vectors:
	.word	__stack			            /* Top of stack */
	.word	Reset_Handler		        /* Reset handler */
	.word	NMI_Handler		            /* Non Maskable Interrupt handler */
	.word	HardFault_Handler	        /* Hard fault handler */
	.word	MemManage_Handler	        /* MPU fault handler */
	.word	BusFault_Handler	        /* Bus Fault Handler */
	.word	UsageFault_Handler	        /* Usage Fault Handler */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	SVC_Handler		            /* SVCall Handler */
	.word	DebugMon_Handler	        /* Debug Monitor Handler */
	.word	0			                /* Reserved */
	.word	PendSV_Handler	            /* PendSV Handler */
	.word	SysTick_Handler	            /* SysTick Handler */
	.word	GPIOPortA_Handler	        /* GPIO Port A */
	.word	GPIOPortB_Handler	        /* GPIO Port B */
	.word	GPIOPortC_Handler	        /* GPIO Port C */
	.word	GPIOPortD_Handler	        /* GPIO Port D */
	.word	GPIOPortE_Handler	        /* GPIO Port E */
	.word	UART0_Handler		        /* UART0 Rx and Tx */
	.word	UART1_Handler		        /* UART1 Rx and Tx */
	.word	SSI0_Handler		        /* SSI0 Rx and Tx */
	.word	I2C0_Handler		        /* I2C0 Master and Slave */
	.word	PWM0Fault_Handler	        /* PWM 0 Fault */
	.word	PWM0Generator0_Handler	    /* PWM 0 Generator 0 */
	.word	PWM0Generator1_Handler	    /* PWM 0 Generator 1 */
	.word	PWM0Generator2_Handler	    /* PWM 0 Generator 2 */
	.word	Quadrature0_Handler	        /* Quadrature Encoder 0 */
	.word	ADC0Seq0_Handler	        /* ADC0 Sequence 0 */
	.word	ADC0Seq1_Handler	        /* ADC0 Sequence 1 */
	.word	ADC0Seq2_Handler	        /* ADC0 Sequence 2 */
	.word	ADC0Seq3_Handler	        /* ADC0 Sequence 3 */
	.word	WDT_Handler		            /* Watchdog */
	.word	Timer0A_Handler		        /* Timer 0 subtimer A */
	.word	Timer0B_Handler		        /* Timer 0 subtimer B */
	.word	Timer1A_Handler		        /* Timer 1 subtimer A */
	.word	Timer1B_Handler		        /* Timer 1 subtimer B */
	.word	Timer2A_Handler		        /* Timer 2 subtimer A */
	.word	Timer2B_Handler		        /* Timer 2 subtimer B */
	.word	Comp0_Handler		        /* Analog Comp 0 */
	.word	Comp1_Handler		        /* Analog Comp 1 */
	.word	0		                    /* Reserved */
	.word	SysCtl_Handler		        /* System Control */
	.word	FlashCtl_Handler	        /* Flash Control */
	.word	GPIOPortF_Handler	        /* GPIO Port F */
	.word	0	                        /* Reserved */
	.word	0	                        /* Reserved */
	.word	UART2_Handler		        /* UART2 Rx and Tx */
	.word	SSI1_Handler	        	/* SSI1 Rx and Tx */
	.word	Timer3A_Handler	        	/* Timer 3 subtimer A */
	.word	Timer3B_Handler	        	/* Timer 3 subtimer B */
	.word	I2C1_Handler	        	/* I2C1 Master and Slave */
	.word	Quadrature1_Handler	        /* Quadrature Encoder 1 */
	.word	CAN0_Handler		        /* CAN0 */
	.word	CAN1_Handler		        /* CAN1 */
	.word	0		                    /* Reserved */
	.word	0	                        /* Reserved */
	.word	Hibernate_Handler	        /* Hibernate */
	.word	USB0_Handler		        /* USB0 */
	.word	PWM0Generator3_Handler	    /* PWM 0 Generator 3 */
	.word	uDMA_Handler		        /* uDMA Software Transfer */
	.word	uDMA_Error		            /* uDMA Error */
	.word	ADC1Seq0_Handler	        /* ADC1 Sequence 0 */
	.word	ADC1Seq1_Handler	        /* ADC1 Sequence 1 */
	.word	ADC1Seq2_Handler	        /* ADC1 Sequence 2 */
	.word	ADC1Seq3_Handler	        /* ADC1 Sequence 3 */
	.word	0		                    /* Reserved */
	.word	0		                    /* Reserved */
	.word	0	                        /* Reserved */
	.word	0	                        /* Reserved */
	.word	0	                        /* Reserved */
	.word	SSI2_Handler		        /* SSI2 Rx and Tx */
	.word	SSI3_Handler		        /* SSI3 Rx and Tx */
	.word	UART3_Handler		        /* UART3 Rx and Tx */
	.word	UART4_Handler		        /* UART4 Rx and Tx */
	.word	UART5_Handler		        /* UART5 Rx and Tx */
	.word	UART6_Handler		        /* UART6 Rx and Tx */
	.word	UART7_Handler		        /* UART7 Rx and Tx */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	0			                /* Reserved */
	.word	I2C2_Handler		        /* I2C2 Master and Slave */
	.word	I2C3_Handler		        /* I2C3 Master and Slave */
	.word	Timer4A_Handler		        /* Timer 4 subtimer A */
	.word	Timer4B_Handler		        /* Timer 4 subtimer B */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	Timer5A_Handler		        /* Timer 5 subtimer A */
	.word	Timer5B_Handler		        /* Timer 5 subtimer B */
	.word	WideTimer0A_Handler	        /* Wide Timer 0 subtimer A */
	.word	WideTimer0B_Handler	        /* Wide Timer 0 subtimer B */
	.word	WideTimer1A_Handler	        /* Wide Timer 1 subtimer A */
	.word	WideTimer1B_Handler	        /* Wide Timer 1 subtimer B */
	.word	WideTimer2A_Handler	        /* Wide Timer 2 subtimer A */
	.word	WideTimer2B_Handler	        /* Wide Timer 2 subtimer B */
	.word	WideTimer3A_Handler	        /* Wide Timer 3 subtimer A */
	.word	WideTimer3B_Handler     	/* Wide Timer 3 subtimer B */
	.word	WideTimer4A_Handler     	/* Wide Timer 4 subtimer A */
	.word	WideTimer4B_Handler	        /* Wide Timer 4 subtimer B */
	.word	WideTimer5A_Handler	        /* Wide Timer 5 subtimer A */
	.word	WideTimer5B_Handler	        /* Wide Timer 5 subtimer B */
	.word	FPU_Handler		            /* FPU */
	.word	0		                    /* Reserved */
	.word	0		                    /* Reserved */
	.word	0		                    /* Reserved */
	.word	0		                    /* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0		                    /* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	0							/* Reserved */
	.word	PWM1Generator0_Handler	    /* PWM 1 Generator 0 */
	.word	PWM1Generator1_Handler	    /* PWM 1 Generator 1 */
	.word	PWM1Generator2_Handler	    /* PWM 1 Generator 2 */
	.word	PWM1Generator3_Handler	    /* PWM 1 Generator 3 */
	.word	PWM1Fault_Handler	        /* PWM 1 Fault */


/* Declare default handler as weak replacement for all IRSs */
	
    .macro def_irq_handler handler_name
	.weak \handler_name
	.set \handler_name, Default_Handler
	.endm
	 
	def_irq_handler	MemManage_Handler	 
	def_irq_handler	BusFault_Handler	 
	def_irq_handler	UsageFault_Handler	 
	def_irq_handler	SVC_Handler
	def_irq_handler	DebugMon_Handler	 
	def_irq_handler	PendSV_Handler		 
	def_irq_handler	SysTick_Handler		 
	def_irq_handler	GPIOPortA_Handler	 
	def_irq_handler	GPIOPortB_Handler	 
	def_irq_handler	GPIOPortC_Handler	 
	def_irq_handler	GPIOPortD_Handler	 
	def_irq_handler	GPIOPortE_Handler	 
	def_irq_handler	UART0_Handler		 
	def_irq_handler	UART1_Handler		 
	def_irq_handler	SSI0_Handler		 
	def_irq_handler	I2C0_Handler		 
	def_irq_handler	PWM0Fault_Handler	 
	def_irq_handler	PWM0Generator0_Handler	 
	def_irq_handler	PWM0Generator1_Handler	 
	def_irq_handler	PWM0Generator2_Handler	 
	def_irq_handler	Quadrature0_Handler	 
	def_irq_handler	ADC0Seq0_Handler	 
	def_irq_handler	ADC0Seq1_Handler	 
	def_irq_handler	ADC0Seq2_Handler	 
	def_irq_handler	ADC0Seq3_Handler	 
	def_irq_handler	WDT_Handler		 
	def_irq_handler	Timer0A_Handler		 
	def_irq_handler	Timer0B_Handler		 
	def_irq_handler	Timer1A_Handler		 
	def_irq_handler	Timer1B_Handler		 
	def_irq_handler	Timer2A_Handler		 
	def_irq_handler	Timer2B_Handler		 
	def_irq_handler	Comp0_Handler		 
	def_irq_handler	Comp1_Handler		 

	def_irq_handler	SysCtl_Handler		 
	def_irq_handler	FlashCtl_Handler	 
	def_irq_handler	GPIOPortF_Handler	 

	def_irq_handler	UART2_Handler		 
	def_irq_handler	SSI1_Handler		 
	def_irq_handler	Timer3A_Handler		 
	def_irq_handler	Timer3B_Handler		 
	def_irq_handler	I2C1_Handler		 
	def_irq_handler	Quadrature1_Handler	 
	def_irq_handler	CAN0_Handler		 
	def_irq_handler	CAN1_Handler		 

	def_irq_handler	Hibernate_Handler	 
	def_irq_handler	USB0_Handler		 
	def_irq_handler	PWM0Generator3_Handler	 
	def_irq_handler	uDMA_Handler		 
	def_irq_handler	uDMA_Error		 
	def_irq_handler	ADC1Seq0_Handler	 
	def_irq_handler	ADC1Seq1_Handler	 
	def_irq_handler	ADC1Seq2_Handler	 
	def_irq_handler	ADC1Seq3_Handler	 

	def_irq_handler	SSI2_Handler		 
	def_irq_handler	SSI3_Handler		 
	def_irq_handler	UART3_Handler		 
	def_irq_handler	UART4_Handler		 
	def_irq_handler	UART5_Handler		 
	def_irq_handler	UART6_Handler		 
	def_irq_handler	UART7_Handler		 

	def_irq_handler	I2C2_Handler		 
	def_irq_handler	I2C3_Handler		 
	def_irq_handler	Timer4A_Handler		 
	def_irq_handler	Timer4B_Handler		 
	def_irq_handler	Timer5A_Handler		 
	def_irq_handler	Timer5B_Handler		 
	def_irq_handler	WideTimer0A_Handler	 
	def_irq_handler	WideTimer0B_Handler	 
	def_irq_handler	WideTimer1A_Handler	 
	def_irq_handler	WideTimer1B_Handler	 
	def_irq_handler	WideTimer2A_Handler	 
	def_irq_handler	WideTimer2B_Handler	 
	def_irq_handler	WideTimer3A_Handler	 
	def_irq_handler	WideTimer3B_Handler	 
	def_irq_handler	WideTimer4A_Handler	 
	def_irq_handler	WideTimer4B_Handler	 
	def_irq_handler	WideTimer5A_Handler	 
	def_irq_handler	WideTimer5B_Handler	 
	def_irq_handler	FPU_Handler		 

	def_irq_handler	PWM1Generator0_Handler	 
	def_irq_handler	PWM1Generator1_Handler	 
	def_irq_handler	PWM1Generator2_Handler	 
	def_irq_handler	PWM1Generator3_Handler	 
	def_irq_handler	PWM1Fault_Handler	 



