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
	.equ	Bezeichnung, Wert 
	.equ 	PI, 3
	 */

	

	/* Das Symbol 'main' ist der Einsprungpunkt;
	   Durch .global ist es im ganzen Programm sichtbar */
	.global main
	.type main, %function
	/* Hier beginnt die Funktion 'main' */
main:
	/*
	
		1. Register Addresse und deren Inhalt in zwei Arbeitsregister 
			(r0 bis r12) laden
		2. Inhalt entsprechend bearbeiten
		3. Veränderten Inhalt an die Adresse zurückspeichern
	
Folgende Assembler Befehle werden hierfür benötigt:

Für Schritt 1:
		ldr _Ziel_ , _Ursprung_
			
			_Ziel_ 		= Arbeitsregister (r0 bis r12)
			_Ursprung_ 	= Kann entweder ein Arbeitsregister, eine konstante
							Zahl (mit '=' davor) oder der Inhalt hinter
							einer Adresse sein, die in einem Arbeitsregister
							steht (dann mit eckigen Klammern)
	
Für Schritt 2: (Auswahl möglicher Befehle zum Bearbeiten)
		orr _Ziel_ , _Arg1_ , _Arg2_
	
			Verodert _Arg1_ mit _Arg2_ und speichert Ergebnis in _Ziel_
	
			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12)
			_Arg2_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
							(dann mit einem '#' davor)

--> _Arg2_ ist optional: wird _Arg2_ nicht angegeben, wird der Wert in _Ziel_ mit _Arg1_ verodert 							
	
		bic	_Ziel_ , _Arg1_ , _Arg2_
	
			Löscht die Bits, die in _Arg2_ auf 1 sind, in _Arg1_ und
			speichert Ergbnis in _Ziel_
	
			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12)
			_Arg2_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)

--> _Arg2_ ist optional: wird _Arg2_ nicht angegeben, werden die durch _Arg1_ angegebenen Bits in _Ziel_ gelöscht 

 
	
	
Für Schritt 3:
			str _Quelle_ , _Ziel_ 
	
			_Quelle_	= Arbeitsregister (r0 bis r12)
			_Ziel_		= Adresse in einem Arbeitsregister (mit eckgien 
							Klammern)


	*/




	
loop:

/*
--------------------------------------------------------------------------------------------------------------
Bitweise logische Befehle
--------------------------------------------------------------------------------------------------------------
			and	_Ziel_ , _Arg1_ , _Arg2_

			Bitweises  AND von _Arg1_ mit _Arg2_ und speichert Ergebnis in _Ziel_
			Ausmaskieren/auslesen einzelner Bit --> auszulesendes Bit mit 1 verunden, restliche Bits mit 0

			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)
			_Arg2_ 		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)

--> auch hier _Arg2_ optional
		orr _Ziel_ , _Arg1_ , _Arg2_
	
			Verodert _Arg1_ mit _Arg2_ und speichert Ergebnis in _Ziel_
	
			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12)
			_Arg2_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
							(dann mit einem '#' davor)

--> _Arg2_ ist optional: wird _Arg2_ nicht angegeben, wird der Wert in _Ziel_ mit _Arg1_ verodert 							
	
		bic	_Ziel_ , _Arg1_ , _Arg2_
	
			Löscht die Bits, die in _Arg2_ auf 1 sind, in _Arg1_ und
			speichert Ergbnis in _Ziel_
	
			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12)
			_Arg2_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)

--> _Arg2_ ist optional: wird _Arg2_ nicht angegeben, werden die durch _Arg1_ angegebenen Bits in _Ziel_ gelöscht 

 
		eor	_Ziel_ , _Arg1_ 

			Exklusiv Oder : Ersetzt 1 durch 0 bzw. 0 durch 1, wobei Arg1 das/die
			Bit(s), welche(s) exklusiv verordert wird/werden, angibt.
	
	
			_Ziel_		= Arbeitsregister (r0 bis r12), dort wird das Ergebnis
							gespeichert
			_Arg1_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)
	
--------------------------------------------------------------------------------------------------------------
Vergleichsoperatoren
--------------------------------------------------------------------------------------------------------------

		cmp _Arg1_, _Arg2_ 

			Subtrahiert den Wert _Arg2_ von _Arg1_ und setzt Flags
			Compare -> Wertevergleich

			_Arg1_		= Arbeitsregister (r0 bis r12)
			_Arg2_		= Arbeitsregister (r0 bis r12) oder konstante Zahl 
						(dann mit einem '#' davor)

--------------------------------------------------------------------------------------------------------------
Sprungbefehle
--------------------------------------------------------------------------------------------------------------			
		b Sprungadresse

		Sprung zur Sprungadresse wird ausgeführt

		
		beq Sprungadresse

		branch equal
		Sprung zur Sprungadresse wird ausgeführt, wenn das Zero Flag bei einem vorangegangenen cmp gesetzt wurde


		bne Sprungadresse

		branch not equal
		Sprung zur Sprungadresse wird ausgeführt, wenn das Zero Flag bei einem vorangegangenen cmp  NICHT gesetzt wurde

		
		blt Sprungadresse: branch less than
		bgt Sprungadresse: branch greater than


		Label/ Sprungziele:
		Stehen ganz links mit nachfolgendenm :

		
*/
	





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

