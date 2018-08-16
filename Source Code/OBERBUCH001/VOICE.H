/*
   ========================================================================
	File:		VOICE.H

	Purpose:	OB-MX C header file

	Original:		1993-05-26	D.N. Lynx Crowe

	Revision:	69	1993-12-01	D.N. Lynx Crowe

	WARNING:	These definitions MUST match those in voice.inc
   ========================================================================
*/

#include <io8096.h>

/* =========================== defined types ============================== */

typedef unsigned char	BYTE;		/*  8 bit unsigned value */
typedef signed char		S_BYTE;		/*  8 bit signed value */

typedef unsigned short	WORD;		/* 16 bit unsigned value */
typedef short			INT;		/* 16 bit signed value */

typedef long			DWORD;		/* 32 bit unsigned value */

typedef					(*ADDR)();	/* 16 bit function address */

/* boolean values */

#define	TRUE	1
#define	FALSE	0

/* ========================= relational operators ========================= */

#define	EQ	==
#define	NE	!=
#define	GE	>=
#define	LE	<=
#define	GT	>
#define	LT	<

/* ========================== logical operators =========================== */

#define	NOT	!
#define	AND	&&
#define	OR	||

/* ======================= infinite loop construct ======================== */

#ifndef	FOREVER
#define	FOREVER	for(;;)
#endif

/* ======================= OB-MX hardware equates ========================= */

#define	FMASK	0x07FF				/* IPC input FIFO index mask */

/* WARNING:  FMASK must match the allocation for ipc_fifo[] */

#define	VA_CTL	(*(BYTE *) 0xFF00)	/* VOICE A control bits */
#define	VB_CTL	(*(BYTE *) 0xFF80)	/* VOICE B control bits */

#define	MAPLEN	128					/* length of preset to DAC map */

#define	QP_A	0x50				/* QuadPot A Serial Device Address */

#define	A_MM_FRQ_TRIM	0			/* Voice A MM_VCF frequency offset */
#define	A_OB_RES_TRIM	1			/* Voice A OB_VCF resonance scaling */
#define	A_OB_FRQ_TRIM	2			/* Voice A OB_VCF frequency offset */
#define	A_MM_RES_TRIM	3			/* Voice A MM_VCF resonance scaling */

#define	QP_B	0x51				/* QuadPot B Serial Device Address */

#define	B_MM_FRQ_TRIM	0			/* Voice B MM_VCF frequency offset */
#define	B_OB_RES_TRIM	1			/* Voice B OB_VCF resonance scaling */
#define	B_OB_FRQ_TRIM	2			/* Voice B OB_VCF frequency offset */
#define	B_MM_RES_TRIM	3			/* Voice B MM_VCF resonance scaling */

#define	QP_C	0x52				/* QuadPot C Serial Device Address */

#define	A_VCO1_LIN_TRIM	0			/* Voice A VCO1 linearity */
#define	B_VCO1_LIN_TRIM	1			/* Voice B VCO1 linearity */
#define	A_VCO2_LIN_TRIM	2			/* Voice A VCO2 linearity */
#define	B_VCO2_LIN_TRIM	3			/* Voice B VCO2 linearity */

#define	QP_D	0x53				/* QuadPot D Serial Device Address */

#define	A_VCO1_OFF_TRIM	0			/* Voice A VCO1 frequency offset */
#define	B_VCO1_OFF_TRIM	1			/* Voice B VCO1 frequency offset */
#define	A_VCO2_OFF_TRIM	2			/* Voice A VCO2 frequency offset */
#define	B_VCO2_OFF_TRIM	3			/* Voice B VCO2 frequency offset */

/* =================== hardware Control Voltage numbers =================== */

#define	HW_MM_IN1		0
#define	HW_OB_IN1		1
#define	HW_MM_IN2		2
#define	HW_OB_IN2		3
#define	HW_MM_NOISE		4
#define	HW_OB_NOISE		5
#define	HW_MM_RESON		6
#define	HW_OB_RESON		7
#define	HW_VCO1_PW		8
#define	HW_MIX_MM		9
#define	HW_VCO2_PW		10
#define	HW_MIX_LP		11
#define	HW_VCO1_FM		12
#define	HW_MIX_BP		13
#define	HW_VCO2_FM		14
#define	HW_MIX_HP		15
#define	HW_VCO1_PITCH	16
#define	HW_VCO1_FINE	17
#define	HW_VCO2_PITCH	18
#define	HW_VCO2_FINE	19
#define	HW_MM_FREQ		20
#define	HW_MM_FINE		21
#define	HW_OB_FREQ		22
#define	HW_OB_FINE		23
#define	HW_VCA			24
#define	HW_SPARE1		25		/* goes nowhere useful */
#define	HW_PAN			26
#define	HW_SPARE2		27		/* goes nowhere useful */
#define	HW_NC_1			28		/* goes nowhere, no S/H here */
#define	HW_NC_2			29		/* goes nowhere, no S/H here */
#define	HW_NC_3			30		/* goes nowhere, no S/H here */
#define	HW_NC_4			31		/* goes nowhere, no S/H here */

#define	NO_DAC		HW_NC_4		/* DAC garbage slot - ye old bit bucket */

/* =================== Control Voltage table indices ====================== */

#define	CV_A_V1_SCL		33
#define	CV_B_V1_SCL		35
#define	CV_A_V2_SCL		37
#define	CV_B_V2_SCL		39

#define	CV_A_MM_SCL		41
#define	CV_B_MM_SCL		43
#define	CV_A_OB_SCL		45
#define	CV_B_OB_SCL		47

#define	CV_A_VCA		48
#define	CV_B_VCA		50

#define	BIT_BUCKET		63

/* =================== instrument parameter definitions =================== */

/* ************************************************************************ */
/* ***** WARNING: CHANGING THE FOLLOWING ENUM WILL BREAK EVERYTHING! ****** */
/* ************************************************************************ */

enum {

	/* -------- VCOs -------- */

	VCO1_PITCH,			/*  0 */
	VCO1_FINE,			/*  1 */
	VCO1_TRACK,			/*  2 */
	VCO1_PORT,			/*  3 */
	VCO1_PWIDTH,		/*  4 */
	VCO1_SHAPE,			/*  5 */
	VCO1_VCO2FM,		/*  6 */
	VCO1_ENV1FM,		/*  7 */
	VCO1_LFO1FM,		/*  8 */
	VCO1_PWM,			/*  9 */

	VCO2_PITCH,			/* 10 */
	VCO2_FINE,			/* 11 */
	VCO2_TRACK,			/* 12 */
	VCO2_PORT,			/* 13 */
	VCO2_PWIDTH,		/* 14 */
	VCO2_SHAPE,			/* 15 */
	VCO2_VCO1FM,		/* 16 */
	VCO2_ENV1FM,		/* 17 */
	VCO2_LFO1FM,		/* 18 */
	VCO2_PWM,			/* 19 */

	/* -------- VCFs -------- */

	MM_VCO1,			/* 20 */
	MM_VCO2,			/* 21 */
	MM_NOISE,			/* 22 */
	MM_FREQ,			/* 23 */
	MM_RESON,			/* 24 */
	MM_ENV1FM,			/* 25 */
	MM_LFO1FM,			/* 26 */
	MM_TRACK,			/* 27 */

	OB_VCO1,			/* 28 */
	OB_VCO2,			/* 29 */
	OB_NOISE,			/* 30 */
	OB_FREQ,			/* 31 */
	OB_RESON,			/* 32 */
	OB_ENV2FM,			/* 33 */
	OB_LFO2FM,			/* 34 */
	OB_TRACK,			/* 35 */

	/* -------- LFOs -------- */

	LFO1_DELAY,			/* 36 */
	LFO1_RATE,			/* 37 */
	LFO1_OFFSET,		/* 38 */
	LFO1_S_H,			/* 39 */
	LFO1_SHAPE,			/* 40 */

	LFO2_DELAY,			/* 41 */
	LFO2_RATE,			/* 42 */
	LFO2_OFFSET,		/* 43 */
	LFO2_S_H,			/* 44 */
	LFO2_SHAPE,			/* 45 */

	LFO3_DELAY,			/* 46 */
	LFO3_RATE,			/* 47 */
	LFO3_OFFSET,		/* 48 */
	LFO3_S_H,			/* 49 */
	LFO3_SHAPE,			/* 50 */

	/* -------- ENVs -------- */

	ENV1_MODE,			/* 51 */
	ENV1_ATTACK,		/* 52 */
	ENV1_ATCK_DEL,		/* 53 */
	ENV1_DECAY,			/* 54 */
	ENV1_DCAY_DEL,		/* 55 */
	ENV1_SUSTAIN,		/* 56 */
	ENV1_SUS_DCAY,		/* 57 */
	ENV1_RELEASE,		/* 58 */
	ENV1_VEL_SENS,		/* 59 */

	ENV2_MODE,			/* 60 */
	ENV2_ATTACK,		/* 61 */
	ENV2_ATCK_DEL,		/* 62 */
	ENV2_DECAY,			/* 63 */
	ENV2_DCAY_DEL,		/* 64 */
	ENV2_SUSTAIN,		/* 65 */
	ENV2_SUS_DCAY,		/* 66 */
	ENV2_RELEASE,		/* 67 */
	ENV2_VEL_SENS,		/* 68 */

	ENV3_MODE,			/* 69 */
	ENV3_ATTACK,		/* 70 */
	ENV3_ATCK_DEL,		/* 71 */
	ENV3_DECAY,			/* 72 */
	ENV3_DCAY_DEL,		/* 73 */
	ENV3_SUSTAIN,		/* 74 */
	ENV3_SUS_DCAY,		/* 75 */
	ENV3_RELEASE,		/* 76 */
	ENV3_VEL_SENS,		/* 77 */

	ENV4_MODE,			/* 78 */
	ENV4_ATTACK,		/* 79 */
	ENV4_ATCK_DEL,		/* 80 */
	ENV4_DECAY,			/* 81 */
	ENV4_DCAY_DEL,		/* 82 */
	ENV4_SUSTAIN,		/* 83 */
	ENV4_SUS_DCAY,		/* 84 */
	ENV4_RELEASE,		/* 85 */
	ENV4_VEL_SENS,		/* 86 */

	/* -------- MIX --------- */

	MIX_LP,				/* 87 */
	MIX_BP,				/* 88 */
	MIX_HP,				/* 89 */
	MIX_MM,				/* 90 */
	MIX_PAN,			/* 91 */
	MIX_LEVEL,			/* 92 */

	NUM_PARAM			/* 93	number of parameters defined */
};

/* =========================== VCO definitions ============================ */

struct vco {			/* VCO structure definition */

	BYTE	pitch;		/* [ 0] VCO coarse pitch						(P M ) */
	BYTE	fine;		/* [ 1] VCO fine pitch							(P M ) */
	BYTE	track;		/* [ 2] VCO keyboard tracking					(P   ) */
	BYTE	port;		/* [ 3] VCO portamento rate						(P M ) */
	BYTE	pwidth;		/* [ 4] VCO pulse width							(P M ) */
	BYTE	wshape;		/* [ 5] VCO sync and waveshape select bits		(P   ) */
	BYTE	vcofm;		/* [ 6] VCO FM from other VCO					(P M ) */
	BYTE	env1fm;		/* [ 7] VCO FM from ENV1						(P MF) */
	BYTE	lfo1fm;		/* [ 8] VCO FM from LFO1						(P MF) */
	BYTE	pwm;		/* [ 9] VCO FM from ENV2 or LFO2				(P  F) */

	WORD	ptcnt;		/* [10] VCO portamento tick count				( I  ) */
	WORD	ptick;		/* [12] VCO portamento tick counter				( I  ) */
	WORD	pincl;		/* [14] VCO portamento increment lo				( I  ) */
	WORD	pinch;		/* [16] VCO portamento increment hi				( I  ) */
	WORD	paccl;		/* [18] VCO portamento accumulator lo			( I  ) */
	WORD	pacch;		/* [20] VCO portamento accumulator hi			( I  ) */
	WORD	pdiff;		/* [22] VCO portamento note difference			( I  ) */
};

#define	VCO_PLS		0x01	/* VCO wshape pulse select			(INVERT) */
#define	VCO_TRI		0x02	/* VCO wshape triangle select		(INVERT) */
#define	VCO_SAW		0x04	/* VCO wshape sawtooth select		(INVERT) */
#define	VCO_SYNC	0x08	/* VCO wshape sync select */

#define	N_VCOS		2		/* number of VCOs */

#define	VCO_1		0		/* VCO1 index */
#define	VCO_2		1		/* VCO2 index */

#define	VCO1_BASE	VCO1_PITCH	/* base for VCO1 parameters */
#define	VCO2_BASE	VCO2_PITCH	/* base for VCO2 parameters */

#define	VCO_PITCH		0	/* VCO -- coarse pitch parameter index */
#define	VCO_FINE		1	/* VCO -- fine pitch parameter index */
#define	VCO_TRACK		2	/* VCO -- keyboard tracking parameter index */
#define	VCO_PORT		3	/* VCO -- portamento time parameter index */
#define	VCO_PWIDTH		4	/* VCO -- pulse width parameter index */
#define	VCO_SHAPE		5	/* VCO -- waveshape parameter index */
#define	VCO_VCOFM		6	/* VCO -- VCO FM parameter index */
#define	VCO_ENVFM		7	/* VCO -- ENV FM parameter index */
#define	VCO_LFOFM		8	/* VCO -- LFO FM parameter index */
#define	VCO_PWM			9	/* VCO -- pulse modulation parameter index */

/* =========================== VCF definitions =========================== */

struct vcf {			/* VCF structure definition */

	BYTE	vco1;		/* [0] VCF VCO1 input level						(P M ) */
	BYTE	vco2;		/* [1] VCF VCO2 input level						(P M ) */
	BYTE	noise;		/* [2] VCF noise input level					(P M ) */
	BYTE	freq;		/* [3] VCF frequency							(P M ) */
	BYTE	reson;		/* [4] VCF resonance							(P M ) */
	BYTE	envfm;		/* [5] VCF FM from associated ENV				(P MF) */
	BYTE	lfofm;		/* [6] VCF FM from associated LFO				(P MF) */
	BYTE	kbtrk;		/* [7] VCF keyboard tracking					(P   ) */
};

#define	N_VCFS		2		/* number of VCFs */

#define	MM_VCF		0		/* MM VCF index */
#define	OB_VCF		1		/* OB VCF index */

#define	MM_BASE		MM_VCO1		/* base for MM parameters */
#define	OB_BASE		OB_VCO1		/* base for OB parameters */

#define	VCF_VCO1	0	/* VCF -- VCO1 input level parameter index */
#define	VCF_VCO2	1	/* VCF -- VCO2 input level parameter index */
#define	VCF_NOISE	2	/* VCF -- noise input level parameter index */
#define	VCF_FREQ	3	/* VCF -- frequency parameter index */
#define	VCF_RESON	4	/* VCF -- resonance parameter index */
#define	VCF_ENVFM	5	/* VCF -- ENV FM parameter index */
#define	VCF_LFOFM	6	/* VCF -- LFO FM parameter index */
#define	VCF_TRACK	7	/* VCF -- keyboard tracking parameter index */

/* ========================== LFO definitions ============================ */

struct lfo {			/* LFO structure definition */

	BYTE	delay;		/* [ 0] LFO startup delay after trigger			(P M ) */
	BYTE	rate;		/* [ 1] LFO rate								(P M ) */
	BYTE	offset;		/* [ 2] LFO output offset						(P   ) */
	BYTE	quant;		/* [ 3] LFO quantization steps					(P M ) */
	BYTE	shape;		/* [ 4] LFO waveshape							(P   ) */
	BYTE	lpad;		/* [ 5] LFO PAD byte							( I  ) */

	WORD	tcnt;		/* [ 6] LFO tick count from r_ticks[]			( I  ) */
	WORD	tick;		/* [ 8] LFO tick counter						( I  ) */
	WORD	dtcnt;		/* [10] LFO delay tick count from l_ticks[]		( I  ) */
	WORD	dtick;		/* [12] LFO delay tick counter					( I  ) */
	WORD	cntr;		/* [14] LFO counter								( I  ) */
	WORD	dcntr;		/* [16] LFO delay counter						( I  ) */
	WORD	rand;		/* [18] LFO random value						( I  ) */
	WORD	vold;		/* [20] LFO old value							( I  ) */
	WORD	vnew;		/* [22] LFO new value							( I  ) */
};

#define	LFO_RAMP	0	/* LFO -- Ramp waveshape select */
#define	LFO_SAW		1	/* LFO -- Sawtooth waveshape select */
#define	LFO_TRI		2	/* LFO -- Triangle waveshape select */
#define	LFO_RAND	3	/* LFO -- Random waveshape select */

#define	N_LFOS		3	/* number of LFOs */

#define	LFO_1		0	/* LFO1 index */
#define	LFO_2		1	/* LFO2 index */
#define	LFO_3		2	/* LFO3 index */

#define	LFO1_BASE	LFO1_DELAY	/* base for LFO1 parameters */
#define	LFO2_BASE	LFO2_DELAY	/* base for LFO2 parameters */
#define	LFO3_BASE	LFO3_DELAY	/* base for LFO3 parameters */

#define	LFO_DELAY	0	/* LFO -- Delay parameter index */
#define	LFO_RATE	1	/* LFO -- Rate parameter index */
#define	LFO_OFFSET	2	/* LFO -- Offset parameter index */
#define	LFO_S_H		3	/* LFO -- Quantization parameter index */
#define	LFO_SHAPE	4	/* LFO -- Waveshape parameter index */

#define	INIT_LFO_RATE	94				/* 5 Hz rate */
#define	INIT_LFO_SHAPE	LFO_SAW			/* Sawtooth waveform */

/* ========================== ENV definitions ============================ */

struct env {			/* Envelope structure definition */

	BYTE	mode;			/* [ 0] ENV mode bits						(P   ) */
	BYTE	attack;			/* [ 1] ENV attack time						(P M ) */
	BYTE	atck_del;		/* [ 2] ENV attack delay time				(P M ) */
	BYTE	decay;			/* [ 3] ENV decay time						(P M ) */
	BYTE	dcay_del;		/* [ 4] ENV decay delay time				(P M ) */
	BYTE	sustain;		/* [ 5] ENV sustain value					(P M ) */
	BYTE	sus_dcay;		/* [ 6] ENV sustain decay rate				(P   ) */
	BYTE	release;		/* [ 7] ENV release time					(P M ) */
	BYTE	vel_sens;		/* [ 8] ENV pedal release time				(P   ) */
	BYTE	estep;			/* [ 9] ENV current state		 			( I  ) */

	WORD	etcnt;			/* [10] ENV tick count from t_ticks[t]		( I  ) */
	WORD	etick;			/* [12] ENV tick counter					( I  ) */
	WORD	eincr;			/* [14] ENV increment						( I  ) */
	WORD	ecntr;			/* [16] ENV counter							( I  ) */
	WORD	current;		/* [18] ENV current value					( I  ) */
	INT		s_vel;			/* [20] ENV scaled velocity					( I  ) */

	WORD	*p_vcur;		/* [22] ENV current value pointer			( I  ) */
	WORD	*p_vout;		/* [24] ENV output value pointer			( I  ) */
	WORD	*p_attack;		/* [26] ENV attack time pointer				( I  ) */
	WORD	*p_atck_del;	/* [28] ENV attack delay time pointer		( I  ) */
	WORD	*p_decay;		/* [30] ENV decay time pointer				( I  ) */
	WORD	*p_dcay_del;	/* [32] ENV decay delay time pointer		( I  ) */
	WORD	*p_sustain;		/* [34] ENV sustain value pointer			( I  ) */
	WORD	*p_sus_dcay;	/* [36] ENV sustain decay rate pointer		( I  ) */
	WORD	*p_release;		/* [38] ENV release time pointer			( I  ) */
	WORD	*p_vel_sens;	/* [40] ENV velocity sensitivity pointer	( I  ) */
};

#define	ENV_TRACK	0x01	/* ENV keyboard track */
#define	ENV_REPEAT	0x02	/* ENV repeat mode */
#define	ENV_RESET	0x04	/* ENV reset mode */
#define	ENV_FREE	0x08	/* ENV freerun mode */

#define	ENV_GATE	0x10	/* ENV GATE/!ENV4 mode */

#define	ENV_CYCLE	0x80	/* ENV cycle flag */

#define	N_ENVS		4		/* number of ENVs */

#define	ENV_1		0		/* ENV1 index */
#define	ENV_2		1		/* ENV2 index */
#define	ENV_3		2		/* ENV3 index */
#define	ENV_4		3		/* ENV4 index */

#define	ENV1_BASE	ENV1_MODE	/* base for ENV1 parameters */
#define	ENV2_BASE	ENV2_MODE	/* base for ENV2 parameters */
#define	ENV3_BASE	ENV3_MODE	/* base for ENV3 parameters */
#define	ENV4_BASE	ENV4_MODE	/* base for ENV4 parameters */

#define	ENV_MODE		0	/* ENV -- mode parameter index */
#define	ENV_ATTACK		1	/* ENV -- attack parameter index */
#define	ENV_ATCK_DEL	2	/* ENV -- attack delay parameter index */
#define	ENV_DECAY		3	/* ENV -- decay parameter index */
#define	ENV_DCAY_DEL	4	/* ENV -- decay delay parameter index */
#define	ENV_SUSTAIN		5	/* ENV -- sustain level parameter index */
#define	ENV_SUS_DCAY	6	/* ENV -- sustain decay parameter index */
#define	ENV_RELEASE		7	/* ENV -- release parameter index */
#define	ENV_VEL_SENS	8	/* ENV -- velocity sensitivity parameter index */

#define	INIT_ENV_MODE	ENV_RESET		/* reset mode */
#define	INIT_ENV_ST		ENV_STOP		/* reset state */

/* ========================== MOD definitions ============================= */

struct mod {			/* Modulation structure definition */

	WORD		flg;		/* [ 0] MOD flag word */
	BYTE		src;		/* [ 2] MOD source (SRC) index */
	BYTE		dst;		/* [ 3] MOD destination (DST) index */
	INT			mlt;		/* [ 4] MOD multiplier */
	INT			*srp;		/* [ 6] MOD &vp->outval[src] */
	INT			*dsp;		/* [ 8] MOD &vp->outval[dst] */
	INT			*cvp;		/* [10] MOD &vp->curval[dst] */
	WORD		*dac;		/* [12] MOD &cvtable[mapped_dst] */
	struct mod	*nxd;		/* [14] MOD next destination (DST) pointer */
};

#define	MOD_SRC		0		/* MOD -- source parameter index */
#define	MOD_DST		1		/* MOD -- destination parameter index */
#define	MOD_MLT		2		/* MOD -- multiplier parameter index */

#define	MOD_F_NXD	0x8000	/* MOD -- on DST list (used in mod.flg) */

/* the following defines are used in the dst_typ[] table and in mod.flg */

/* masks */

#define	DT_GENL		0x01	/* MOD -- general destination */
#define	DT_TIME		0x02	/* MOD -- time destination */
#define	DT_RATE		0x04	/* MOD -- rate destination */
#define	DT_FREQ		0x08	/* MOD -- frequency/pitch destination */

#define	DT_MASK		0xFF00	/* MOD -- dst_typ[] mask */

/* bit numbers */

#define	DB_GENL 	0		/* MOD -- general destination */
#define	DB_TIME 	1		/* MOD -- time destination */
#define	DB_RATE 	2		/* MOD -- rate destination */
#define	DB_FREQ 	3		/* MOD -- frequency/pitch destination */

/* ************************************************************************ */
/*	IMPORTANT:  Fixed MODs preceed User MODs in the mods[] table.			*/
/*																			*/
/*	Many functions depend heavily on this ...								*/
/* ************************************************************************ */

#define	N_FMODS		12						/* number of fixed MODs */
#define	N_UMODS		12						/* number of user MODs */

#define	N_MODS		(N_FMODS + N_UMODS)		/* total number of MODs */

/* ---------------------- Modulation destinations ------------------------- */

/* ************************************************************************ */
/* ***** WARNING: CHANGING THE FOLLOWING ENUM WILL BREAK EVERYTHING! ****** */
/* ************************************************************************ */

enum {

	UM_NONE,				/*  0	(bit bucket)	user			*/

	UM_VCO1_PITCH,			/*  1	HW_VCO1_PITCH	user	fixed	*/
	UM_VCO1_PORT,			/*  2					user			*/
	UM_VCO1_PWIDTH,			/*  3	HW_VCO1_PW		user	fixed	*/
	UM_VCO1_VCO2FM,			/*  4	HW_VCO1_FM		user			*/
	UM_VCO1_ENV1FM,			/*  5	HW_VCO1_PITCH	user	fixed	*/
	UM_VCO1_LFO1FM,			/*  6	HW_VCO1_PITCH	user	fixed	*/

	UM_VCO2_PITCH,			/*  7	HW_VCO2_PITCH	user	fixed	*/
	UM_VCO2_PORT,			/*  8					user			*/
	UM_VCO2_PWIDTH,			/*  9	HW_VCO2_PW		user	fixed	*/
	UM_VCO2_VCO1FM,			/* 10	HW_VCO2_FM		user			*/
	UM_VCO2_ENV1FM,			/* 11	HW_VCO2_PITCH	user	fixed	*/
	UM_VCO2_LFO1FM,			/* 12	HW_VCO2_PITCH	user	fixed	*/

	UM_MM_VCO1,				/* 13	HW_MM_IN1		user			*/
	UM_MM_VCO2,				/* 14	HW_MM_IN2		user			*/
	UM_MM_NOISE,			/* 15	HW_MM_NOISE		user			*/
	UM_MM_FREQ,				/* 16	HW_MM_FREQ		user	fixed	*/
	UM_MM_RESON,			/* 17	HW_MM_RESON		user			*/
	UM_MM_ENV1FM,			/* 18					user			*/
	UM_MM_LFO1FM,			/* 19			 		user			*/

	UM_OB_VCO1,				/* 20	HW_OB_IN1		user			*/
	UM_OB_VCO2,				/* 21	HW_OB_IN2		user			*/
	UM_OB_NOISE,			/* 22	HW_OB_NOISE		user			*/
	UM_OB_FREQ,				/* 23	HW_OB_FREQ		user	fixed	*/
	UM_OB_RESON,			/* 24	HW_OB_RESON		user			*/
	UM_OB_ENV2FM,			/* 25					user			*/
	UM_OB_LFO2FM,			/* 26					user			*/

	UM_MIX_MM,				/* 27	HW_MIX_MM		user			*/
	UM_MIX_LP,				/* 28	HW_MIX_LP		user			*/
	UM_MIX_BP,				/* 29	HW_MIX_BP		user			*/
	UM_MIX_HP,				/* 30	HW_MIX_HP		user			*/
	UM_MIX_PAN,				/* 31	HW_PAN			user			*/
	UM_MIX_VCA,				/* 32	HW_VCA	 		    	fixed	*/

	UM_LFO1_DELAY,			/* 33					user			*/
	UM_LFO1_RATE,			/* 34					user			*/
	UM_LFO1_QUANT,			/* 35					user			*/

	UM_LFO2_DELAY,			/* 36					user			*/
	UM_LFO2_RATE,			/* 37					user			*/
	UM_LFO2_QUANT,			/* 38					user			*/

	UM_LFO3_DELAY,			/* 39					user			*/
	UM_LFO3_RATE,			/* 40					user			*/
	UM_LFO3_QUANT,			/* 41					user			*/

	UM_ENV1_ATTACK,			/* 42					user			*/
	UM_ENV1_ATCK_DEL,		/* 43					user			*/
	UM_ENV1_DECAY,			/* 44					user			*/
	UM_ENV1_DCAY_DEL,		/* 45					user			*/
	UM_ENV1_SUSTAIN,		/* 46					user			*/
	UM_ENV1_RELEASE,		/* 47					user			*/

	UM_ENV2_ATTACK,			/* 48					user			*/
	UM_ENV2_ATCK_DEL,		/* 49					user			*/
	UM_ENV2_DECAY,			/* 50					user			*/
	UM_ENV2_DCAY_DEL,		/* 51					user			*/
	UM_ENV2_SUSTAIN,		/* 52					user			*/
	UM_ENV2_RELEASE,		/* 53					user			*/

	UM_ENV3_ATTACK,			/* 54					user			*/
	UM_ENV3_ATCK_DEL,		/* 55					user			*/
	UM_ENV3_DECAY,			/* 56					user			*/
	UM_ENV3_DCAY_DEL,		/* 57					user			*/
	UM_ENV3_SUSTAIN,		/* 58					user			*/
	UM_ENV3_RELEASE,		/* 59					user			*/

	UM_ENV4_ATTACK,			/* 60					user			*/
	UM_ENV4_ATCK_DEL,		/* 61					user			*/
	UM_ENV4_DECAY,			/* 62					user			*/
	UM_ENV4_DCAY_DEL,		/* 63					user			*/
	UM_ENV4_SUSTAIN,		/* 64					user			*/
	UM_ENV4_RELEASE,		/* 65					user			*/

	UM_NUM_PARAM			/* 66	number of UMs defined */
};

#define	N_DSTS	UM_NUM_PARAM

#define	NO_DST	UM_NONE

/*
   ------------------------------------------------------------------------
	The following enum values are the indices into the value tables in
	the voice structure:

		curval[]	current (unmodulated) values
		outval[]	output (modulated) values

	The sources come first in the table, then the (possible) destinations.

	Not everything can be a source or a destination, but if it has a value
	used by this instrument it most likely lives somewhere here.
   ------------------------------------------------------------------------
*/

/* ************************************************************************ */
/* ***** WARNING: CHANGING THE FOLLOWING ENUM WILL BREAK EVERYTHING! ****** */
/* ************************************************************************ */

enum {

	/* ------ NULL source -------- */

	VT_NONE,				/*   0 */

	/* ------ MIDI sources ------- */

	VT_PP_PRESSURE,			/*   1 */
	VT_PP_VELOCITY,			/*   2 */
	VT_PP_NOTE,				/*   3 */
	VT_PP_MODWHL,			/*   4 */
	VT_PP_PITCHWHL,			/*   5 */
	VT_PP_BREATH,			/*   6 */
	VT_PP_PEDAL,			/*   7 */
	VT_PP_VOLUME,			/*   8 */

	VT_PP_MIDI_A,			/*   9 */
	VT_PP_MIDI_B,			/*  10 */
	VT_PP_MIDI_C,			/*  11 */
	VT_PP_MIDI_D,			/*  12 */

	/* ------- LFO outputs ------- */

	VT_PP_LFO1,				/*  13 */
	VT_PP_LFO2,				/*  14 */
	VT_PP_LFO3,				/*  15 */

	/* ------- ENV outputs ------- */

	VT_PP_ENV1,				/*  16 */
	VT_PP_ENV2,				/*  17 */
	VT_PP_ENV3,				/*  18 */
	VT_PP_ENV4,				/*  19 */

	/* ------- misc values ------- */

	VT_PP_RANDOM,			/*  20 */

	/* ===== End of Sources ====== */

	/* ---------- VCOs ----------- */

	VT_VCO1_PITCH,			/*  21 */
	VT_VCO1_FINE,			/*  22 */
	VT_VCO1_TRACK,			/*  23 */
	VT_VCO1_PORT,			/*  24 */
	VT_VCO1_PWIDTH,			/*  25 */
	VT_VCO1_VCO2FM,			/*  26 */
	VT_VCO1_ENV1FM,			/*  27 */
	VT_VCO1_LFO1FM,			/*  28 */
	VT_VCO1_PWM,			/*  29 */

	VT_VCO2_PITCH,			/*  30 */
	VT_VCO2_FINE,			/*  31 */
	VT_VCO2_TRACK,			/*  32 */
	VT_VCO2_PORT,			/*  33 */
	VT_VCO2_PWIDTH,			/*  34 */
	VT_VCO2_VCO1FM,			/*  35 */
	VT_VCO2_ENV1FM,			/*  36 */
	VT_VCO2_LFO1FM,			/*  37 */
	VT_VCO2_PWM,			/*  38 */

	/* ---------- VCFs ----------- */

	VT_MM_VCO1,				/*  39 */
	VT_MM_VCO2,				/*  40 */
	VT_MM_NOISE,			/*  41 */
	VT_MM_FREQ,				/*  42 */
	VT_MM_RESON,			/*  43 */
	VT_MM_ENV1FM,			/*  44 */
	VT_MM_LFO1FM,			/*  45 */
	VT_MM_TRACK,			/*  46 */

	VT_OB_VCO1,				/*  47 */
	VT_OB_VCO2,				/*  48 */
	VT_OB_NOISE,			/*  49 */
	VT_OB_FREQ,				/*  50 */
	VT_OB_RESON,			/*  51 */
	VT_OB_ENV2FM,			/*  52 */
	VT_OB_LFO2FM,			/*  53 */
	VT_OB_TRACK,			/*  54 */

	/* ---------- LFOs ----------- */

	VT_LFO1_DELAY,			/*  55 */
	VT_LFO1_RATE,			/*  56 */
	VT_LFO1_OFFSET,			/*  57 */
	VT_LFO1_S_H,			/*  58 */

	VT_LFO2_DELAY,			/*  59 */
	VT_LFO2_RATE,			/*  60 */
	VT_LFO2_OFFSET,			/*  61 */
	VT_LFO2_S_H,			/*  62 */

	VT_LFO3_DELAY,			/*  63 */
	VT_LFO3_RATE,			/*  64 */
	VT_LFO3_OFFSET,			/*  65 */
	VT_LFO3_S_H,			/*  66 */

	/* ---------- ENVs ----------- */

	VT_ENV1_ATTACK,			/*  67 */
	VT_ENV1_ATCK_DEL,		/*  68 */
	VT_ENV1_DECAY,			/*  69 */
	VT_ENV1_DCAY_DEL,		/*  70 */
	VT_ENV1_SUSTAIN,		/*  71 */
	VT_ENV1_SUS_DCAY,		/*  72 */
	VT_ENV1_RELEASE,		/*  73 */
	VT_ENV1_VEL_SENS,		/*  74 */

	VT_ENV2_ATTACK,			/*  75 */
	VT_ENV2_ATCK_DEL,		/*  76 */
	VT_ENV2_DECAY,			/*  77 */
	VT_ENV2_DCAY_DEL,		/*  78 */
	VT_ENV2_SUSTAIN,		/*  79 */
	VT_ENV2_SUS_DCAY,		/*  80 */
	VT_ENV2_RELEASE,		/*  81 */
	VT_ENV2_VEL_SENS,		/*  82 */

	VT_ENV3_ATTACK,			/*  83 */
	VT_ENV3_ATCK_DEL,		/*  84 */
	VT_ENV3_DECAY,			/*  85 */
	VT_ENV3_DCAY_DEL,		/*  86 */
	VT_ENV3_SUSTAIN,		/*  87 */
	VT_ENV3_SUS_DCAY,		/*  88 */
	VT_ENV3_RELEASE,		/*  89 */
	VT_ENV3_VEL_SENS,		/*  90 */

	VT_ENV4_ATTACK,			/*  91 */
	VT_ENV4_ATCK_DEL,		/*  92 */
	VT_ENV4_DECAY,			/*  93 */
	VT_ENV4_DCAY_DEL,		/*  94 */
	VT_ENV4_SUSTAIN,		/*  95 */
	VT_ENV4_SUS_DCAY,		/*  96 */
	VT_ENV4_RELEASE,		/*  97 */
	VT_ENV4_VEL_SENS,		/*  98 */

	/* ----------- MIX ----------- */

	VT_MIX_LP,				/*  99 */
	VT_MIX_BP,				/* 100 */
	VT_MIX_HP,				/* 101 */
	VT_MIX_MM,				/* 102 */
	VT_MIX_PAN,				/* 103 */
	VT_MIX_LEVEL,			/* 104 */

	/* -------- Internal --------- */

	VT_VCO1_ADJUST,			/* 105 */
	VT_VCO2_ADJUST,			/* 106 */
	VT_MM_ADJUST,			/* 107 */
	VT_OB_ADJUST,			/* 108 */
	VT_VCO1_CNOTE,			/* 109 */
	VT_VCO2_CNOTE,			/* 110 */
	VT_TRANSPOSE,			/* 111 */

	VT_NUM_PARAM			/* 112	number of VT entries */
};

#define	N_VALS		VT_NUM_PARAM	/* number of values */

/* ---------- User Modulation Sources and Performance Parameters ---------- */

/*
   ------------------------------------------------------------------------
	User Modulation Sources make up the beginning of the value table.

	Performance Parameters are a subset of the User Modulation Sources.

	Footswitches and the Pan Pedal aren't user accessable sources,
	so they follow the User Modulation Sources as Performance Parameter
	numbers.

	Internal Sources sent as Performance Parameters are ignored.

   ------------------------------------------------------------------------
*/

#define PP_NONE			VT_NONE			/* 0	"NONE    "    */

	/* External Sources (Performance Parameters) */

#define PP_PRESSURE		VT_PP_PRESSURE	/* 1	"Pressure" PP */
#define PP_VELOCITY		VT_PP_VELOCITY	/* 2	"Velocity" PP */
#define PP_NOTE			VT_PP_NOTE		/* 3	"Note #  " PP */
#define PP_MODWHL		VT_PP_MODWHL	/* 4	"ModWheel" PP */
#define PP_PITCHWHL		VT_PP_PITCHWHL	/* 5	"PitchWhl" PP */
#define PP_BREATH		VT_PP_BREATH	/* 6	"Breath  " PP */
#define PP_PEDAL		VT_PP_PEDAL		/* 7	"Pedal   " PP */
#define PP_VOLUME		VT_PP_VOLUME	/* 8	"Volume  " PP */

#define PP_MIDI_A		VT_PP_MIDI_A	/* 9	"MIDI A  " PP */
#define PP_MIDI_B		VT_PP_MIDI_B	/* 10	"MIDI B  " PP */
#define PP_MIDI_C		VT_PP_MIDI_C	/* 11	"MIDI C  " PP */
#define PP_MIDI_D		VT_PP_MIDI_D	/* 12	"MIDI D  " PP */

	/* Internal Sources */

#define PP_LFO1			VT_PP_LFO1		/* 13	"LFO 1   " INT */
#define PP_LFO2			VT_PP_LFO2		/* 14	"LFO 2   " INT */
#define PP_LFO3			VT_PP_LFO3		/* 15	"LFO 3   " INT */

#define PP_ENV1			VT_PP_ENV1		/* 16	"EnvGen 1" INT */
#define PP_ENV2			VT_PP_ENV2		/* 17	"EnvGen 2" INT */
#define PP_ENV3			VT_PP_ENV3		/* 18	"EnvGen 3" INT */
#define PP_ENV4			VT_PP_ENV4		/* 19	"EnvGen 4" INT */

#define PP_RANDOM		VT_PP_RANDOM	/* 20	"Random  " INT */

#define	N_SRCS			21				/* 21	number of sources */

	/* Foot Switches */

#define	PP_SUST_P		21				/* 21	Sustain Footswitch */
#define	PP_PORT_P		22				/* 22	Portamento Footswitch */

	/* Other stuff */

#define	PP_PAN			23				/* 23	Pan Pedal */

	/* sizes of things, etc. */

#define PP_NUM_PARAM	24				/* 24	number of PPs defined */

#define	NO_SRC			PP_NONE			/* NULL source 		  */

/* ========================== VOICE definitions =========================== */

#define	TT_LEN			128		/* tuning table length */

struct voice {					/* VOICE structure definition */

	BYTE	vtrig;				/* [  0] VOICE trigger flag */
	BYTE	vgate;				/* [  1] VOICE gate flag */

	BYTE	legato;				/* [  2] VOICE legato mode */
	BYTE	port;				/* [  3] VOICE portamento pedal status */

	BYTE	pedal;				/* [  4] VOICE sustain pedal status */
	BYTE	tuning;				/* [  5] VOICE tuning flags */

	WORD	m_level;			/* [  6] VOICE MIDI level */
	WORD	p_level;			/* [  8] VOICE part level */
	WORD	m_pan;				/* [ 10] VOICE MIDI pan */
	WORD	p_pan;				/* [ 12] VOICE part pan */
	WORD	v_pan;				/* [ 14] VOICE pan value */

	WORD	vel;				/* [ 16] VOICE note velocity */
	WORD	note;				/* [ 18] VOICE note value */
	WORD	note1;				/* [ 20] VOICE VCO1 final note value */
	WORD	note2;				/* [ 22] VOICE VCO2 final note value */

	INT		trans;				/* [ 24] VOICE part transpose value */
	INT		offset;				/* [ 26] VOICE "A" tuning offset */
	INT		pwsens;				/* [ 28] VOICE pitch wheel sensitivity */

	WORD	note_ons;			/* [ 30] VOICE legato note on count */
	WORD	inverts;			/* [ 32] VOICE inversion flags */

	struct vco vcos[N_VCOS];	/* [ 34] VCOs */
	struct vcf vcfs[N_VCFS];	/* [   ] VCFs */
	struct lfo lfos[N_LFOS];	/* [   ] LFOs */
	struct env envs[N_ENVS];	/* [   ] ENVs */
	struct mod mods[N_MODS];	/* [   ] MODs (IMPORTANT: fixed 1st, then user) */

	struct mod *dstptr[N_DSTS];	/* [   ] VOICE MOD destination (DST) pointers */

	INT		curval[N_VALS];		/* [   ] VOICE current values */
	INT		outval[N_VALS];		/* [   ] VOICE modulated values */

	WORD	tunetab[TT_LEN];	/* [   ] VOICE tuning table */
};

#define	VA	0		/* VOICE A index */
#define	VB	1		/* VOICE B index */

#define	M_GATE		0x01		/* vgate: gate */
#define	M_UNGATE	0x80		/* vgate: ungate */

#define	M_INV_VEL	0x0001		/* inverts: velocity invert */

/* The End */
