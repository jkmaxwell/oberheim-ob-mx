;+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+;	File:		VOICE.INC
;+;	Purpose:	OB-MX include file for assembly modules
;+;	Original:		1993-05-26	D.N. Lynx Crowe
;+;	Revision:	70	1993-12-06	D.N. Lynx Crowe
;+;
;+; WARNING:	These definitions MUST match those in voice.h
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

;+ --- idlpd instruction keys ---

IDLE_KEY	equ			1

;+ --- OB-MX hardware equates  ---

FMASK		equ		07FFH		; FIFO length mask  (see WARNING below)

;+ ---------------------------------------------------------------------------
;+	WARNING: the code relies on the length of ipc_fifo being a power of 2.
;+	----
;+	The code will break if the length of ipc_fifo[] is changed to a value
;+	which isn't a power of 2, or if FMASK doesn't match the length.
;+ ---------------------------------------------------------------------------

VACTL		equ			0FF00H		; Voice A oscillator controls
VBCTL		equ			0FF80H		; Voice B oscillator controls

DAC_BASE	equ			0FD00H		; DAC base address
UPDATE_DAC	equ			0FE00H		; DAC update address
UPDATE_SH	equ			0FE80H		; S/H update address

;+ --- hardware QuadPot addresses ---

QP_A			equ		050H		; QuadPot A
QP_B			equ		051H		; QuadPot B
QP_C			equ		052H		; QuadPot C
QP_D			equ		053H		; QuadPot D

;+ --- sizes of storage units

BYTES			equ		1					; sizeof(BYTE)
ADDRS			equ		2					; sizeof(ADDR)
INTS			equ		2					; sizeof(INT)
WORDS			equ		2					; sizeof(WORD)
DWORDS			equ		4					; sizeof(DWORD)

;+ --- hardware CV numbers ---

HW_MM_IN1		equ		0
HW_OB_IN1		equ		1
HW_MM_IN2		equ		2
HW_OB_IN2		equ		3
HW_MM_NOISE		equ		4
HW_OB_NOISE		equ		5
HW_MM_RESON		equ		6
HW_OB_RESON		equ		7
HW_VCO1_PW		equ		8
HW_MIX_MM		equ		9
HW_VCO2_PW		equ		10
HW_MIX_LP		equ		11
HW_VCO1_FM		equ		12
HW_MIX_BP		equ		13
HW_VCO2_FM		equ		14
HW_MIX_HP		equ		15
HW_VCO1_PITCH	equ		16
HW_VCO1_FINE	equ		17
HW_VCO2_PITCH	equ		18
HW_VCO2_FINE	equ		19
HW_MM_FREQ		equ		20
HW_MM_FINE		equ		21
HW_OB_FREQ		equ		22
HW_OB_FINE		equ		23
HW_VCA			equ		24
HW_SPARE1		equ		25
HW_PAN			equ		26
HW_SPARE2		equ		27
HW_NC_1			equ		28
HW_NC_2			equ		29
HW_NC_3			equ		30
HW_NC_4			equ		31

NO_DAC			equ		HW_NC_4

BIT_BUCKET		equ		63

;+ --- preset parameter numbers ---

VCO1_PITCH		equ	 0
VCO1_FINE		equ	 1
VCO1_TRACK		equ	 2
VCO1_PORT		equ	 3
VCO1_PWIDTH		equ	 4
VCO1_SHAPE		equ	 5
VCO1_VCO2FM		equ	 6
VCO1_ENV1FM		equ	 7
VCO1_LFO1FM		equ	 8
VCO1_PWM		equ	 9

VCO2_PITCH		equ	10
VCO2_FINE		equ	11
VCO2_TRACK		equ	12
VCO2_PORT		equ	13
VCO2_PWIDTH		equ	14
VCO2_SHAPE		equ	15
VCO2_VCO1FM		equ	16
VCO2_ENV1FM		equ	17
VCO2_LFO1FM		equ	18
VCO2_PWM		equ	19

MM_VCO1			equ	20
MM_VCO2			equ	21
MM_NOISE		equ	22
MM_FREQ			equ	23
MM_RESON		equ	24
MM_ENV1FM		equ	25
MM_LFO1FM		equ	26
MM_TRACK		equ	27

OB_VCO1			equ	28
OB_VCO2			equ	29
OB_NOISE		equ	30
OB_FREQ			equ	31
OB_RESON		equ	32
OB_ENV2FM		equ	33
OB_LFO2FM		equ	34
OB_TRACK		equ	35

LFO1_DELAY		equ	36
LFO1_RATE		equ	37
LFO1_OFFSET		equ	38
LFO1_S_H		equ	39
LFO1_SHAPE		equ	40

LFO2_DELAY		equ	41
LFO2_RATE		equ	42
LFO2_OFFSET		equ	43
LFO2_S_H		equ	44
LFO2_SHAPE		equ	45

LFO3_DELAY		equ	46
LFO3_RATE		equ	47
LFO3_OFFSET		equ	48
LFO3_S_H		equ	49
LFO3_SHAPE		equ	50

ENV1_MODE		equ	51
ENV1_ATTACK		equ	52
ENV1_ATCK_DEL	equ	53
ENV1_DECAY		equ	54
ENV1_DCAY_DEL	equ	55
ENV1_SUSTAIN	equ	56
ENV1_SUS_DCAY	equ	57
ENV1_RELEASE	equ	58
ENV1_VEL_SENS	equ	59

ENV2_MODE		equ	60
ENV2_ATTACK		equ	61
ENV2_ATCK_DEL	equ	62
ENV2_DECAY		equ	63
ENV2_DCAY_DEL	equ	64
ENV2_SUSTAIN	equ	65
ENV2_SUS_DCAY	equ	66
ENV2_RELEASE	equ	67
ENV2_VEL_SENS	equ	68

ENV3_MODE		equ	69
ENV3_ATTACK		equ	70
ENV3_ATCK_DEL	equ	71
ENV3_DECAY		equ	72
ENV3_DCAY_DEL	equ	73
ENV3_SUSTAIN	equ	74
ENV3_SUS_DCAY	equ	75
ENV3_RELEASE	equ	76
ENV3_VEL_SENS	equ	77

ENV4_MODE		equ	78
ENV4_ATTACK		equ	79
ENV4_ATCK_DEL	equ	80
ENV4_DECAY		equ	81
ENV4_DCAY_DEL	equ	82
ENV4_SUSTAIN	equ	83
ENV4_SUS_DCAY	equ	84
ENV4_RELEASE	equ	85
ENV4_VEL_SENS	equ	86

MIX_LP			equ	87
MIX_BP			equ	88
MIX_HP			equ	89
MIX_MM			equ	90
MIX_PAN			equ	91
MIX_LEVEL		equ	92

NUM_PARAM		equ	93					; number of user parameters

;+;	struct vco ---------------------------------------------------------------

	%strdef	vco

	%mbyte	vco_pitch
	%mbyte	vco_fine
	%mbyte	vco_track
	%mbyte	vco_port
	%mbyte	vco_pwidth
	%mbyte	vco_wshape
	%mbyte	vco_vcofm
	%mbyte	vco_env1fm
	%mbyte	vco_lfo1fm
	%mbyte	vco_pwm

	%mword	vco_ptcnt
	%mword	vco_ptick
	%mword	vco_pincl
	%mword	vco_pinch
	%mword	vco_paccl
	%mword	vco_pacch
	%mword	vco_pdiff
	%enddef	vco

VCO_PLS		equ		001H
VCO_TRI		equ		002H
VCO_SAW		equ		004H
VCO_SYNC	equ		008H

N_VCOS		equ		2					; number of VCOs

VCO_1		equ		0
VCO_2		equ		1

;+;	struct vcf ---------------------------------------------------------------

	%strdef	vcf

	%mbyte	vcf_vco1
	%mbyte	vcf_vco2
	%mbyte	vcf_noise
	%mbyte	vcf_freq
	%mbyte	vcf_reson
	%mbyte	vcf_envfm
	%mbyte	vcf_lfofm
	%mbyte	vcf_kbtrk
	%enddef	vcf

N_VCFS		equ		2					; number of VCFs

MM_VCF		equ		0
OB_VCF		equ		1

;+;	struct lfo ---------------------------------------------------------------

	%strdef	lfo

	%mbyte	lfo_delay
	%mbyte	lfo_rate
	%mbyte	lfo_offset
	%mbyte	lfo_quant
	%mbyte	lfo_shape
	%mbyte	lfo_lpad

	%mword	lfo_tcnt
	%mword	lfo_tick
	%mword	lfo_dtcnt
	%mword	lfo_dtick
	%mword	lfo_cntr
	%mword	lfo_dcntr
	%mword	lfo_rand
	%mword	lfo_vold
	%mword	lfo_vnew
	%enddef	lfo

;+ --- values in lfo_shape ---

LFO_RAMP	equ		0
LFO_SAW		equ		1
LFO_TRI		equ		2
LFO_RAND	equ		3

;+ ---

N_LFOS		equ		3					; number of LFOs

LFO_1		equ		0
LFO_2		equ		1
LFO_3		equ		2

;+;	struct env ---------------------------------------------------------------

	%strdef	env

	%mbyte	env_mode
	%mbyte	env_attack
	%mbyte	env_atck_del
	%mbyte	env_decay
	%mbyte	env_dcay_del
	%mbyte	env_sustain
	%mbyte	env_sus_dcay
	%mbyte	env_release
	%mbyte	env_vel_sens
	%mbyte	env_estep

	%mword	env_etcnt
	%mword	env_etick
	%mword	env_eincr
	%mword	env_ecntr
	%mword	env_current
	%mword	env_s_vel

	%maddr	env_p_vcur
	%maddr	env_p_vout
	%maddr	env_p_attack
	%maddr	env_p_atck_del
	%maddr	env_p_decay
	%maddr	env_p_dcay_del
	%maddr	env_p_sustain
	%maddr	env_p_sus_dcay
	%maddr	env_p_release
	%maddr	env_p_vel_sens
	%enddef	env

;+ --- bits in env_mode ---

ENV_FREE	equ		001H
ENV_RESET	equ		002H
ENV_REPEAT	equ		004H
ENV_TRACK	equ		008H
ENV_GATE	equ		010H
ENV_CYCLE	equ		080H

;+ --- BIT NUMBERS in env_mode ---

ENV_M_TRACK		equ		0
ENV_M_REPEAT	equ		1
ENV_M_RESET		equ		2
ENV_M_FREE		equ		3
ENV_M_GATE		equ		4
ENV_M_CYCLE		equ		7

;+ ---

N_ENVS		equ		4					; number of ENVs

ENV_1		equ		0
ENV_2		equ		1
ENV_3		equ		2
ENV_4		equ		3

;+;	struct mod ---------------------------------------------------------------

	%strdef	mod

	%mword	mod_flg
	%mbyte	mod_src
	%mbyte	mod_dst
	%mint	mod_mlt
	%maddr	mod_srp
	%maddr	mod_dsp
	%maddr	mod_cvp
	%maddr	mod_dac
	%maddr	mod_nxd
	%enddef	mod

;+ --- bits in mod_flg ---

DT_GENL		equ		01H					; general destination
DT_TIME		equ		02H					; time destination
DT_RATE		equ		04H					; rate destination
DT_FREQ		equ		08H					; frequency/pitch destination

DT_MASK		equ		0FF00H				; dst_typ[] mask

;+ --- BIT NUMBERS in mod_flg ---

DB_GENL		equ		0					; general destination
DB_TIME		equ		1					; time destination
DB_RATE		equ		2					; rate destination
DB_FREQ		equ		3					; frequency/pitch destination

;+ ---

N_FMODS		equ		12					; number of fixed MODs
N_UMODS		equ		12					; number of user MODs

N_MODS		equ		(N_UMODS + N_FMODS)	; total number of MODs / VOICE

;+ --- modulation destinations ---

UM_NONE				equ	 0	;					user		

UM_VCO1_PITCH		equ	 1	;	HW_VCO1_PITCH	user	fixed
UM_VCO1_PORT		equ	 2	;					user		
UM_VCO1_PWIDTH		equ	 3	;	HW_VCO1_PW		user	fixed
UM_VCO1_VCO2FM		equ	 4	;	HW_VCO1_FM		user		
UM_VCO1_ENV1FM		equ	 5	;	HW_VCO1_PITCH	user	fixed
UM_VCO1_LFO1FM		equ	 6	;	HW_VCO1_PITCH	user	fixed

UM_VCO2_PITCH		equ	 7	;	HW_VCO2_PITCH	user	fixed
UM_VCO2_PORT		equ	 8	;					user		
UM_VCO2_PWIDTH		equ	 9	;	HW_VCO2_PW		user	fixed
UM_VCO2_VCO1FM		equ	10	;	HW_VCO2_FM		user		
UM_VCO2_ENV1FM		equ	11	;	HW_VCO2_PITCH	user	fixed
UM_VCO2_LFO1FM		equ	12	;	HW_VCO2_PITCH	user	fixed

UM_MM_VCO1			equ	13	;	HW_MM_IN1		user		
UM_MM_VCO2			equ	14	;	HW_MM_IN2		user		
UM_MM_NOISE			equ	15	;	HW_MM_NOISE		user		
UM_MM_FREQ			equ	16	;	HW_MM_FREQ		user	fixed
UM_MM_RESON			equ	17	;	HW_MM_RESON		user		
UM_MM_ENV1FM		equ	18	;					user		
UM_MM_LFO1FM		equ	19	;			 		user		

UM_OB_VCO1			equ	20	;	HW_OB_IN1		user		
UM_OB_VCO2			equ	21	;	HW_OB_IN2		user		
UM_OB_NOISE			equ	22	;	HW_OB_NOISE		user		
UM_OB_FREQ			equ	23	;	HW_OB_FREQ		user	fixed
UM_OB_RESON			equ	24	;	HW_OB_RESON		user		
UM_OB_ENV2FM		equ	25	;					user		
UM_OB_LFO2FM		equ	26	;					user		

UM_MIX_MM			equ	27	;	HW_MIX_MM		user		
UM_MIX_LP			equ	28	;	HW_MIX_LP		user		
UM_MIX_BP			equ	29	;	HW_MIX_BP		user		
UM_MIX_HP			equ	30	;	HW_MIX_HP		user		
UM_MIX_PAN			equ	31	;	HW_PAN			user		
UM_MIX_VCA			equ	32	;	HW_VCA	 		    	fixed

UM_LFO1_DELAY		equ	33	;					user		
UM_LFO1_RATE		equ	34	;					user		
UM_LFO1_QUANT		equ	35	;					user		

UM_LFO2_DELAY		equ	36	;					user		
UM_LFO2_RATE		equ	37	;					user		
UM_LFO2_QUANT		equ	38	;					user		

UM_LFO3_DELAY		equ	39	;					user		
UM_LFO3_RATE		equ	40	;					user		
UM_LFO3_QUANT		equ	41	;					user		

UM_ENV1_ATTACK		equ	42	;					user		
UM_ENV1_ATCK_DEL	equ	43	;					user		
UM_ENV1_DECAY		equ	44	;					user		
UM_ENV1_DCAY_DEL	equ	45	;					user		
UM_ENV1_SUSTAIN		equ	46	;					user		
UM_ENV1_RELEASE		equ	47	;					user		

UM_ENV2_ATTACK		equ	48	;					user		
UM_ENV2_ATCK_DEL	equ	49	;					user		
UM_ENV2_DECAY		equ	50	;					user		
UM_ENV2_DCAY_DEL	equ	51	;					user		
UM_ENV2_SUSTAIN		equ	52	;					user		
UM_ENV2_RELEASE		equ	53	;					user		

UM_ENV3_ATTACK		equ	54	;					user		
UM_ENV3_ATCK_DEL	equ	55	;					user		
UM_ENV3_DECAY		equ	56	;					user		
UM_ENV3_DCAY_DEL	equ	57	;					user		
UM_ENV3_SUSTAIN		equ	58	;					user		
UM_ENV3_RELEASE		equ	59	;					user		

UM_ENV4_ATTACK		equ	60	;					user		
UM_ENV4_ATCK_DEL	equ	61	;					user		
UM_ENV4_DECAY		equ	62	;					user		
UM_ENV4_DCAY_DEL	equ 63	;					user		
UM_ENV4_SUSTAIN		equ	64	;					user		
UM_ENV4_RELEASE		equ	65	;					user		

UM_NUM_PARAM		equ		66					; number of MOD destinations
N_DSTS				equ		UM_NUM_PARAM

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

;+ --- bits in voice_inverts ---

M_INV_VEL			equ		00001H				; inverts: velocity invert

;+ ---

N_VOCS				equ		2					; number of VOICEs

VLEN				equ		voice_size

VA					equ		0
VB					equ		1

;+ --- value table indices ---

VT_NONE				equ		  0

VT_PP_PRESSURE		equ		  1
VT_PP_VELOCITY		equ		  2
VT_PP_NOTE			equ		  3
VT_PP_MODWHL		equ		  4
VT_PP_PITCHWHL		equ		  5
VT_PP_BREATH		equ		  6
VT_PP_PEDAL			equ		  7
VT_PP_VOLUME		equ		  8

VT_PP_MIDI_A		equ		  9
VT_PP_MIDI_B		equ		 10
VT_PP_MIDI_C		equ		 11
VT_PP_MIDI_D		equ		 12

VT_PP_LFO1			equ		 13
VT_PP_LFO2			equ		 14
VT_PP_LFO3			equ		 15

VT_PP_ENV1			equ		 16
VT_PP_ENV2			equ		 17
VT_PP_ENV3			equ		 18
VT_PP_ENV4			equ		 19

VT_PP_RANDOM		equ		 20

VT_VCO1_PITCH		equ		 21
VT_VCO1_FINE		equ		 22
VT_VCO1_TRACK		equ		 23
VT_VCO1_PORT		equ		 24
VT_VCO1_PWIDTH		equ		 25
VT_VCO1_VCO2FM		equ		 26
VT_VCO1_ENV1FM		equ		 27
VT_VCO1_LFO1FM		equ		 28
VT_VCO1_PWM			equ		 29

VT_VCO2_PITCH		equ		 30
VT_VCO2_FINE		equ		 31
VT_VCO2_TRACK		equ		 32
VT_VCO2_PORT		equ		 33
VT_VCO2_PWIDTH		equ		 34
VT_VCO2_VCO1FM		equ		 35
VT_VCO2_ENV1FM		equ		 36
VT_VCO2_LFO1FM		equ		 37
VT_VCO2_PWM			equ		 38

VT_MM_VCO1			equ		 39
VT_MM_VCO2			equ		 40
VT_MM_NOISE			equ		 41
VT_MM_FREQ			equ		 42
VT_MM_RESON			equ		 43
VT_MM_ENV1FM		equ		 44
VT_MM_LFO1FM		equ		 45
VT_MM_TRACK			equ		 46

VT_OB_VCO1			equ		 47
VT_OB_VCO2			equ		 48
VT_OB_NOISE			equ		 49
VT_OB_FREQ			equ		 50
VT_OB_RESON			equ		 51
VT_OB_ENV2FM		equ		 52
VT_OB_LFO2FM		equ		 53
VT_OB_TRACK			equ		 54

VT_LFO1_DELAY		equ		 55
VT_LFO1_RATE		equ		 56
VT_LFO1_OFFSET		equ		 57
VT_LFO1_S_H			equ		 58

VT_LFO2_DELAY		equ		 59
VT_LFO2_RATE		equ		 60
VT_LFO2_OFFSET		equ		 61
VT_LFO2_S_H			equ		 62

VT_LFO3_DELAY		equ		 63
VT_LFO3_RATE		equ		 64
VT_LFO3_OFFSET		equ		 65
VT_LFO3_S_H			equ		 66

VT_ENV1_ATTACK		equ		 67
VT_ENV1_ATCK_DEL	equ		 68
VT_ENV1_DECAY		equ		 69
VT_ENV1_DCAY_DEL	equ		 70
VT_ENV1_SUSTAIN		equ		 71
VT_ENV1_SUS_DCAY	equ		 72
VT_ENV1_RELEASE		equ		 73
VT_ENV1_VEL_SENS	equ		 74

VT_ENV2_ATTACK		equ		 75
VT_ENV2_ATCK_DEL	equ		 76
VT_ENV2_DECAY		equ		 77
VT_ENV2_DCAY_DEL	equ		 78
VT_ENV2_SUSTAIN		equ		 79
VT_ENV2_SUS_DCAY	equ		 80
VT_ENV2_RELEASE		equ		 81
VT_ENV2_VEL_SENS	equ		 82

VT_ENV3_ATTACK		equ		 83
VT_ENV3_ATCK_DEL	equ		 84
VT_ENV3_DECAY		equ		 85
VT_ENV3_DCAY_DEL	equ		 86
VT_ENV3_SUSTAIN		equ		 87
VT_ENV3_SUS_DCAY	equ		 88
VT_ENV3_RELEASE		equ		 89
VT_ENV3_VEL_SENS	equ		 90

VT_ENV4_ATTACK		equ		 91
VT_ENV4_ATCK_DEL	equ		 92
VT_ENV4_DECAY		equ		 93
VT_ENV4_DCAY_DEL	equ		 94
VT_ENV4_SUSTAIN		equ		 95
VT_ENV4_SUS_DCAY	equ		 96
VT_ENV4_RELEASE		equ		 97
VT_ENV4_VEL_SENS	equ		 98

VT_MIX_LP			equ		 99
VT_MIX_BP			equ		100
VT_MIX_HP			equ		101
VT_MIX_MM			equ		102
VT_MIX_PAN			equ		103
VT_MIX_LEVEL		equ		104

VT_VCO1_ADJUST		equ		105
VT_VCO2_ADJUST		equ		106
VT_MM_ADJUST		equ		107
VT_OB_ADJUST		equ		108
VT_VCO1_CNOTE		equ		109
VT_VCO2_CNOTE		equ		110
VT_TRANSPOSE		equ		111

VT_NUM_PARAM		equ		112					; number of values
N_VALS				equ		VT_NUM_PARAM		; number of values

;+ -- performance parameters ---

PP_NONE				equ		VT_NONE				;  0 NONE       
PP_PRESSURE			equ		VT_PP_PRESSURE		;  1 Pressure PP
PP_VELOCITY			equ		VT_PP_VELOCITY		;  2 Velocity PP
PP_NOTE				equ		VT_PP_NOTE			;  3 Note #   PP
PP_MODWHL			equ		VT_PP_MODWHL		;  4 ModWheel PP
PP_PITCHWHL			equ		VT_PP_PITCHWHL		;  5 PitchWhl PP
PP_BREATH			equ		VT_PP_BREATH		;  6 Breath   PP
PP_PEDAL			equ		VT_PP_PEDAL			;  7 Pedal    PP
PP_VOLUME			equ		VT_PP_VOLUME		;  8 Volume   PP
PP_MIDI_A			equ		VT_PP_MIDI_A		;  9 MIDI A   PP
PP_MIDI_B			equ		VT_PP_MIDI_B		; 10 MIDI B   PP
PP_MIDI_C			equ		VT_PP_MIDI_C		; 11 MIDI C   PP
PP_MIDI_D			equ		VT_PP_MIDI_D		; 12 MIDI D   PP

PP_LFO1				equ		VT_PP_LFO1			; 13 LFO 1    INT
PP_LFO2				equ		VT_PP_LFO2			; 14 LFO 2    INT
PP_LFO3				equ		VT_PP_LFO3			; 15 LFO 3    INT
PP_ENV1				equ		VT_PP_ENV1			; 16 EnvGen 1 INT
PP_ENV2				equ		VT_PP_ENV2			; 17 EnvGen 2 INT
PP_ENV3				equ		VT_PP_ENV3			; 18 EnvGen 3 INT
PP_ENV4				equ		VT_PP_ENV4			; 19 EnvGen 4 INT
PP_RANDOM			equ		VT_PP_RANDOM		; 20 Random   INT

PP_SUST_P			equ		21					; 21 Sustain Footswitch
PP_PORT_P			equ		22					; 22 Portamento Footswitch

PP_PAN				equ		23					; 23 Pan

PP_NUM_PARAM		equ		24					; number of MOD sources
N_SRCS				equ		PP_NUM_PARAM		; number of MOD sources

; The End
