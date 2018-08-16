/*
+++ ==========================================================================
+++	File:		TABLES1.C
+++	Purpose:	OB-MX constant tables, Part 1
+++	Original:		1993-05-26	D.N. Lynx Crowe
+++	Revision:	55	1993-12-13	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		dacmap[]		control voltage to DAC bit scramble map
+++		dst_cvn[]		destination number to CV number table
+++		dst_typ[]		destination number to value type table
+++		dst_val[]		destination number to value number table
+++		fixed_mods[]	setup data for fixed modulations
+++		par_dst[]		preset parameter number to destination number
+++		par_val[]		preset parameter number to value number table
+++		pw_scl[]		pitch wheel scaling table
+++		qpa_cmd[]		voice A quadpot pot commands
+++		qpa_pot[]		voice A quadpot pot addresses
+++		qpb_cmd[]		voice B quadpot pot commands
+++		qpb_pot[]		voice b quadpot pot addresses
+++		tuneup			tune on power up flag
+++		vco_off[]		VCO offset values for tuning A off of 440 Hz
+++		vin_tab[]		velocity inversion table
+++ ==========================================================================
*/

#include "voice.h"

/*
+++ --------------------------------------------------------------------------
+++	tuneup = 0		master card initiates power-up tuning
+++	tuneup = 1		voice card initiates power-up tuning
+++ --------------------------------------------------------------------------
*/

const	WORD	tuneup = 0;		/*+ tune on power-up flag */

/*
+++ ==========================================================================
+++	const BYTE dacmap[] -- control voltage to DAC bit scramble map
+++
+++	Used to map control voltage numbers (A00..A31,B00..B31) to DAC slots.
+++
+++	ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»
+++	º                                                                º
+++	º    DAC Value Base Address    FD00                              º
+++	º    DAC Update Address        FE00                              º
+++	º    S/H Update Address        FE80                              º
+++	º                                                                º
+++	º   ÚÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄÂÄ¿                            º
+++	º   ³1³1³1³1³1³1³0³1³0³C³C³C³C³V³D³B³                            º
+++	º   ÀÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÁÄÙ                            º
+++	º                      ÄÂÄ ÄÂÄ Â Â Â                             º
+++	º                       ³   ³  ³ ³ À Byte    (0 = LS, 1 = MS)    º
+++	º                       ³   ³  ³ ÀÄÄ DAC     (0 = A, 1 = B)      º
+++	º                       ³   ³  ÀÄÄÄÄ Voice   (0 = A, 1 = B)      º
+++	º                       ³   ÀÄÄÄÄÄÄÄ Slot                        º
+++	º                       ÀÄÄÄÄÄÄÄÄÄÄÄ S/H                         º
+++	º                                                                º
+++	ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼
+++
+++ ==========================================================================
*/

const BYTE dacmap[64] = {

	0,	/* [ 0] 00000000 = 00000000 */
	1,	/* [ 1] 00000001 = 00000001 */
	4,	/* [ 2] 00000010 = 00000100 */
	5,	/* [ 3] 00000011 = 00000101 */
	8,	/* [ 4] 00000100 = 00001000 */
	9,	/* [ 5] 00000101 = 00001001 */
	12,	/* [ 6] 00000110 = 00001100 */
	13,	/* [ 7] 00000111 = 00001101 */
	16,	/* [ 8] 00001000 = 00010000 */
	17,	/* [ 9] 00001001 = 00010001 */
	20,	/* [10] 00001010 = 00010100 */
	21,	/* [11] 00001011 = 00010101 */
	24,	/* [12] 00001100 = 00011000 */
	25,	/* [13] 00001101 = 00011001 */
	28,	/* [14] 00001110 = 00011100 */
	29,	/* [15] 00001111 = 00011101 */
	32,	/* [16] 00010000 = 00100000 */
	33,	/* [17] 00010001 = 00100001 */
	36,	/* [18] 00010010 = 00100100 */
	37,	/* [19] 00010011 = 00100101 */
	40,	/* [20] 00010100 = 00101000 */
	41,	/* [21] 00010101 = 00101001 */
	44,	/* [22] 00010110 = 00101100 */
	45,	/* [23] 00010111 = 00101101 */
	48,	/* [24] 00011000 = 00110000 */
	49,	/* [25] 00011001 = 00110001 */
	52,	/* [26] 00011010 = 00110100 */
	53,	/* [27] 00011011 = 00110101 */
	56,	/* [28] 00011100 = 00111000 */
	57,	/* [29] 00011101 = 00111001 */
	60,	/* [30] 00011110 = 00111100 */
	61,	/* [31] 00011111 = 00111101 */
	2,	/* [32] 00100000 = 00000010 */
	3,	/* [33] 00100001 = 00000011 */
	6,	/* [34] 00100010 = 00000110 */
	7,	/* [35] 00100011 = 00000111 */
	10,	/* [36] 00100100 = 00001010 */
	11,	/* [37] 00100101 = 00001011 */
	14,	/* [38] 00100110 = 00001110 */
	15,	/* [39] 00100111 = 00001111 */
	18,	/* [40] 00101000 = 00010010 */
	19,	/* [41] 00101001 = 00010011 */
	22,	/* [42] 00101010 = 00010110 */
	23,	/* [43] 00101011 = 00010111 */
	26,	/* [44] 00101100 = 00011010 */
	27,	/* [45] 00101101 = 00011011 */
	30,	/* [46] 00101110 = 00011110 */
	31,	/* [47] 00101111 = 00011111 */
	34,	/* [48] 00110000 = 00100010 */
	35,	/* [49] 00110001 = 00100011 */
	38,	/* [50] 00110010 = 00100110 */
	39,	/* [51] 00110011 = 00100111 */
	42,	/* [52] 00110100 = 00101010 */
	43,	/* [53] 00110101 = 00101011 */
	46,	/* [54] 00110110 = 00101110 */
	47,	/* [55] 00110111 = 00101111 */
	50,	/* [56] 00111000 = 00110010 */
	51,	/* [57] 00111001 = 00110011 */
	54,	/* [58] 00111010 = 00110110 */
	55,	/* [59] 00111011 = 00110111 */
	58,	/* [60] 00111100 = 00111010 */
	59,	/* [61] 00111101 = 00111011 */
	62,	/* [62] 00111110 = 00111110 */
	63	/* [63] 00111111 = 00111111 */
};

/*
+++ ==========================================================================
+++	const struct mod fixed_mods[] -- setup data for fixed modulations
+++
+++	Note:  This table is ORDER DEPENDENT -- many things depend on this...
+++ ==========================================================================
*/

const struct mod fixed_mods[N_FMODS] = {	/* fixed modulation setups */

/*	flg, src, dst, mlt, srp,dsp,cvp,dac,nxd */

	{0,	PP_LFO1, UM_VCO1_PITCH,		0, 	0,0,0,0,0},	/* [ 0] VCO1_LFO1FM */
	{0,	PP_ENV1, UM_VCO1_PITCH,		0, 	0,0,0,0,0},	/* [ 1] VCO1_ENV1FM */

	{0,	PP_LFO1, UM_VCO2_PITCH,		0, 	0,0,0,0,0},	/* [ 2] VCO2_LFO1FM */
	{0,	PP_ENV1, UM_VCO2_PITCH,		0, 	0,0,0,0,0},	/* [ 3] VCO2_ENV1FM */

	{0,	PP_LFO2, UM_VCO1_PWIDTH,	0, 	0,0,0,0,0},	/* [ 4] VCO1_PWM */
	{0,	PP_ENV2, UM_VCO1_PWIDTH,	0, 	0,0,0,0,0},	/* [ 5] VCO1_PWM */

	{0,	PP_LFO2, UM_VCO2_PWIDTH,	0, 	0,0,0,0,0},	/* [ 6] VCO2_PWM */
	{0,	PP_ENV2, UM_VCO2_PWIDTH,	0, 	0,0,0,0,0},	/* [ 7] VCO2_PWM */

	{0,	PP_LFO1, UM_MM_FREQ,		0, 	0,0,0,0,0},	/* [ 8] MM_LFO1FM */
	{0,	PP_ENV1, UM_MM_FREQ,		0, 	0,0,0,0,0},	/* [ 9] MM_ENV1FM */

	{0,	PP_LFO2, UM_OB_FREQ,		0, 	0,0,0,0,0},	/* [10] OB_LFO2FM */
	{0,	PP_ENV2, UM_OB_FREQ,		0, 	0,0,0,0,0}	/* [11] OB_ENV2FM */
};

/*
+++ ==========================================================================
+++	const BYTE dst_cvn[] -- destination number to CV number table
+++
+++	The 0xFF entry is used to indicate that no CV is associated with
+++	this destination.  These should be routed to cvtable[BIT_BUCKET].
+++ ==========================================================================
*/

const BYTE dst_cvn[N_DSTS] = {

	0xFF,			/*  0	UM_NONE				*/

	0xFF,			/*  1	UM_VCO1_PITCH		*/
	0xFF,			/*  2	UM_VCO1_PORT		*/
	HW_VCO1_PW,		/*  3	UM_VCO1_PWIDTH		*/
	HW_VCO1_FM,		/*  4	UM_VCO1_VCO2FM		*/
	0xFF,			/*  5	UM_VCO1_ENV1FM		*/
	0xFF,			/*  6	UM_VCO1_LFO1FM		*/

	0xFF,			/*  7	UM_VCO2_PITCH		*/
	0xFF,			/*  8	UM_VCO2_PORT		*/
	HW_VCO2_PW,		/*  9	UM_VCO2_PWIDTH		*/
	HW_VCO2_FM,		/* 10	UM_VCO2_VCO1FM		*/
	0xFF,			/* 11	UM_VCO2_ENV1FM		*/
	0xFF,			/* 12	UM_VCO2_LFO1FM		*/

	HW_MM_IN1,		/* 13	UM_MM_VCO1			*/
	HW_MM_IN2,		/* 14	UM_MM_VCO2			*/
	HW_MM_NOISE,	/* 15	UM_MM_NOISE			*/
	0xFF,			/* 16	UM_MM_FREQ			*/
	HW_MM_RESON,	/* 17	UM_MM_RESON			*/
	0xFF,			/* 18	UM_MM_ENV1FM		*/
	0xFF,			/* 19	UM_MM_LFO1FM		*/

	HW_OB_IN1,		/* 20	UM_OB_VCO1			*/
	HW_OB_IN2,		/* 21	UM_OB_VCO2			*/
	HW_OB_NOISE,	/* 22	UM_OB_NOISE			*/
	0xFF,			/* 23	UM_OB_FREQ			*/
	HW_OB_RESON,	/* 24	UM_OB_RESON			*/
	0xFF,			/* 25	UM_OB_ENV2FM		*/
	0xFF,			/* 26	UM_OB_LFO2FM		*/

	HW_MIX_MM,		/* 27	UM_MIX_MM			*/
	HW_MIX_LP,		/* 28	UM_MIX_LP			*/
	HW_MIX_BP,		/* 29	UM_MIX_BP			*/
	HW_MIX_HP,		/* 30	UM_MIX_HP			*/
	HW_PAN,			/* 31	UM_MIX_PAN			*/
	0xFF,			/* 32	UM_MIX_VCA			*/

	0xFF,			/* 33	UM_LFO1_DELAY		*/
	0xFF,			/* 34	UM_LFO1_RATE		*/
	0xFF,			/* 35	UM_LFO1_QUANT		*/

	0xFF,			/* 36	UM_LFO2_DELAY		*/
	0xFF,			/* 37	UM_LFO2_RATE		*/
	0xFF,			/* 38	UM_LFO2_QUANT		*/

	0xFF,			/* 39	UM_LFO3_DELAY		*/
	0xFF,			/* 40	UM_LFO3_RATE		*/
	0xFF,			/* 41	UM_LFO3_QUANT		*/

	0xFF,			/* 42	UM_ENV1_ATTACK		*/
	0xFF,			/* 43	UM_ENV1_ATCK_DEL	*/
	0xFF,			/* 44	UM_ENV1_DECAY		*/
	0xFF,			/* 45	UM_ENV1_DCAY_DEL	*/
	0xFF,			/* 46	UM_ENV1_SUSTAIN		*/
	0xFF,			/* 47	UM_ENV1_RELEASE		*/

	0xFF,			/* 48	UM_ENV2_ATTACK		*/
	0xFF,			/* 49	UM_ENV2_ATCK_DEL	*/
	0xFF,			/* 50	UM_ENV2_DECAY		*/
	0xFF,			/* 51	UM_ENV2_DCAY_DEL	*/
	0xFF,			/* 52	UM_ENV2_SUSTAIN		*/
	0xFF,			/* 53	UM_ENV2_RELEASE		*/

	0xFF,			/* 54	UM_ENV3_ATTACK		*/
	0xFF,			/* 55	UM_ENV3_ATCK_DEL	*/
	0xFF,			/* 56	UM_ENV3_DECAY		*/
	0xFF,			/* 57	UM_ENV3_DCAY_DEL	*/
	0xFF,			/* 58	UM_ENV3_SUSTAIN		*/
	0xFF,			/* 59	UM_ENV3_RELEASE		*/

	0xFF,			/* 60	UM_ENV4_ATTACK		*/
	0xFF,			/* 61	UM_ENV4_ATCK_DEL	*/
	0xFF,			/* 62	UM_ENV4_DECAY		*/
	0xFF,			/* 63	UM_ENV4_DCAY_DEL	*/
	0xFF,			/* 64	UM_ENV4_SUSTAIN		*/
	0xFF			/* 65	UM_ENV4_RELEASE		*/
};

/*
+++ ==========================================================================
+++	const BYTE dst_typ[] -- destination number to value type table
+++ ==========================================================================
*/

const BYTE dst_typ[N_DSTS] = {

	DT_GENL,		/*  0 UM_NONE				*/

	DT_FREQ,		/*  1 UM_VCO1_PITCH			*/
	DT_TIME,		/*  2 UM_VCO1_PORT			*/
	DT_GENL,		/*  3 UM_VCO1_PWIDTH		*/
	DT_GENL,		/*  4 UM_VCO1_VCO2FM		*/
	DT_FREQ,		/*  5 UM_VCO1_ENV1FM		*/
	DT_FREQ,		/*  6 UM_VCO1_LFO1FM		*/

	DT_FREQ,		/*  7 UM_VCO2_PITCH			*/
	DT_TIME,		/*  8 UM_VCO2_PORT			*/
	DT_GENL,		/*  9 UM_VCO2_PWIDTH		*/
	DT_GENL,		/* 10 UM_VCO2_VCO1FM		*/
	DT_FREQ,		/* 11 UM_VCO2_ENV1FM		*/
	DT_FREQ,		/* 12 UM_VCO2_LFO1FM		*/

	DT_GENL,		/* 13 UM_MM_VCO1			*/
	DT_GENL,		/* 14 UM_MM_VCO2			*/
	DT_GENL,		/* 15 UM_MM_NOISE			*/
	DT_FREQ,		/* 16 UM_MM_FREQ			*/
	DT_GENL,		/* 17 UM_MM_RESON			*/
	DT_GENL,		/* 18 UM_MM_ENV1FM			*/
	DT_GENL,		/* 19 UM_MM_LFO1FM			*/

	DT_GENL,		/* 20 UM_OB_VCO1			*/
	DT_GENL,		/* 21 UM_OB_VCO2			*/
	DT_GENL,		/* 22 UM_OB_NOISE			*/
	DT_FREQ,		/* 23 UM_OB_FREQ			*/
	DT_GENL,		/* 24 UM_OB_RESON			*/
	DT_GENL,		/* 25 UM_OB_ENV2FM			*/
	DT_GENL,		/* 26 UM_OB_LFO2FM			*/

	DT_GENL,		/* 27 UM_MIX_MM				*/
	DT_GENL,		/* 28 UM_MIX_LP				*/
	DT_GENL,		/* 29 UM_MIX_BP				*/
	DT_GENL,		/* 30 UM_MIX_HP				*/
	DT_GENL,		/* 31 UM_MIX_PAN			*/
	DT_GENL,		/* 32 UM_MIX_VCA			*/

	DT_TIME,		/* 33 UM_LFO1_DELAY			*/
	DT_RATE,		/* 34 UM_LFO1_RATE			*/
	DT_GENL,		/* 35 UM_LFO1_QUANT			*/

	DT_TIME,		/* 36 UM_LFO2_DELAY			*/
	DT_RATE,		/* 37 UM_LFO2_RATE			*/
	DT_GENL,		/* 38 UM_LFO2_QUANT			*/

	DT_TIME,		/* 39 UM_LFO3_DELAY			*/
	DT_RATE,		/* 40 UM_LFO3_RATE			*/
	DT_GENL,		/* 41 UM_LFO3_QUANT			*/

	DT_TIME,		/* 42 UM_ENV1_ATTACK		*/
	DT_TIME,		/* 43 UM_ENV1_ATCK_DEL		*/
	DT_TIME,		/* 44 UM_ENV1_DECAY			*/
	DT_TIME,		/* 45 UM_ENV1_DCAY_DEL		*/
	DT_GENL,		/* 46 UM_ENV1_SUSTAIN		*/
	DT_TIME,		/* 47 UM_ENV1_RELEASE		*/

	DT_TIME,		/* 48 UM_ENV2_ATTACK		*/
	DT_TIME,		/* 49 UM_ENV2_ATCK_DEL		*/
	DT_TIME,		/* 50 UM_ENV2_DECAY			*/
	DT_TIME,		/* 51 UM_ENV2_DCAY_DEL		*/
	DT_GENL,		/* 52 UM_ENV2_SUSTAIN		*/
	DT_TIME,		/* 53 UM_ENV2_RELEASE		*/

	DT_TIME,		/* 54 UM_ENV3_ATTACK		*/
	DT_TIME,		/* 55 UM_ENV3_ATCK_DEL		*/
	DT_TIME,		/* 56 UM_ENV3_DECAY			*/
	DT_TIME,		/* 57 UM_ENV3_DCAY_DEL		*/
	DT_GENL,		/* 58 UM_ENV3_SUSTAIN		*/
	DT_TIME,		/* 59 UM_ENV3_RELEASE		*/

	DT_TIME,		/* 60 UM_ENV4_ATTACK		*/
	DT_TIME,		/* 61 UM_ENV4_ATCK_DEL		*/
	DT_TIME,		/* 62 UM_ENV4_DECAY			*/
	DT_TIME,		/* 63 UM_ENV4_DCAY_DEL		*/
	DT_GENL,		/* 64 UM_ENV4_SUSTAIN		*/
	DT_TIME			/* 65 UM_ENV4_RELEASE		*/
};

/*
+++ ==========================================================================
+++	const BYTE dst_val[] -- destination number to value number table
+++ ==========================================================================
*/

const BYTE dst_val[N_DSTS] = {

	VT_NONE,			/*  0 UM_NONE			*/

	VT_VCO1_CNOTE,		/*  1 UM_VCO1_PITCH		*/
	VT_VCO1_PORT,		/*  2 UM_VCO1_PORT		*/
	VT_VCO1_PWIDTH,		/*  3 UM_VCO1_PWIDTH	*/
	VT_VCO1_VCO2FM,		/*  4 UM_VCO1_VCO2FM	*/
	VT_VCO1_ENV1FM,		/*  5 UM_VCO1_ENV1FM	*/
	VT_VCO1_LFO1FM,		/*  6 UM_VCO1_LFO1FM	*/

	VT_VCO2_CNOTE,		/*  7 UM_VCO2_PITCH		*/
	VT_VCO2_PORT,		/*  8 UM_VCO2_PORT		*/
	VT_VCO2_PWIDTH,		/*  9 UM_VCO2_PWIDTH	*/
	VT_VCO2_VCO1FM,		/* 10 UM_VCO2_VCO1FM	*/
	VT_VCO2_ENV1FM,		/* 11 UM_VCO2_ENV1FM	*/
	VT_VCO2_LFO1FM,		/* 12 UM_VCO2_LFO1FM	*/

	VT_MM_VCO1,			/* 13 UM_MM_VCO1		*/
	VT_MM_VCO2,			/* 14 UM_MM_VCO2		*/
	VT_MM_NOISE,		/* 15 UM_MM_NOISE		*/
	VT_MM_FREQ,			/* 16 UM_MM_FREQ		*/
	VT_MM_RESON,		/* 17 UM_MM_RESON		*/
	VT_MM_ENV1FM,		/* 18 UM_MM_ENV1FM		*/
	VT_MM_LFO1FM,		/* 19 UM_MM_LFO1FM		*/

	VT_OB_VCO1,			/* 20 UM_OB_VCO1		*/
	VT_OB_VCO2,			/* 21 UM_OB_VCO2		*/
	VT_OB_NOISE,		/* 22 UM_OB_NOISE		*/
	VT_OB_FREQ,			/* 23 UM_OB_FREQ		*/
	VT_OB_RESON,		/* 24 UM_OB_RESON		*/
	VT_OB_ENV2FM,		/* 25 UM_OB_ENV2FM		*/
	VT_OB_LFO2FM,		/* 26 UM_OB_LFO2FM		*/

	VT_MIX_MM,			/* 27 UM_MIX_MM			*/
	VT_MIX_LP,			/* 28 UM_MIX_LP			*/
	VT_MIX_BP,			/* 29 UM_MIX_BP			*/
	VT_MIX_HP,			/* 30 UM_MIX_HP			*/
	VT_MIX_PAN,			/* 31 UM_MIX_PAN		*/
	VT_MIX_LEVEL,		/* 32 UM_MIX_VCA		*/

	VT_LFO1_DELAY,		/* 33 UM_LFO1_DELAY		*/
	VT_LFO1_RATE,		/* 34 UM_LFO1_RATE		*/
	VT_LFO1_S_H,		/* 35 UM_LFO1_QUANT		*/

	VT_LFO2_DELAY,		/* 36 UM_LFO2_DELAY		*/
	VT_LFO2_RATE,		/* 37 UM_LFO2_RATE		*/
	VT_LFO2_S_H,		/* 38 UM_LFO2_QUANT		*/

	VT_LFO3_DELAY,		/* 39 UM_LFO3_DELAY		*/
	VT_LFO3_RATE,		/* 40 UM_LFO3_RATE		*/
	VT_LFO3_S_H,		/* 41 UM_LFO3_QUANT		*/

	VT_ENV1_ATTACK,		/* 42 UM_ENV1_ATTACK	*/
	VT_ENV1_ATCK_DEL,	/* 43 UM_ENV1_ATCK_DEL	*/
	VT_ENV1_DECAY,		/* 44 UM_ENV1_DECAY		*/
	VT_ENV1_DCAY_DEL,	/* 45 UM_ENV1_DCAY_DEL	*/
	VT_ENV1_SUSTAIN,	/* 46 UM_ENV1_SUSTAIN	*/
	VT_ENV1_RELEASE,	/* 47 UM_ENV1_RELEASE	*/

	VT_ENV2_ATTACK,		/* 48 UM_ENV2_ATTACK	*/
	VT_ENV2_ATCK_DEL,	/* 49 UM_ENV2_ATCK_DEL	*/
	VT_ENV2_DECAY,		/* 50 UM_ENV2_DECAY		*/
	VT_ENV2_DCAY_DEL,	/* 51 UM_ENV2_DCAY_DEL	*/
	VT_ENV2_SUSTAIN,	/* 52 UM_ENV2_SUSTAIN	*/
	VT_ENV2_RELEASE,	/* 53 UM_ENV2_RELEASE	*/

	VT_ENV3_ATTACK,		/* 54 UM_ENV3_ATTACK	*/
	VT_ENV3_ATCK_DEL,	/* 55 UM_ENV3_ATCK_DEL	*/
	VT_ENV3_DECAY,		/* 56 UM_ENV3_DECAY		*/
	VT_ENV3_DCAY_DEL,	/* 57 UM_ENV3_DCAY_DEL	*/
	VT_ENV3_SUSTAIN,	/* 58 UM_ENV3_SUSTAIN	*/
	VT_ENV3_RELEASE,	/* 59 UM_ENV3_RELEASE	*/

	VT_ENV4_ATTACK,		/* 60 UM_ENV4_ATTACK	*/
	VT_ENV4_ATCK_DEL,	/* 61 UM_ENV4_ATCK_DEL	*/
	VT_ENV4_DECAY,		/* 62 UM_ENV4_DECAY		*/
	VT_ENV4_DCAY_DEL,	/* 63 UM_ENV4_DCAY_DEL	*/
	VT_ENV4_SUSTAIN,	/* 64 UM_ENV4_SUSTAIN	*/
	VT_ENV4_RELEASE		/* 65 UM_ENV4_RELEASE	*/
};

/*
+++ ==========================================================================
+++	const BYTE par_dst[] -- preset parameter number to destination number
+++ ==========================================================================
*/

const BYTE par_dst[NUM_PARAM] = {

	UM_VCO1_PITCH,		/* VCO1_PITCH		 0 */
	0xFF,				/* VCO1_FINE		 1 */
	0xFF,				/* VCO1_TRACK		 2 */
	UM_VCO1_PORT,		/* VCO1_PORT		 3 */
	UM_VCO1_PWIDTH,		/* VCO1_PWIDTH		 4 */
	0xFF,				/* VCO1_SHAPE		 5 */
	UM_VCO1_VCO2FM,		/* VCO1_VCO2FM		 6 */
	UM_VCO1_ENV1FM,		/* VCO1_ENV1FM		 7 */
	UM_VCO1_LFO1FM,		/* VCO1_LFO1FM		 8 */
	0xFF,				/* VCO1_PWM			 9 */

	UM_VCO2_PITCH,		/* VCO2_PITCH		10 */
	0xFF,				/* VCO2_FINE		11 */
	0xFF		,		/* VCO2_TRACK		12 */
	UM_VCO2_PORT,		/* VCO2_PORT		13 */
	UM_VCO2_PWIDTH,		/* VCO2_PWIDTH		14 */
	0xFF,				/* VCO2_SHAPE		15 */
	UM_VCO2_VCO1FM,		/* VCO2_VCO1FM		16 */
	UM_VCO2_ENV1FM,		/* VCO2_ENV1FM		17 */
	UM_VCO2_LFO1FM,		/* VCO2_LFO1FM		18 */
	0xFF,				/* VCO2_PWM			19 */

	UM_MM_VCO1,			/* MM_VCO1			20 */
	UM_MM_VCO2,			/* MM_VCO2			21 */
	UM_MM_NOISE,		/* MM_NOISE			22 */
	UM_MM_FREQ,			/* MM_FREQ			23 */
	UM_MM_RESON,		/* MM_RESON			24 */
	UM_MM_ENV1FM,		/* MM_ENV1FM		25 */
	UM_MM_LFO1FM,		/* MM_LFO1FM		26 */
	0xFF,				/* MM_TRACK			27 */

	UM_OB_VCO1,			/* OB_VCO1			28 */
	UM_OB_VCO2,			/* OB_VCO2			29 */
	UM_OB_NOISE,		/* OB_NOISE			30 */
	UM_OB_FREQ,			/* OB_FREQ			31 */
	UM_OB_RESON,		/* OB_RESON			32 */
	UM_OB_ENV2FM,		/* OB_ENV2FM		33 */
	UM_OB_LFO2FM,		/* OB_LFO2FM		34 */
	0xFF,				/* OB_TRACK			35 */

	UM_LFO1_DELAY,		/* LFO1_DELAY		36 */
	UM_LFO1_RATE,		/* LFO1_RATE		37 */
	0xFF,				/* LFO1_OFFSET		38 */
	UM_LFO1_QUANT,		/* LFO1_S_H			39 */
	0xFF,				/* LFO1_SHAPE		40 */

	UM_LFO2_DELAY,		/* LFO2_DELAY		41 */
	UM_LFO2_RATE,		/* LFO2_RATE		42 */
	0xFF,				/* LFO2_OFFSET		43 */
	UM_LFO2_QUANT,		/* LFO2_S_H			44 */
	0xFF,				/* LFO2_SHAPE		45 */

	UM_LFO3_DELAY,		/* LFO3_DELAY		46 */
	UM_LFO3_RATE,		/* LFO3_RATE		47 */
	0xFF,				/* LFO3_OFFSET		48 */
	UM_LFO3_QUANT,		/* LFO3_S_H			49 */
	0xFF,				/* LFO3_SHAPE		50 */

	0xFF,				/* ENV1_MODE		51 */
	UM_ENV1_ATTACK,		/* ENV1_ATTACK		52 */
	UM_ENV1_ATCK_DEL,	/* ENV1_ATCK_DEL	53 */
	UM_ENV1_DECAY,		/* ENV1_DECAY		54 */
	UM_ENV1_DCAY_DEL,	/* ENV1_DCAY_DEL	55 */
	UM_ENV1_SUSTAIN,	/* ENV1_SUSTAIN		56 */
	0xFF,				/* ENV1_SUS_DCAY	57 */
	UM_ENV1_RELEASE,	/* ENV1_RELEASE		58 */
	0xFF,				/* ENV1_VEL_SENS	59 */

	0xFF,				/* ENV2_MODE		60 */
	UM_ENV2_ATTACK,		/* ENV2_ATTACK		61 */
	UM_ENV2_ATCK_DEL,	/* ENV2_ATCK_DEL	62 */
	UM_ENV2_DECAY,		/* ENV2_DECAY		63 */
	UM_ENV2_DCAY_DEL,	/* ENV2_DCAY_DEL	64 */
	UM_ENV2_SUSTAIN,	/* ENV2_SUSTAIN		65 */
	0xFF,				/* ENV2_SUS_DCAY	66 */
	UM_ENV2_RELEASE,	/* ENV2_RELEASE		67 */
	0xFF,				/* ENV2_VEL_SENS	68 */

	0xFF,				/* ENV3_MODE		69 */
	UM_ENV3_ATTACK,		/* ENV3_ATTACK		70 */
	UM_ENV3_ATCK_DEL,	/* ENV3_ATCK_DEL	71 */
	UM_ENV3_DECAY,		/* ENV3_DECAY		72 */
	UM_ENV3_DCAY_DEL,	/* ENV3_DCAY_DEL	73 */
	UM_ENV3_SUSTAIN,	/* ENV3_SUSTAIN		74 */
	0xFF,				/* ENV3_SUS_DCAY	75 */
	UM_ENV3_RELEASE,	/* ENV3_RELEASE		76 */
	0xFF,				/* ENV3_VEL_SENS	77 */

	0xFF,				/* ENV4_MODE		78 */
	UM_ENV4_ATTACK,		/* ENV4_ATTACK		79 */
	UM_ENV4_ATCK_DEL,	/* ENV4_ATCK_DEL	80 */
	UM_ENV4_DECAY,		/* ENV4_DECAY		81 */
	UM_ENV4_DCAY_DEL,	/* ENV4_DCAY_DEL	82 */
	UM_ENV4_SUSTAIN,	/* ENV4_SUSTAIN		83 */
	0xFF,				/* ENV4_SUS_DCAY	84 */
	UM_ENV4_RELEASE,	/* ENV4_RELEASE		85 */
	0xFF,				/* ENV4_VEL_SENS	86 */

	UM_MIX_LP,			/* MIX_LP			87 */
	UM_MIX_BP,			/* MIX_BP			88 */
	UM_MIX_HP,			/* MIX_HP			89 */
	UM_MIX_MM,			/* MIX_MM			90 */
	UM_MIX_PAN,			/* MIX_PAN			91 */
	UM_MIX_VCA			/* MIX_LEVEL		92 */
};

/*
+++ ==========================================================================
+++	const BYTE par_val[] -- parameter number to value number table
+++ ==========================================================================
*/

const BYTE par_val[NUM_PARAM] = {

	/* -------- VCOs -------- */

	VT_VCO1_PITCH,		/* VCO1_PITCH,	 	 0 */
	VT_VCO1_FINE,		/* VCO1_FINE,		 1 */
	VT_VCO1_TRACK,		/* VCO1_TRACK,		 2 */
	VT_VCO1_PORT,		/* VCO1_PORT,		 3 */
	VT_VCO1_PWIDTH,		/* VCO1_PWIDTH,		 4 */
	0xFF,				/* VCO1_SHAPE,		 5 */
	VT_VCO1_VCO2FM,		/* VCO1_VCO2FM,		 6 */
	VT_VCO1_ENV1FM,		/* VCO1_ENV1FM,		 7 */
	VT_VCO1_LFO1FM,		/* VCO1_LFO1FM,		 8 */
	VT_VCO1_PWM,		/* VCO1_PWM,		 9 */

	VT_VCO2_PITCH,		/* VCO2_PITCH,		10 */
	VT_VCO2_FINE,		/* VCO2_FINE,		11 */
	VT_VCO2_TRACK,		/* VCO2_TRACK,		12 */
	VT_VCO2_PORT,		/* VCO2_PORT,		13 */
	VT_VCO2_PWIDTH,		/* VCO2_PWIDTH,		14 */
	0xFF,				/* VCO2_SHAPE,		15 */
	VT_VCO2_VCO1FM,		/* VCO2_VCO1FM,		16 */
	VT_VCO2_ENV1FM,		/* VCO2_ENV1FM,		17 */
	VT_VCO2_LFO1FM,		/* VCO2_LFO1FM,		18 */
	VT_VCO2_PWM,		/* VCO2_PWM,		19 */

	/* -------- VCFs -------- */

	VT_MM_VCO1,			/* MM_VCO1,			20 */
	VT_MM_VCO2,			/* MM_VCO2,			21 */
	VT_MM_NOISE,		/* MM_NOISE,		22 */
	VT_MM_FREQ,			/* MM_FREQ,			23 */
	VT_MM_RESON,		/* MM_RESON,		24 */
	VT_MM_ENV1FM,		/* MM_ENV1FM,		25 */
	VT_MM_LFO1FM,		/* MM_LFO1FM,		26 */
	VT_MM_TRACK,		/* MM_TRACK,		27 */

	VT_OB_VCO1,			/* OB_VCO1,			28 */
	VT_OB_VCO2,			/* OB_VCO2,			29 */
	VT_OB_NOISE,		/* OB_NOISE,		30 */
	VT_OB_FREQ,			/* OB_FREQ,			31 */
	VT_OB_RESON,		/* OB_RESON,		32 */
	VT_OB_ENV2FM,		/* OB_ENV2FM,		33 */
	VT_OB_LFO2FM,		/* OB_LFO2FM,		34 */
	VT_OB_TRACK,		/* OB_TRACK,		35 */

	/* -------- LFOs -------- */

	VT_LFO1_DELAY,		/* LFO1_DELAY,		36 */
	VT_LFO1_RATE,		/* LFO1_RATE,		37 */
	VT_LFO1_OFFSET,		/* LFO1_OFFSET,		38 */
	VT_LFO1_S_H,		/* LFO1_S_H,		39 */
	0xFF,				/* LFO1_SHAPE,		40 */

	VT_LFO2_DELAY,		/* LFO2_DELAY,		41 */
	VT_LFO2_RATE,		/* LFO2_RATE,		42 */
	VT_LFO2_OFFSET,		/* LFO2_OFFSET,		43 */
	VT_LFO2_S_H,		/* LFO2_S_H,		44 */
	0xFF,				/* LFO2_SHAPE,		45 */

	VT_LFO3_DELAY,		/* LFO3_DELAY,		46 */
	VT_LFO3_RATE,		/* LFO3_RATE,		47 */
	VT_LFO3_OFFSET,		/* LFO3_OFFSET,		48 */
	VT_LFO3_S_H,		/* LFO3_S_H,		49 */
	0xFF,				/* LFO3_SHAPE,		50 */

	/* -------- ENVs -------- */

	0xFF,				/* ENV1_MODE,		51 */
	VT_ENV1_ATTACK,		/* ENV1_ATTACK,		52 */
	VT_ENV1_ATCK_DEL,	/* ENV1_ATCK_DEL,	53 */
	VT_ENV1_DECAY,		/* ENV1_DECAY,		54 */
	VT_ENV1_DCAY_DEL,	/* ENV1_DCAY_DEL,	55 */
	VT_ENV1_SUSTAIN,	/* ENV1_SUSTAIN,	56 */
	VT_ENV1_SUS_DCAY,	/* ENV1_SUS_DCAY,	57 */
	VT_ENV1_RELEASE,	/* ENV1_RELEASE,	58 */
	VT_ENV1_VEL_SENS,	/* ENV1_VEL_SENS,	59 */

	0xFF,				/* ENV2_MODE,		60 */
	VT_ENV2_ATTACK,		/* ENV2_ATTACK,		61 */
	VT_ENV2_ATCK_DEL,	/* ENV2_ATCK_DEL,	62 */
	VT_ENV2_DECAY,		/* ENV2_DECAY,		63 */
	VT_ENV2_DCAY_DEL,	/* ENV2_DCAY_DEL,	64 */
	VT_ENV2_SUSTAIN,	/* ENV2_SUSTAIN,	65 */
	VT_ENV2_SUS_DCAY,	/* ENV2_SUS_DCAY,	66 */
	VT_ENV2_RELEASE,	/* ENV2_RELEASE,	67 */
	VT_ENV2_VEL_SENS,	/* ENV2_VEL_SENS,	68 */

	0xFF,				/* ENV3_MODE,		69 */
	VT_ENV3_ATTACK,		/* ENV3_ATTACK,		70 */
	VT_ENV3_ATCK_DEL,	/* ENV3_ATCK_DEL,	71 */
	VT_ENV3_DECAY,		/* ENV3_DECAY,		72 */
	VT_ENV3_DCAY_DEL,	/* ENV3_DCAY_DEL,	73 */
	VT_ENV3_SUSTAIN,	/* ENV3_SUSTAIN,	74 */
	VT_ENV3_SUS_DCAY,	/* ENV3_SUS_DCAY,	75 */
	VT_ENV3_RELEASE,	/* ENV3_RELEASE,	76 */
	VT_ENV3_VEL_SENS,	/* ENV3_VEL_SENS,	77 */

	0xFF,				/* ENV4_MODE,		78 */
	VT_ENV4_ATTACK,		/* ENV4_ATTACK,		79 */
	VT_ENV4_ATCK_DEL,	/* ENV4_ATCK_DEL,	80 */
	VT_ENV4_DECAY,		/* ENV4_DECAY,		81 */
	VT_ENV4_DCAY_DEL,	/* ENV4_DCAY_DEL,	82 */
	VT_ENV4_SUSTAIN,	/* ENV4_SUSTAIN,	83 */
	VT_ENV4_SUS_DCAY,	/* ENV4_SUS_DCAY,	84 */
	VT_ENV4_RELEASE,	/* ENV4_RELEASE,	85 */
	VT_ENV4_VEL_SENS,	/* ENV4_VEL_SENS,	86 */

	/* -------- MIX --------- */

	VT_MIX_LP,			/* MIX_LP,			87 */
	VT_MIX_BP,			/* MIX_BP,			88 */
	VT_MIX_HP,			/* MIX_HP,			89 */
	VT_MIX_MM,			/* MIX_MM,			90 */
	VT_MIX_PAN,			/* MIX_PAN,			91 */
	VT_MIX_LEVEL,		/* MIX_LEVEL,		92 */
};

/*
+++ ==========================================================================
+++	const BYTE qpa_pot[] -- voice A quadpot pot addresses
+++ ==========================================================================
*/

const BYTE qpa_pot[8] = {0x53, 0x52, 0x53, 0x52, 0x50, 0x50, 0x50, 0x50};

/*
+++ ==========================================================================
+++	const BYTE qpb_pot[] -- voice B quadpot pot addresses
+++ ==========================================================================
*/

const BYTE qpb_pot[8] = {0x53, 0x52, 0x53, 0x52, 0x51, 0x51, 0x51, 0x51};

/*
+++ ==========================================================================
+++	const BYTE qpa_cmd[] -- voice A quadpot pot commands
+++ ==========================================================================
*/

const BYTE qpa_cmd[8] = {0xA0, 0xA0, 0xA8, 0xA8, 0xA0, 0xAC, 0xA8, 0xA4};

/*
+++ ==========================================================================
+++	const BYTE qpb_cmd[] -- voice B quadpot pot commands
+++ ==========================================================================
*/

const BYTE qpb_cmd[8] = {0xA4, 0xA4, 0xAC, 0xAC, 0xA0, 0xAC, 0xA8, 0xA4};

/*
+++ ==========================================================================
+++	const S_BYTE vco_off[] -- VCO offset values for tuning A off of 440 Hz
+++	Range: 415..465 Hz
+++ ==========================================================================
*/

/*	Step        Actual        Wanted   Offset Error   Percent Index*/

const S_BYTE vco_off[81] = {

	 -53,	/*  399.8566      400      -40    -0.1434 -0.0359 00 */
	 -51,	/*  401.3027      401      -39     0.3027  0.0754 01 */
	 -50,	/*  402.0277      402      -38     0.0277  0.0069 02 */
	 -49,	/*  402.7541      403      -37    -0.2459 -0.0611 03 */
	 -47,	/*  404.2107      404      -36     0.2107  0.0521 04 */
	 -46,	/*  404.9410      405      -35    -0.0590 -0.0146 05 */
	 -45,	/*  405.6726      406      -34    -0.3274 -0.0807 06 */
	 -43,	/*  407.1398      407      -33     0.1398  0.0343 07 */
	 -42,	/*  407.8754      408      -32    -0.1246 -0.0306 08 */
	 -40,	/*  409.3505      409      -31     0.3505  0.0856 09 */
	 -39,	/*  410.0901      410      -30     0.0901  0.0220 10 */
	 -38,	/*  410.8310      411      -29    -0.1690 -0.0411 11 */
	 -36,	/*  412.3168      412      -28     0.3168  0.0768 12 */
	 -35,	/*  413.0618      413      -27     0.0618  0.0150 13 */
	 -34,	/*  413.8081      414      -26    -0.1919 -0.0464 14 */
	 -32,	/*  415.3047      415      -25     0.3047  0.0734 15 */
	 -31,	/*  416.0550      416      -24     0.0550  0.0132 16 */
	 -30,	/*  416.8067      417      -23    -0.1933 -0.0464 17 */
	 -28,	/*  418.3141      418      -22     0.3141  0.0751 18 */
	 -27,	/*  419.0699      419      -21     0.0699  0.0167 19 */
	 -26,	/*  419.8270      420      -20    -0.1730 -0.0412 20 */
	 -24,	/*  421.3454      421      -19     0.3454  0.0820 21 */
	 -23,	/*  422.1066      422      -18     0.1066  0.0253 22 */
	 -22,	/*  422.8693      423      -17    -0.1307 -0.0309 23 */
	 -21,	/*  423.6333      424      -16    -0.3667 -0.0866 24 */
	 -19,	/*  425.1654      425      -15     0.1654  0.0389 25 */
	 -18,	/*  425.9336      426      -14    -0.0664 -0.0156 26 */
	 -17,	/*  426.7031      427      -13    -0.2969 -0.0696 27 */
	 -15,	/*  428.2463      428      -12     0.2463  0.0575 28 */
	 -14,	/*  429.0200      429      -11     0.0200  0.0047 29 */
	 -13,	/*  429.7952      430      -10    -0.2048 -0.0477 30 */
	 -11,	/*  431.3496      431       -9     0.3496  0.0810 31 */
	 -10,	/*  432.1289      432       -8     0.1289  0.0298 32 */
	  -9,	/*  432.9096      433       -7    -0.0904 -0.0209 33 */
	  -8,	/*  433.6918      434       -6    -0.3082 -0.0711 34 */
	  -6,	/*  435.2603      435       -5     0.2603  0.0598 35 */
	  -5,	/*  436.0467      436       -4     0.0467  0.0107 36 */
	  -4,	/*  436.8345      437       -3    -0.1655 -0.0379 37 */
	  -3,	/*  437.6237      438       -2    -0.3763 -0.0860 38 */
	  -1,	/*  439.2064      439       -1     0.2064  0.0470 39 */
	   0,	/*  440.0000      440        0    -0.0000 -0.0000 40 */
	   1,	/*  440.7949      441        1    -0.2051 -0.0465 41 */
	   3,	/*  442.3891      442        2     0.3891  0.0880 42 */
	   4,	/*  443.1884      443        3     0.1884  0.0425 43 */
	   5,	/*  443.9891      444        4    -0.0109 -0.0025 44 */
	   6,	/*  444.7912      445        5    -0.2088 -0.0469 45 */
	   8,	/*  446.3999      446        6     0.3999  0.0896 46 */
	   9,	/*  447.2064      447        7     0.2064  0.0462 47 */
	  10,	/*  448.0144      448        8     0.0144  0.0032 48 */
	  11,	/*  448.8238      449        9    -0.1762 -0.0393 49 */
	  12,	/*  449.6347      450       10    -0.3653 -0.0812 50 */
	  14,	/*  451.2609      451       11     0.2609  0.0578 51 */
	  15,	/*  452.0762      452       12     0.0762  0.0169 52 */
	  16,	/*  452.8929      453       13    -0.1071 -0.0236 53 */
	  17,	/*  453.7112      454       14    -0.2888 -0.0637 54 */
	  19,	/*  455.3521      455       15     0.3521  0.0773 55 */
	  20,	/*  456.1748      456       16     0.1748  0.0383 56 */
	  21,	/*  456.9990      457       17    -0.0010 -0.0002 57 */
	  22,	/*  457.8246      458       18    -0.1754 -0.0383 58 */
	  23,	/*  458.6518      459       19    -0.3482 -0.0759 59 */
	  25,	/*  460.3106      460       20     0.3106  0.0675 60 */
	  26,	/*  461.1422      461       21     0.1422  0.0308 61 */
	  27,	/*  461.9754      462       22    -0.0246 -0.0053 62 */
	  28,	/*  462.8100      463       23    -0.1900 -0.0411 63 */
	  29,	/*  463.6462      464       24    -0.3538 -0.0763 64 */
	  31,	/*  465.3230      465       25     0.3230  0.0694 65 */
	  32,	/*  466.1637      466       26     0.1637  0.0351 66 */
	  33,	/*  467.0059      467       27     0.0059  0.0013 67 */
	  34,	/*  467.8497      468       28    -0.1503 -0.0321 68 */
	  35,	/*  468.6949      469       29    -0.3051 -0.0651 69 */
	  37,	/*  470.3901      470       30     0.3901  0.0829 70 */
	  38,	/*  471.2399      471       31     0.2399  0.0509 71 */
	  39,	/*  472.0913      472       32     0.0913  0.0193 72 */
	  40,	/*  472.9442      473       33    -0.0558 -0.0118 73 */
	  41,	/*  473.7987      474       34    -0.2013 -0.0425 74 */
	  42,	/*  474.6547      475       35    -0.3453 -0.0727 75 */
	  44,	/*  476.3714      476       36     0.3714  0.0780 76 */
	  45,	/*  477.2320      477       37     0.2320  0.0486 77 */
	  46,	/*  478.0943      478       38     0.0943  0.0197 78 */
	  47,	/*  478.9580      479       39    -0.0420 -0.0088 79 */
	  48	/*  479.8234      480       40    -0.1766 -0.0368 80 */
};

/*
+++ =======================================================================
+++	const INT pw_scl[] -- pitch wheel scaling table - 1..12 semitones
+++ =======================================================================
*/

const INT pw_scl[12] = {

	0x7FFF,		/* [ 0] +/-  1 semitone  */
	0x3FFF,		/* [ 1] +/-  2 semitones */
	0x2AAA,		/* [ 2] +/-  3 semitones */
	0x1FFF,		/* [ 3] +/-  4 semitones */
	0x1999,		/* [ 4] +/-  5 semitones */
	0x1555,		/* [ 5] +/-  6 semitones */
	0x1249,		/* [ 6] +/-  7 semitones */
	0x0FFF,		/* [ 7] +/-  8 semitones */
	0x0E38,		/* [ 8] +/-  9 semitones */
	0x0CCC,		/* [ 9] +/- 10 semitones */
	0x0BA2,		/* [10] +/- 11 semitones */
	0x0AAA		/* [11] +/- 12 semitones */
};

/*
+++ =======================================================================
+++	const BYTE vin_tab[] -- velocity inversion table
+++ =======================================================================
*/

const BYTE vin_tab[128] = {

	0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,	/*   0..7 */
	0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,	/*   8..15 */
	0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,	/*  16..23 */
	0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,	/*  24..31 */
	0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7D,	/*  32..39 */
	0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7C, 0x7C, 0x7C,	/*  40..47 */
	0x7C, 0x7C, 0x7B, 0x7B, 0x7B, 0x7B, 0x7A, 0x7A,	/*  48..55 */
	0x7A, 0x79, 0x79, 0x79, 0x78, 0x78, 0x77, 0x77,	/*  56..63 */
	0x76, 0x76, 0x75, 0x75, 0x74, 0x73, 0x73, 0x72,	/*  64..71 */
	0x71, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B,	/*  72..79 */
	0x6B, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63,	/*  80..87 */
	0x61, 0x60, 0x5E, 0x5D, 0x5C, 0x5A, 0x58, 0x57,	/*  88..95 */
	0x55, 0x53, 0x51, 0x50, 0x4E, 0x4C, 0x4A, 0x48,	/*  96..103 */
	0x45, 0x43, 0x41, 0x3F, 0x3C, 0x3A, 0x37, 0x34,	/* 104..111 */
	0x32, 0x2F, 0x2C, 0x29, 0x26, 0x23, 0x20, 0x1D,	/* 112..119 */
	0x19, 0x16, 0x12, 0x0F, 0x0B, 0x07, 0x03, 0x00	/* 120..127 */
};

/* The End */
