;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+;	File:		STDMAC.INC
;+;	Purpose:	OB-MX data structure macro definitions
;+;	Original:		1993-05-26	D.N. Lynx Crowe
;+;	Revision:	9	1993-12-06	D.N. Lynx Crowe
;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;+ ---------------------------------------------------------------------------
;+ %strdef -- macro to begin a structure definition
;+ ---------------------------------------------------------------------------

	macro   %strdef					; {no arguments}
	stroff  set     0
	endmac

;+ ---------------------------------------------------------------------------
;+ %salign -- macro to align a structure to a WORD boundary 
;+ ---------------------------------------------------------------------------

	macro   %salign					; {no arguments}
	if      (stroff and 1)
	stroff  set (stroff + 1)
	endif
	endmac

;+ ---------------------------------------------------------------------------
;+ %mfield -- macro to define a field of <length> bytes
;+ ---------------------------------------------------------------------------

	macro   %mfield					; <length>, <label>
	%salign
\1      set     stroff
	stroff  set stroff + \0
	endmac

;+ ---------------------------------------------------------------------------
;+ %mstruct -- macro to reference a structure in a structure
;+ ---------------------------------------------------------------------------

	macro   %mstruct				; <struct_ref>, <label>
	%salign
\1      set     stroff
	stroff  set stroff + \0_size
	endmac

;+ ---------------------------------------------------------------------------
;+ %maddr -- macro to define an address field in a structure
;+ ---------------------------------------------------------------------------

	macro   %maddr					; <label>
	%salign
\0      set     stroff
	stroff  set stroff + 2
	endmac

;+ ---------------------------------------------------------------------------
;+ %mword -- macro to define a WORD field in a structure
;+ ---------------------------------------------------------------------------

	macro   %mword					; <label>
	%salign
\0      set     stroff
	stroff  set stroff + 2
	endmac

;+ ---------------------------------------------------------------------------
;+ %mint -- macro to define an INT field in a structure
;+ ---------------------------------------------------------------------------

	macro   %mint					; <label>
	%salign
\0      set     stroff
	stroff  set stroff + 2
	endmac

;+ ---------------------------------------------------------------------------
;+ %mbyte -- macro to define a BYTE field in a structure
;+ ---------------------------------------------------------------------------

	macro   %mbyte					; <label>
\0      set     stroff
	stroff  set stroff + 1
	endmac

;+ ---------------------------------------------------------------------------
;+ %marray -- macro to define an array reference in a structure
;+ ---------------------------------------------------------------------------

	macro	%marray					; <num_elem>, <elem_size>, <label>
	%salign
\2		set		stroff
\2_size	set	(\0 * \1)
	stroff	set	stroff + \2_size
	endmac

;+ ---------------------------------------------------------------------------
;+ %enddef -- macro to define the end of a structure
;+ ---------------------------------------------------------------------------

	macro   %enddef					; <label>
	%salign
\0_size set     stroff
	endmac

; The End
