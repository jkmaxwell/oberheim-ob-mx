/*
   ===========================================================================
	File:		VARS.H

	Purpose:	OB-MX variable and table external references

	Original:		1993-05-30	D.N. Lynx Crowe

	Revision:	58	1994-05-25	D.N. Lynx Crowe

	WARNING:  These externs must match the variables in VARS.C, etc.
   ===========================================================================
*/

/* -------------------------- defined in vars.c --------------------------- */

extern WORD			first_var;		/* beginning of VARS.C variables */

extern WORD			vid1;			/* voice ID, voice A */
extern WORD			vid2;			/* voice ID, voice B */

extern WORD			vchan1;			/* channel, voice A */
extern WORD			vchan2;			/* channel, voice B */

extern WORD			vpart1;			/* part, voice A */
extern WORD			vpart2;			/* part, voice B */

extern WORD			ipc_stat;		/* status byte type */
extern WORD			ipc_addr;		/* voice or channel */

extern WORD			cur_cv;			/* current CV for update */
extern WORD			cur_ctl;		/* current controller for update */

extern WORD			wca;			/* tuning table A word counter */
extern WORD			wcb;			/* tuning table B word counter */

extern WORD			*tpa;			/* pointer to next word in A tuning table */
extern WORD			*tpb;			/* pointer to next word in B tuning table */

extern WORD			aoff;			/* composite tuning offset work area A */
extern WORD			boff;			/* composite tuning offset work area B */

extern void			(*ipc_state)();	/* next ipc state processor */

extern BYTE			parmap[];		/* preset parameter to DAC map */

extern WORD			cvtable[];		/* DAC output table */

extern BYTE			ctltable[];		/* control register table (12 used) */

extern struct voice	v[];			/* voice data structures */

extern BYTE			ipc_fifo[];		/* IPC FIFO buffer area */

/* ------------------------- defined in tables1.c ------------------------- */

extern WORD			tuneup;			/* tune on power up flag */

extern BYTE			dacmap[];		/* DAC bit scramble map */

extern struct mod	fixed_mods[];	/* fixed modulation setups */

extern BYTE			dst_cvn[];		/* destination number to CV number table */
extern BYTE			dst_typ[];		/* destination number to value type table */
extern BYTE			dst_val[];		/* destination number to value number table */

extern BYTE			par_dst[];		/* preset parameter number to destination number */
extern BYTE			par_val[];		/* parameter number to value number table */

extern BYTE			qpa_pot[];		/* voice A quadpot pot addresses */
extern BYTE			qpb_pot[];		/* voice B quadpot pot addresses */

extern BYTE			qpa_cmd[];		/* voice A quadpot pot commands */
extern BYTE			qpb_cmd[];		/* voice B quadpot pot commands */

extern S_BYTE		vco_off[];		/* VCO offset values for tuning A off of 440 Hz */

extern INT			pw_scl[];		/* pitch wheel scaling table */

extern BYTE			vin_tab[];		/* velocity inversion table */

/* ------------------------- defined in tables2.c ------------------------- */

extern BYTE			p_ticks[];		/* portamento tick table */
extern WORD			p_incrs[];		/* portamento incr table */

extern BYTE			t_ticks[];		/* general time tick table */
extern WORD			t_incrs[];		/* general time incr table */

extern BYTE			l_ticks[];		/* LFO time tick table */
extern WORD			l_incrs[];		/* LFO time incr table */

extern BYTE			r_ticks[];		/* LFO rate tick table */
extern WORD			r_incrs[];		/* LFO rate incr table */

extern WORD			lfosh[];		/* LFO quantization table */

extern INT			kbtable[];		/* keyboard tracking table */

/* ------------------------- defined in tables3.c ------------------------- */

extern INT			mlt_tab[];		/* general multiplier table */
extern INT			tml_tab[];		/* tracking multiplier table */
extern INT			pml_tab[];		/* pitch multiplier table */

extern INT			off_val[];		/* offset value table */
extern INT			val_tab[];		/* signed value table */

extern INT			fml_tab[];		/* filter keyboard tracking table */
extern INT			smooth[];		/* LFO random number smoothing table */

/* --------------------------- defined in hdw.a --------------------------- */

extern WORD			if_start;		/* IPC FIFO head pointer (REGISTER) */
extern WORD			if_end;			/* IPC FIFO tail pointer (REGISTER) */

extern WORD			ipc_byte1;		/* IPC message byte 1 (REGISTER) */
extern WORD			ipc_byte2;		/* IPC message byte 2 (REGISTER) */

extern WORD			intune;			/* tuning in progress flag (REGISTER) */
extern WORD			diagmode;		/* diagnostic mode flag (REGISTER) */
extern WORD			stwat_flag;		/* "stop the world and tune" flag (REGISTER) */

extern WORD			hsi_isw;		/* HSI interrupt processing mode flag */

extern WORD			r_crash;		/* stray interrupt crash register (REGISTER) */
extern WORD			r_mstime;		/* wait time counter (REGISTER) */

extern WORD			bflag;			/* background timer flag (REGISTER) */
extern WORD			calref;			/* calibration reference flag */
extern WORD			sflag;			/* skip MOD cycle flag (REGISTER) */

extern BYTE			ioc0_img;		/* IOC0 image (REGISTER) */
extern BYTE			ioc1_img;		/* IOC1 image (REGISTER) */
extern BYTE			ioc2_img;		/* IOC2 image (REGISTER) */
extern BYTE			port2_img;		/* IO_PORT2 image (REGISTER) */

extern char			ipc_obuf;		/* IPC output buffer */

/* -------------------------- defined in tune.a --------------------------- */

extern INT			a_v1_off;		/* VOICE A VCO1 tuning offset */
extern INT			a_v2_off;		/* VOICE A VCO2 tuning offset */
extern INT			a_mm_off;		/* VOICE A MM tuning offset */
extern INT			a_ob_off;		/* VOICE A OB tuning offset */

extern INT			b_v1_off;		/* VOICE B VCO1 tuning offset */
extern INT			b_v2_off;		/* VOICE B VCO2 tuning offset */
extern INT			b_mm_off;		/* VOICE B MM tuning offset */
extern INT			b_ob_off;		/* VOICE B OB tuning offset */

extern WORD			tune_vars[];	/* tuning offsets and scales */
extern WORD			tune_save[];	/* tuning variable save area */

/* The End */
