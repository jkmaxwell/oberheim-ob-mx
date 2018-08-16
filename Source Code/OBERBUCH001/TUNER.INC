;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+;	File:		TUNER.INC
;+;	Purpose:	OB-MX include file for tune.a
;+;	Original:		1994-05-16	D.N. Lynx Crowe
;+;	Revision:	1	1994-05-16	D.N. Lynx Crowe
;+;
;+; WARNING:	These definitions MUST match those in voice.h and voice.inc
;+;
;+; Note:		See the comments in voice.h for more details on variable
;+;				definitions, bit usage, etc.
;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

$STDMAC.INC

TEMP		equ			0EAH		; C keeps its temps here  00EAH .. 00FFH

;+ --- BIT MASKS ---

BIT0		equ			001H
BIT1		equ			002H
BIT2		equ			004H
BIT3		equ			008H
BIT4		equ			010H
BIT5		equ			020H
BIT6		equ			040H
BIT7		equ			080H

;+ --- sizes of storage units

BYTES			equ		1					; sizeof(BYTE)
ADDRS			equ		2					; sizeof(ADDR)
INTS			equ		2					; sizeof(INT)
WORDS			equ		2					; sizeof(WORD)
DWORDS			equ		4					; sizeof(DWORD)

;+ --- OB-MX hardware equates  ---

VACTL		equ			0FF00H		; Voice A oscillator controls
VBCTL		equ			0FF80H		; Voice B oscillator controls

;+ --- Data Structure sizes ---

vco_size	equ			24
vcf_size	equ			8
lfo_size	equ			24
env_size	equ			42
mod_size	equ			16

N_VCOS		equ		2					; number of VCOs
N_VCFS		equ		2					; number of VCFs
N_LFOS		equ		3					; number of LFOs
N_ENVS		equ		4					; number of ENVs

N_FMODS		equ		12					; number of fixed MODs
N_UMODS		equ		12					; number of user MODs

N_MODS		equ		(N_UMODS + N_FMODS)	; total number of MODs / VOICE

UM_NUM_PARAM		equ		66					; number of MOD destinations
N_DSTS				equ		UM_NUM_PARAM

VT_NUM_PARAM		equ		112					; number of values
N_VALS				equ		VT_NUM_PARAM		; number of values

TT_LEN				equ		128					; number of tuning table entries

;+;	struct voice -------------------------------------------------------------

	%strdef	voice

	%mbyte	voice_vtrig
	%mbyte	voice_vgate

	%mbyte	voice_legato
	%mbyte	voice_port

	%mbyte	voice_pedal
	%mbyte	voice_tuning

	%mword	voice_m_level
	%mword	voice_p_level
	%mword	voice_m_pan
	%mword	voice_p_pan
	%mword	voice_v_pan

	%mword	voice_vel
	%mword	voice_note
	%mword	voice_note1
	%mword	voice_note2

	%mword	voice_trans
	%mword	voice_offset
	%mword	voice_pwsens

	%mword	voice_note_ons
	%mword	voice_inverts

	%marray	N_VCOS, vco_size, voice_vcos
	%marray	N_VCFS, vcf_size, voice_vcfs
	%marray	N_LFOS, lfo_size, voice_lfos
	%marray	N_ENVS, env_size, voice_envs
	%marray	N_MODS, mod_size, voice_mods

	%marray	N_DSTS, WORDS, voice_dstptr

	%marray	N_VALS, WORDS, voice_curval
	%marray	N_VALS, WORDS, voice_outval

	%marray	TT_LEN, WORDS, voice_tunetab
	%enddef	voice

; The End
