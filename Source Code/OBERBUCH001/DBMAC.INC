;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+;	File:		DBMAC.INC
;+;	Purpose:	OB-MX debug macros
;+;	Original:		1993-10-21	D.N. Lynx Crowe
;+;	Revision:	2	1993-12-06	D.N. Lynx Crowe
;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; ~~~ DEBUG BEGIN ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

;+ ---------------------------------------------------------------------------
;+ %debugf -- turn off the debug flag
;+
;+ This turns the debug LED on  (it's inverted logic)
;+ ---------------------------------------------------------------------------

	macro	%debugf

	if		DEBUGIT

	pusha	; {18} START OF CRITICAL SECTION -- DISABLE INTERRUPTS ---------------

	ldb		HSO_COMMAND, #002H				; turn off hso.2 for debugging
	add		HSO_TIME, TIMER1, #3			; ----------------------------

	popa	; {18} END OF CRITICAL SECTION -- RESTORE INTERRUPTS -----------------

	endif	; DEBUGIT

	endmac

;+ ---------------------------------------------------------------------------
;+ %debugn -- turn on the debug flag
;+
;+ This turns the debug LED off  (it's inverted logic)
;+ ---------------------------------------------------------------------------

	macro	%debugn

	if		DEBUGIT

	pusha	; {18} START OF CRITICAL SECTION -- DISABLE INTERRUPTS ---------------

	ldb		HSO_COMMAND, #022H				; turn on hso.2 for debugging
	add		HSO_TIME, TIMER1, #3			; ---------------------------

	popa	; {18} END OF CRITICAL SECTION -- RESTORE INTERRUPTS -----------------

	endif	; DEBUGIT

	endmac

; ~~~ DEBUG END ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; The End
