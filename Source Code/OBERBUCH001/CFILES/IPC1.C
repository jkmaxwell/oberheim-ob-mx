/*
+++ ==========================================================================
+++	File:		IPC1.C
+++	Purpose:	OB-MX IPC message parser -- parser utilities & voice reductions
+++	Original:		1993-05-26	D.N. Lynx Crowe
+++	Revision:	84	1994-06-09	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		get_tt()			read in a tuning table from the IPC bus
+++		init_ipc()			initialize IPC
+++		never()				handle bogus message types
+++		part_misc()			process part miscellaneous function
+++		part_misc1()		process part miscellaneous function for voice A
+++		part_misc2()		process part miscellaneous function for voice B
+++		part_miscb()		process part miscellaneous function for both voices
+++		perform_param1()	process performance parameter for voice A
+++		perform_param2()	process performance parameter for voice B
+++		perform_paramb()	process performance parameter for both voices
+++		preset_param1()		process preset parameter for voice A
+++		preset_param2()		process preset parameter for voice B
+++		preset_paramb()		process performance parameter for both voices
+++		set_channel1()		set channel for voice A
+++		set_channel2()		set channel for voice B
+++		set_transpose()		set VT_TRANSPOSE for a VOICE
+++		user_mod1()			process user mod for voice A
+++		user_mod2()			process user mod for voice B
+++		user_modb()			process user mod for both voices
+++		voice_misc()		process voice miscellaneous function
+++		voice_misc1()		process voice A miscellaneous function
+++		voice_misc2()		process voice B miscellaneous function
+++
+++		red1_tbl[]			message reduction table -- voice A
+++		red2_tbl[]			message reduction table -- voice B
+++		redb_tbl[]			message reduction table -- voices A & B
+++		stch_tbl[]			xref CHANNEL to second state
+++		stpt_tbl[]			xref PART to second state
+++		stvc_tbl[]			xref VOICE to second state
+++
+++	Added proc_both() and changed part_miscb(), preset_paramb(), user_modb(),
+++	and perform_paramb() to call proc_both() to conserve space.
+++ ==========================================================================
*/

#include "voice.h"
#include "vars.h"

/* ========================== forward references ========================== */

void set_channel1();		/* process set channel -- voice A */
void part_misc1();			/* process miscellaneous function -- voice A */
void gate_ungate1();		/* process gate ungate -- voice A */
void preset_param1();		/* process preset parameter -- voice A */
void user_mod1();			/* process user modulation -- voice A */
void perform_param1();		/* process performance parameter -- voice A */
void voice_misc1();			/* process voice specific -- voice A */

void set_channel2();		/* process set channel -- voice B */
void part_misc2();			/* process miscellaneous function -- voice B */
void gate_ungate2();		/* process gate ungate -- voice B */
void preset_param2();		/* process preset parameter -- voice B */
void user_mod2();			/* process user modulation -- voice B */
void perform_param2();		/* process performance parameter -- voice B */
void voice_misc2();			/* process voice specific -- voice B */

void part_miscb();			/* process miscellaneous function -- both voices */
void preset_paramb();		/* process preset parameter -- both voices */
void user_modb();			/* process user modulation -- both voices */
void perform_paramb();		/* process performance parameter --both voices */

void never();				/* handle bogus message types */

/*+ ====================== external function references =================== */

extern void		ipc_state_0();		/*+ awaiting a message */
extern void		ipc1_state_1();		/*+ message for voice A -- data byte 1 */
extern void		ipc2_state_1();		/*+ message for voice B -- data byte 1 */
extern void		ipcb_state_1();		/*+ message for both voices -- data byte 1 */
extern INT		mod_vca();			/*+ modulate VCA by ENV4 */
extern void		perform_param();	/*+ process performance parameter */
extern void		preset_param();		/*+ process preset parameter */
extern void		reset_parser();		/*+ reset IPC I/O data structures */
extern WORD		set_pan();			/*+ set pan */
extern void		setpots();			/*+ set quadpot EEPROM */
extern void		user_mod();			/*+ process user modulation */
extern void		wqpot3();			/*+ write a value to a quadpot */
extern void		write_ipc();		/*+ write a byte to the IPC bus */

/*+ ======================== variables and tables ========================= */

/*
+++ ==========================================================================
+++	void (*stvc_tbl[])() -- xref VOICE to second state
+++
+++	This table gets slots stuffed by init_ipc()
+++	according to the IDs of the VOICEs this processor is handling.
+++
+++		Voice A's slot gets ipc1_state_1, and
+++		voice B's slot gets	ipc2_state_1.
+++ ==========================================================================
*/

void (*stvc_tbl[12])() = {

	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0
};

/*
+++ ==========================================================================
+++	void (*stch_tbl[])() -- xref CHANNEL to second state
+++
+++	This table gets stuffed by set_channel1() or set_channel2()
+++	according to the voice assigned to the channel.
+++
+++	Initialized by init_ipc().
+++ ==========================================================================
*/

void (*stch_tbl[16])() = {

	ipc_state_0,		/* inited to: ipcb_state_1 */
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0
};

/*
+++ ==========================================================================
+++	void (*stpt_tbl[])() -- xref PART to second state
+++
+++	This table gets stuffed by set_channel1() or set_channel2()
+++	according to the voice(s) assigned to the PART.
+++
+++	Initialized by init_ipc().
+++
+++	Note that PART 6 is the NULL part.
+++ ==========================================================================
*/

void (*stpt_tbl[7])() = {

	ipc_state_0,		/* inited to: ipcb_state_1 */
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0,
	ipc_state_0			/* NULL PART -- always assigned to ipc_stat_0 */
};

/*
+++ ==========================================================================
+++	const void (*red1_tbl[])() -- message reduction table -- voice A
+++
+++	Used to transfer to the IPC message processing routines for voice A.
+++ ==========================================================================
*/

const void (*red1_tbl[8])() = {

	set_channel1,		/* 0 */
	part_misc1,			/* 1 */
	gate_ungate1,		/* 2 */
	preset_param1,		/* 3 */
	user_mod1,			/* 4 */
	perform_param1,		/* 5 */
	voice_misc1,		/* 6 */
	never				/* 7 ***** SHOULD NEVER HAPPEN ***** */
};

/*
+++ ==========================================================================
+++	const void (*red2_tbl[])() -- message reduction table -- voice B
+++
+++	Used to transfer to the IPC message processing routines for voice B.
+++ ==========================================================================
*/

const void (*red2_tbl[8])() = {

	set_channel2,		/* 0 */
	part_misc2,			/* 1 */
	gate_ungate2,		/* 2 */
	preset_param2,		/* 3 */
	user_mod2,			/* 4 */
	perform_param2,		/* 5 */
	voice_misc2,		/* 6 */
	never				/* 7 ***** SHOULD NEVER HAPPEN ***** */
};

/*
+++ ==========================================================================
+++	const void (*redb_tbl[])() -- message reduction table -- voices A & B
+++
+++	Used to transfer to the IPC message processing routines for
+++	voices A & B.
+++ ==========================================================================
*/

const void (*redb_tbl[8])() = {	/* message reduction table -- both voices */

	never,				/* 0 ***** SHOULD NEVER HAPPEN ***** */
	part_miscb,			/* 1 */
	never,				/* 2 ***** SHOULD NEVER HAPPEN ***** */
	preset_paramb,		/* 3 */
	user_modb,			/* 4 */
	perform_paramb,		/* 5 */
	never,				/* 6 ***** SHOULD NEVER HAPPEN ***** */
	never				/* 7 ***** SHOULD NEVER HAPPEN ***** */
};

/*+ ********************* PARSER UTILITY FUNCTIONS ************************ */

/*
+++ ==========================================================================
+++	init_ipc() -- initialize IPC
+++
+++	Prototype:
+++
+++		void init_ipc() -- initialize IPC
+++
+++	Calls:
+++
+++		reset_parser()
+++ ==========================================================================
*/

void init_ipc()
{
	WORD i;

	for (i = 0; i < MAPLEN; i++)		/* reset parmap[] */
		parmap[i] = NO_DAC;

	parmap[VCO1_PITCH]	= HW_VCO1_PITCH;
	parmap[VCO1_FINE]	= HW_VCO1_PITCH;
	parmap[VCO1_PWIDTH]	= HW_VCO1_PW;
	parmap[VCO1_VCO2FM]	= HW_VCO1_FM;

	parmap[VCO2_PITCH]	= HW_VCO2_PITCH;
	parmap[VCO2_FINE]	= HW_VCO2_PITCH;
	parmap[VCO2_PWIDTH]	= HW_VCO2_PW;
	parmap[VCO2_VCO1FM]	= HW_VCO2_FM;

	parmap[MM_VCO1]		= HW_MM_IN1;
	parmap[MM_VCO2]		= HW_MM_IN2;
	parmap[MM_NOISE]	= HW_MM_NOISE;
	parmap[MM_FREQ]		= HW_MM_FREQ;
	parmap[MM_RESON]	= HW_MM_RESON;

	parmap[OB_VCO1]		= HW_OB_IN1;
	parmap[OB_VCO2]		= HW_OB_IN2;
	parmap[OB_NOISE]	= HW_OB_NOISE;
	parmap[OB_FREQ]		= HW_OB_FREQ;
	parmap[OB_RESON]	= HW_OB_RESON;

	parmap[MIX_LP]		= HW_MIX_LP;
	parmap[MIX_BP]		= HW_MIX_BP;
	parmap[MIX_HP]		= HW_MIX_HP;
	parmap[MIX_MM]		= HW_MIX_MM;
	parmap[MIX_PAN]		= HW_PAN;
	parmap[MIX_LEVEL]	= HW_VCA;

	for (i = 0; i < 12; i++)			/* reset stvc_tbl[] */
		stvc_tbl[i] = ipc_state_0;

	stvc_tbl[vid1] = ipc1_state_1;		/* set voice A initial state */
	stvc_tbl[vid2] = ipc2_state_1;		/* set voice B initial state */

	for (i = 0; i < 16; i++)			/* reset stch_tbl[] */
		stch_tbl[i] = ipc_state_0;

	vchan1 = 0;							/* start with both voices on ch 0 */
	vchan2 = 0;

	stch_tbl[0] = ipcb_state_1;

	for (i = 0; i < 7; i++)				/* reset stpt_tbl[] */
		stpt_tbl[i] = ipc_state_0;

	vpart1 = 0;							/* start with both voices on part 0 */
	vpart2 = 0;

	stpt_tbl[0] = ipcb_state_1; 

	wca = 0;							/* reset tuning table pointers */
	tpa = &v[VA].tunetab;

	wcb = 0;
	tpb = &v[VB].tunetab;

	reset_parser();						/*$ reset the parser I/O structures */
}

/*
+++ ==========================================================================
+++	set_transpose() -- set VT_TRANSPOSE for a VOICE
+++
+++	Prototype:
+++
+++		void set_transpose(vn)
+++		WORD vn;	VOICE number: 0,1
+++ ==========================================================================
*/

void set_transpose(vn)
WORD vn;
{
	struct voice *vp;
	long sum;
	WORD pws;

	vp	= &v[vn];							/* point at the voice */
	pws	= vp->pwsens;						/* get pitch wheel sensitivity */

	if (0 EQ pws) {							/* 0 = pitch wheel off */

		sum = 0L;

	} else if (pws < 13) {					/* 1..12 = scale pitch wheel */

		sum = (long)vp->curval[VT_PP_PITCHWHL] << 8;
		sum /= pw_scl[pws - 1];

	} else {								/* 13 and above = error */

		sum = 0L;
	}

	sum = sum + (vp->trans << 8);			/* add transposition */

	if (sum > 0x7FFFL)						/* limit range */
		sum = 0x7FFFL;
	else if (sum < 0xFFFF8001L)
		sum = 0xFFFF8001L;

	vp->curval[VT_TRANSPOSE] = (INT)sum;	/* update value tables */
	vp->outval[VT_TRANSPOSE] = (INT)sum;
}

/*
+++ ==========================================================================
+++	get_tt() -- read in a tuning table from the IPC bus
+++
+++	Prototype:
+++
+++		void get_tt(nv)
+++		WORD nv;	VOICE number
+++ ==========================================================================
*/

void get_tt(nv)
WORD nv;
{
	if (nv EQ VA) {			/* VOICE A */

		if (wca LE 0) {		/* word count must be positive and non-zero */

			wca = 0;
			tpa = &v[VA].tunetab;

			return;
		}

		*tpa++ = (ipc_byte1 << 8) | ((ipc_byte2 & 0x001F) << 3);
		--wca;

	} else if (nv EQ VB) {	/* VOICE B */

		if (wcb LE 0) {		/* word count must be positive and non-zero */

			wcb = 0;
			tpb = &v[VB].tunetab;

			return;
		}

		*tpb++ = (ipc_byte1 << 8) | ((ipc_byte2 & 0x001F) << 3);
		--wcb;

	}

#if	0
 else {				/* ERROR -- there's a BUG lurking somewhere!! */

		wca = 0;
		tpa = &v[VA].tunetab;

		wcb = 0;
		tpb = &v[VB].tunetab;
	}
#endif
}

/*
+++ ==========================================================================
+++	part_misc() -- process part miscellaneous function
+++
+++	Prototype:
+++
+++		void part_misc(vn)
+++		WORD vn;	VOICE number
+++
+++	Calls:
+++
+++		do_mod_dst()
+++		get_tt()
+++		mod_vca()
+++		set_pan()
+++		set_transpose()
+++		write_cv()
+++ ==========================================================================
*/

void part_misc(vn)
WORD vn;
{
	INT				mval;			/* modulated value */
	WORD			uval;			/* unmodulated value */
	WORD			i;				/* general index */
	struct voice	*vp;			/* VOICE pointer */
	struct env		*ep;			/* ENV pointer */

	vp = &v[vn];					/* point at the voice */

	/* handle tuning table input in progress */

	if (((vn EQ VA) AND (wca > 0)) OR
	    ((vn EQ VB) AND (wcb > 0))) {

		get_tt(vn);
		return;
	}

	switch (ipc_byte1) {				/* switch on function */

	case 0: /* ALL NOTES OFF */

		vp->vgate		= 0;			/* ungate the note */
		vp->vtrig		= 0;			/* kill the trigger */
		vp->note_ons	= 0;			/* reset note on count */

		write_cv(vn, HW_VCA, 0);		/*$ turn off VCA */

		vp->curval[VT_MIX_LEVEL] = 0;	/* VT_MIX_LEVEL in value table = 0 */
		vp->outval[VT_MIX_LEVEL] = 0;

		for (i = 0; i < 4; i++) {

			ep = &vp->envs[i];

			ep->mode &= 0x7F;		/* reset CYCLE bit */
			ep->estep = 0;			/* step = STOP */
			ep->current = 0;		/* current value = 0 */
			ep->ecntr = 0;			/* counter = 0 */

			*(ep->p_vcur) = 0;		/* VT_ENVn in value table = 0 */
			*(ep->p_vout) = 0;
		}

		break;

	case 1: /* SET INVERSION */

		switch (ipc_byte1 >> 1) {

		case 0:		/* velocity */

			if (ipc_byte2 & 0x01)
				vp->inverts |= M_INV_VEL;
			else
				vp->inverts &= NOT M_INV_VEL;

			break;
		}

		break;

	case 2: /* TUNING TABLE */

		if (vn EQ VA) {		/* voice A */

			tpa = &v[VA].tunetab;
			wca = TT_LEN;

		} else {			/* voice B */

			tpb = &v[VB].tunetab;
			wcb = TT_LEN;
		}

		break;

	case 3: /* SET LEGATO MODE */

		vp->legato	= ipc_byte2;
		vp->note_ons	= 0;

		break;

	case 4:	/* PART TRANSPOSE LS BYTE */

		if (vn EQ VA)
			aoff = (aoff & 0xFF80) | ipc_byte2;		/* voice A */
		else
			boff = (boff & 0xFF80) | ipc_byte2;		/* voice B */

		break;

	case 5:	/* PART TRANSPOSE MS BYTE */

		if (vn EQ VA) {		/* voice A */

			aoff = (aoff & 0x007F) | (ipc_byte2 << 7);

			if (ipc_byte2 & 0x40)
				aoff |= 0xC000;

			v[VA].trans = aoff;

		} else {			/* voice B */

			boff = (boff & 0x007F) | (ipc_byte2 << 7);

			if (ipc_byte2 & 0x40)
				boff |= 0xC000;

			v[VB].trans = boff;
		}

		set_transpose(vn);		/* setup transpose value */

		break;

	case 6:	/* PART LEVEL */

		vp->p_level = ipc_byte2 << 7;				/* setup part level */
		uval = vp->outval[VT_MIX_LEVEL];			/* get current master level */
		mval = mod_vca(vp, uval);					/* adjust for ENV4, etc. */
		write_cv(vn, HW_VCA, (mval >> 3));			/* send it on its way */
		break;

	case 7:	/* PART PAN */

		vp->p_pan = (WORD)ipc_byte2;				/* setup part pan */
		uval = set_pan(vn);							/* adjust for MIDI pan, etc. */
		mval = do_mod_dst(vp, MIX_PAN, uval);		/* do mods: MIX_PAN */
		write_cv(vn, HW_PAN, (mval >> 3));			/* send it on its way */
		break;

	case 8:	/* PITCH WHEEL SENSITIVITY */

		vp->pwsens = ipc_byte2;
		break;
	}
}

/*
+++ ==========================================================================
+++	voice_misc() -- process voice miscellaneous function
+++
+++	Prototype:
+++
+++		void voice_misc(vn)
+++		WORD vn;	VOICE number
+++
+++	Calls:
+++
+++		setpots()
+++		set_transpose()
+++		wqpot3()
+++		write_ipc()
+++ ==========================================================================
*/

void voice_misc(vn)
WORD vn;
{
	BYTE vctls;
	BYTE lastdm;
	INT i;

	switch (ipc_byte1) {

	case 0:		/* TUNE REQUEST */

		if (ipc_byte2 EQ 0) {				/* Tune VCOs and VCFs */

			if (vn EQ VA)					/* ... if command was for Voice A */
				stwat_flag = 1;

		} else if (ipc_byte2 < 81) {		/* offset "A" from 440Hz */

			v[vn].offset = (WORD)vco_off[ipc_byte2 - 1];
			set_transpose(vn);
		}

		break;

	case 1:		/* REQUEST TUNING STATUS BYTE */

		write_ipc(v[vn].tuning);
		break;

	case 2:		/* RESET TUNING TABLES */

		if (ipc_byte2 EQ 0) {						/* 0 = normal */

			for (i = 0; i < 16; i++)				/* restore variables */
				tune_vars[i] = tune_save[i];

			/* output scales */

			cvtable[CV_A_V1_SCL] = tune_vars[8]  + 0x0800;
			cvtable[CV_A_V2_SCL] = tune_vars[9]  + 0x0800;
			cvtable[CV_A_MM_SCL] = tune_vars[10] + 0x0800;
			cvtable[CV_A_OB_SCL] = tune_vars[11] + 0x0800;

			cvtable[CV_B_V1_SCL] = tune_vars[12] + 0x0800;
			cvtable[CV_B_V2_SCL] = tune_vars[13] + 0x0800;
			cvtable[CV_B_MM_SCL] = tune_vars[14] + 0x0800;
			cvtable[CV_B_OB_SCL] = tune_vars[15] + 0x0800;

		} else if (ipc_byte2 EQ 1) {				/* 1 = diagnostic */

			for (i = 0; i < 8; i++)					/* clear offsets */
				tune_vars[i] = 0;

			for (i = 8; i < 16; i++)				/* clear scales */
				tune_vars[i] = 0x0800;

			/* output scales */

			cvtable[CV_A_V1_SCL] = 0x0800;
			cvtable[CV_B_V1_SCL] = 0x0800;
			cvtable[CV_A_V2_SCL] = 0x0800;
			cvtable[CV_B_V2_SCL] = 0x0800;
			cvtable[CV_A_MM_SCL] = 0x0800;
			cvtable[CV_B_MM_SCL] = 0x0800;
			cvtable[CV_A_OB_SCL] = 0x0800;
			cvtable[CV_B_OB_SCL] = 0x0800;
		}

		break;

	case 3:		/* SAVE QUADPOT VALUES */

		setpots();
		break;

	case 4:		/* SET CV NUMBER FOR UPDATE */

		cur_cv = (ipc_byte2 >> 1) & 0x003F;
		break;

	case 5:		/* SET CV VALUE */

		cvtable[dacmap[cur_cv]] = (ipc_byte2 & 0x007F) << 5;
		break;

	case 6:		/* SET CONTROL REGISTER NUMBER FOR UPDATE */

		cur_ctl = ipc_byte2 & 0x00F;
		break;

	case 7:		/* SET CONTROL REGISTER VALUE */

		ctltable[cur_ctl] = ipc_byte2 & 0x007F;

		switch (cur_ctl) {

		case 0:		/* quadpot 1 -- VCO1 Offset */
		case 1:		/* quadpot 2 -- VCO1 Linearity */
		case 2:		/* quadpot 3 -- VCO2 Offset */
		case 3:		/* quadpot 4 -- VCO2 Linearity */
		case 4:		/* quadpot 5 -- VCA Leakage */
		case 5:		/* quadpot 6 -- MM Resonance */
		case 6:		/* quadpot 7 -- OB Offset */
		case 7:		/* quadpot 8 -- OB Resonance */

			if (vn EQ VA)		/* voice A */
				wqpot3(qpa_pot[cur_ctl], qpa_cmd[cur_ctl], ipc_byte2 & 0x03F);
			else				/* voice B */
				wqpot3(qpb_pot[cur_ctl], qpb_cmd[cur_ctl], ipc_byte2 & 0x03F);
			break;
		}

		break;

	case 8: /* CALIBRATION REFERENCE */

		calref = ipc_byte2;
		break;
	}
}

/*
+++ ==========================================================================
+++	never() -- handle bogus message types
+++
+++	Prototype:
+++
+++		void never()
+++
+++	We should NEVER see this -- if we do, there's a BUG lurking somewhere...
+++ ==========================================================================
*/

void never()	{	ipc_state = ipc_state_0;	}

/*+ ********************** VOICE A ONLY REDUCTIONS... ********************** */

/*
+++ ==========================================================================
+++	set_channel1() -- set channel for voice A
+++
+++	Prototype:
+++
+++		void set_channel1()
+++ ==========================================================================
*/

void set_channel1()
{
	int part;

	part = ipc_byte1 & 0x0F;				/* extract new part */

	if (part > 6)							/* check part validity */
		return;

	/* *************** channel assignment processing *************** */

	if (vchan2 EQ vchan1)					/* both voices on same channel ? */
		stch_tbl[vchan2] = ipc2_state_1;	/* voice B gets its own channel */
	else
		stch_tbl[vchan1] = ipc_state_0;		/* clear voice A assignment */

	vchan1 = ipc_byte2 & 0x0F;				/* set new channel for voice A */

	if (vchan1 EQ vchan2)					/* both voices now on same channel ? */
		stch_tbl[vchan1] = ipcb_state_1;	/* put both voices on new channel */
	else
		stch_tbl[vchan1] = ipc1_state_1;	/* put voice A on new channel */

	/* *************** part assignment processing *************** */

	if (vpart2 EQ vpart1)					/* both voices on same part ? */
		stpt_tbl[vpart2] = ipc2_state_1;	/* voice B gets its own part */
	else
		stpt_tbl[vpart1] = ipc_state_0;		/* clear voice A assignment */

	vpart1 = part;							/* set new part for voice A */

	if (vpart1 EQ vpart2)					/* both voices now on same part ? */
		stpt_tbl[vpart1] = ipcb_state_1;	/* put both voices on new part */
	else
		stpt_tbl[vpart1] = ipc1_state_1;	/* put voice A on new part */
}

/*
+++ ==========================================================================
+++	part_misc1() -- process part miscellaneous function for voice A
+++
+++	Prototype:
+++
+++		void part_misc1()
+++
+++	Calls:
+++
+++		part_misc()
+++ ==========================================================================
*/

void part_misc1()		{	part_misc(VA);	}

/*
+++ ==========================================================================
+++	preset_param1() -- process preset parameter for voice A
+++
+++	Prototype:
+++
+++		void preset_param1()
+++
+++	Calls:
+++
+++		preset_param()
+++ ==========================================================================
*/

void preset_param1()	{	preset_param(VA);	}

/*
+++ ==========================================================================
+++	user_mod1() -- process user mod for voice A
+++
+++	Prototype:
+++
+++		void user_mod1()
+++
+++	Calls:
+++
+++		user_mod()
+++ ==========================================================================
*/

void user_mod1()		{	user_mod(VA);	}

/*
+++ ==========================================================================
+++	perform_param1() -- process performance parameter for voice A
+++
+++	Prototype:
+++
+++		void perform_param1()
+++
+++	Calls:
+++
+++		perform_param()
+++ ==========================================================================
*/

void perform_param1()	{	perform_param(VA);	}

/*
+++ ==========================================================================
+++	voice_misc1() -- process voice A miscellaneous function
+++
+++	Prototype:
+++
+++		void voice_misc1()
+++
+++	Calls:
+++
+++		voice_misc()
+++ ==========================================================================
*/

void voice_misc1()		{	voice_misc(VA);	}

/*+ ************************ VOICE B ONLY REDUCTIONS ******************** */

/*
+++ ==========================================================================
+++	set_channel2() -- set channel for voice B
+++
+++	Prototype:
+++
+++		void set_channel2()
+++ ==========================================================================
*/

void set_channel2()
{
	int part;

	part = ipc_byte1 & 0x0F;				/* extract new part */

	if (part > 6)							/* check part validity */
		return;

	/* *************** channel assignment processing *************** */

	if (vchan1 EQ vchan2)					/* both voices on same channel ? */
		stch_tbl[vchan1] = ipc1_state_1;	/* voice A gets its own channel */
	else
		stch_tbl[vchan2] = ipc_state_0;		/* clear voice B assignment */

	vchan2 = ipc_byte2 & 0x0F;				/* set new channel for voice B */

	if (vchan2 EQ vchan1)					/* both voices now on same channel ? */
		stch_tbl[vchan2] = ipcb_state_1;	/* put both voices on new channel */
	else
		stch_tbl[vchan2] = ipc2_state_1;	/* put voice B on new channel */

	/* *************** part assignment processing *************** */

	if (vpart1 EQ vpart2)					/* both voices on same part ? */
		stpt_tbl[vpart1] = ipc1_state_1;	/* voice A gets its own part */
	else
		stpt_tbl[vpart2] = ipc_state_0;		/* clear voice B assignment */

	vpart2 = part;							/* set new part for voice B */

	if (vpart2 EQ vpart1)					/* both voices now on same part ? */
		stpt_tbl[vpart2] = ipcb_state_1;	/* put both voices on new part */
	else
		stpt_tbl[vpart2] = ipc2_state_1;	/* put voice B on new part */
}

/*
+++ ==========================================================================
+++	part_misc2() -- process part miscellaneous function for voice B
+++
+++	Prototype:
+++
+++		void part_misc2()
+++
+++	Calls:
+++
+++		part_misc()
+++ ==========================================================================
*/

void part_misc2()		{	part_misc(VB);	}

/*
+++ ==========================================================================
+++	preset_param2() -- process preset parameter for voice B
+++
+++	Prototype:
+++
+++		void preset_param2()
+++
+++	Calls:
+++
+++		preset_param()
+++ ==========================================================================
*/

void preset_param2()	{	preset_param(VB);	}

/*
+++ ==========================================================================
+++	user_mod2() -- process user mod for voice B
+++
+++	Prototype:
+++
+++		void user_mod2()
+++
+++	Calls:
+++
+++		user_mod()
+++ ==========================================================================
*/

void user_mod2()		{	user_mod(VB);	}

/*
+++ ==========================================================================
+++	perform_param2() -- process performance parameter for voice B
+++
+++	Prototype:
+++
+++		void perform_param2()
+++
+++	Calls:
+++
+++		perform_param()
+++ ==========================================================================
*/

void perform_param2()	{	perform_param(VB);	}

/*
+++ ==========================================================================
+++	voice_misc2() -- process voice B miscellaneous function
+++
+++	Prototype:
+++
+++		voice_misc2()
+++
+++	Calls:
+++
+++		voice_misc()
+++ ==========================================================================
*/

void voice_misc2()		{	voice_misc(VB);	}

/* ************************* 2 VOICE REDUCTIONS *************************** */

/*
+++ ==========================================================================
+++	proc_both() -- process function for both voices
+++
+++	Prototype:
+++
+++		void proc_both(what)
+++		void (*what)()
+++
+++	Calls:
+++
+++		(*what)()
+++ ==========================================================================
*/

void proc_both(what)
void (*what)();
{
	WORD o1, o2;

	o1 = ipc_byte1;		o2 = ipc_byte2;		(*what)(VA);
	ipc_byte1 = o1;		ipc_byte2 = o2;		(*what)(VB);
}

/*
+++ ==========================================================================
+++	part_miscb() -- process part miscellaneous function for both voices
+++
+++	Prototype:
+++
+++		void part_miscb()
+++
+++	Calls:
+++
+++		part_misc()
+++ ==========================================================================
*/

void part_miscb()	{	proc_both(part_misc);	}

/*
+++ ==========================================================================
+++	preset_paramb() -- process performance parameter for both voices
+++
+++	Prototype:
+++
+++		void preset_paramb()
+++
+++	Calls:
+++
+++		preset_param()
+++ ==========================================================================
*/

void preset_paramb()	{	proc_both(preset_param);	}

/*
+++ ==========================================================================
+++	user_modb() -- process user mod for both voices
+++
+++	Prototype:
+++
+++		void user_modb()
+++
+++	Calls:
+++
+++		user_mod()
+++ ==========================================================================
*/

void user_modb()	{	proc_both(user_mod);	}

/*
+++ ==========================================================================
+++	perform_paramb() -- process performance parameter for both voices
+++
+++	Prototype:
+++
+++		void perform_paramb()
+++
+++	Calls:
+++
+++		perform_param()
+++ ==========================================================================
*/

void perform_paramb()	{	proc_both(perform_param);	}

/* The End */
