/*
+++ =======================================================================
+++	File:		IPC2.C
+++	Purpose:	OB-MX IPC message parser -- utilities and common reductions
+++	Original:		1993-05-26	D.N. Lynx Crowe
+++	Revision:	82	1993-12-15	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		perform_param()		process the receipt of a performance parameter
+++		preset_param()		process the receipt of a preset parameter
+++		set_adj()			set the VCO ADJUST values
+++		set_env()			setup ENV parameters
+++		set_lfo()			setup LFO parameters
+++		set_mlt()			set the multiplier for a patch
+++		set_vcf()			setup VCF parameters
+++		set_vco()			setup VCO parameters
+++		user_mod()			process the receipt of a user modulation
+++ =======================================================================
*/

#include "voice.h"
#include "vars.h"

#define	VELSCALE	400		/* 1000 * velocity sensitivity scale factor */

#define	MMOB_BASE	0x2C80	/* MM/OB VCF base frequency */

/*+ ====================== external function references =================== */

extern INT			do_mod_dst();		/*+ do a MOD destination change */
extern void			do_mod_src();		/*+ do a MOD source change */
extern void			mod_ins();			/*+ insert a MOD in a list */
extern void			mod_rmv();			/*+ remove a MOD from a list */
extern INT			mod_vca();			/*+ modulate VCA by ENV4 */
extern WORD			set_pan();			/*+ set VT_MIX_PAN */
extern void			set_transpose();	/*+ set VT_TRANSPOSE for a voice */
extern void			write_cv();			/*+ write a value to a DAC CV */

/*+ ************************* UTILITY ROUTINES ************************* */

/*
+++ =======================================================================
+++	set_adj() -- set the VCO ADJUST values
+++
+++	Prototype:
+++
+++		void set_adj()
+++
+++	Calls:
+++
+++		do_mod_src()
+++
+++	Calculates the VCO1_ADJUST and VCO2_ADJUST values from
+++	VCO1_PITCH, VCO1_FINE, VCO2_PITCH, VCO2_FINE
+++ =======================================================================
*/

void set_adj()
{
	struct voice *vp;		/* VOICE pointer */
	INT			pval;		/* VCO pitch value */
	INT			i;			/* VOICE index */
	WORD		rv;			/* value scratch */

	for (i = 0; i < 2; i++) {

		vp = &v[i];

		/* ------------------------------------ */
		/* ----- calculate VT_VCO1_ADJUST ----- */
		/* ------------------------------------ */

		pval =  (vp->curval[VT_VCO1_PITCH] & 0x7F00) + 
				((INT)((vp->curval[VT_VCO1_FINE] >> 6) & 0x01FC) - 0x0100);

		pval -= 0x0400;				/* center round middle C */

		if (pval < 0)				/* don't let pitch go negative */
			rv = 0;
		else
			rv = (WORD)pval;

		do_mod_src(vp, VT_VCO1_ADJUST, rv);			/* do mods: VCO1_PITCH, _FINE */

		/* ------------------------------------ */
		/* ----- calculate VT_VCO2_ADJUST ----- */
		/* ------------------------------------ */

		pval =  (vp->curval[VT_VCO2_PITCH] & 0x7F00) + 
				((INT)((vp->curval[VT_VCO2_FINE] >> 6) & 0x01FC) - 0x0100);

		pval -= 0x0400;				/* center round middle C */

		if (pval < 0)				/* don't let pitch go negative */
			rv = 0;
		else
			rv = (WORD)pval;

		do_mod_src(vp, VT_VCO2_ADJUST, rv);			/* do mods: VCO2_PITCH, _FINE */
	}
}

/*
+++ =======================================================================
+++	set_mlt() -- set the multiplier for a patch
+++
+++	Prototype:
+++
+++		void set_mlt(vp, ind, val, tbl)
+++		struct voice *vp;		voice pointer
+++		WORD ind;				MOD index
+++		WORD val;				multiplier byte
+++		INT *tbl;				multiplier table pointer
+++
+++	Calls:
+++
+++		mod_ins()
+++		mod_rmv()
+++ =======================================================================
*/

void set_mlt(vp, ind, val, tbl)
struct voice *vp;
WORD ind;
WORD val;
INT *tbl;
{
	struct mod *mp;

	mp = &vp->mods[ind];

	mp->mlt	= tbl[val];

	if ((mp->mlt NE 0) AND (mp->src NE NO_SRC) AND (mp->dst NE NO_DST))
		mod_ins(vp, mp);
	else
		mod_rmv(vp, mp);
}

/*
+++ =======================================================================
+++	set_vco() -- setup VCO parameters
+++
+++	Prototype:
+++
+++		WORD set_vco(vp, vn)
+++		struct voice *vp;	VOICE structure pointer
+++		WORD vn;			VCO number
+++
+++	on entry:
+++
+++		ipc_byte1	parameter number
+++		ipc_byte2	data value
+++
+++	returns:
+++
+++		parameter value to be modulated.
+++
+++	Calls:
+++
+++		do_mod_src()
+++		set_mlt()
+++		
+++ =======================================================================
*/

WORD set_vco(vp, vn)
struct voice *vp;
WORD vn;
{
	WORD		nc;			/* case value */
	WORD		np;			/* patch index */
	struct vco	*op;		/* VCO structure pointer */
	INT			pval;		/* VCO pitch value */
	WORD		rv;			/* return value */

	rv = (WORD)ipc_byte2 << 8;				/* rv = input expanded to 16 bits */

	if (vn EQ VCO_1)						/* check VCO number */
		nc = (WORD)ipc_byte1 - VCO1_BASE;	/* set case value */
	else if (vn EQ VCO_2)
		nc = (WORD)ipc_byte1 - VCO2_BASE;	/* set case value */
	else
		return(rv);							/* ERROR:  just return rv */

	op = &vp->vcos[vn];						/* set VCO pointer */

	switch (nc) {

	case VCO_PITCH:		op->pitch	= ipc_byte2;

		if (vn EQ VCO_1)							/* update value tables */
			do_mod_src(vp, VT_VCO1_PITCH, rv);		/* do mods: VCO1_PITCH */
		else
			do_mod_src(vp, VT_VCO2_PITCH, rv);		/* do mods: VCO2_PITCH */

		goto vco_pit;

	case VCO_FINE:		op->fine	= ipc_byte2 & 0x7E;

		rv &= 0x7E00;

		if (vn EQ VCO_1)							/* update value tables */
			do_mod_src(vp, VT_VCO1_FINE, rv);		/* do mods: VCO1_FINE */
		else
			do_mod_src(vp, VT_VCO2_FINE, rv);		/* do mods: VCO2_FINE */

vco_pit:	/* calculate ADJUST from coarse and fine values and tuning offset */

		if (vn EQ VCO_1)  {

			pval =  (vp->curval[VT_VCO1_PITCH] & 0x7F00) + 
					((INT)((vp->curval[VT_VCO1_FINE] >> 6) & 0x01FC) - 0x0100);

		} else {

			pval =  (vp->curval[VT_VCO2_PITCH] & 0x7F00) + 
					((INT)((vp->curval[VT_VCO2_FINE] >> 6) & 0x01FC) - 0x0100);
		}

		pval -= 0x0400;				/* center round middle C */

		if (pval < 0)				/* don't let pitch go negative */
			rv = 0;
		else
			rv = (WORD)pval;

		break;

	case VCO_TRACK:		op->track	= ipc_byte2;				break;

	case VCO_PORT:		op->port	= ipc_byte2;
						op->ptick	= p_ticks[ipc_byte2];
						op->ptcnt	= op->ptick;
						rv			= p_incrs[ipc_byte2];		break;

	case VCO_PWIDTH:	op->pwidth	= ipc_byte2;				break;

	case VCO_SHAPE:		op->wshape	= ipc_byte2;				break;

	case VCO_VCOFM:		op->vcofm	= ipc_byte2;				break;

	case VCO_ENVFM:		op->env1fm	= ipc_byte2;
						rv			= pml_tab[ipc_byte2] << 1;	break;

	case VCO_LFOFM:		op->lfo1fm	= ipc_byte2;
						rv			= pml_tab[ipc_byte2] << 1;	break;

	case VCO_PWM:		op->pwm		= ipc_byte2;

		if (vn EQ VCO_1) {						/* VCO_1 ------------------ */

			if (ipc_byte2 GE 64) {				/* VCO_1 ENV2 -> PWIDTH */

				set_mlt(vp, 4, ipc_byte2, mlt_tab);
				set_mlt(vp, 5, 64, mlt_tab);

			} else {							/* VCO_1 LFO2 -> PWIDTH */

				set_mlt(vp, 4, 64, mlt_tab);
				set_mlt(vp, 5, 126 - ipc_byte2, mlt_tab);
			}

			rv = vp->curval[VT_VCO1_PWIDTH];

		} else {								/* VCO_2 ------------------ */

			if (ipc_byte2 GE 64) {				/* VCO_2 ENV2 -> PWIDTH */

				set_mlt(vp, 6, ipc_byte2, mlt_tab);
				set_mlt(vp, 7, 64, mlt_tab);

			} else {							/* VCO_2 LFO2 -> PWIDTH */

				set_mlt(vp, 6, 64, mlt_tab);
				set_mlt(vp, 7, 126 - ipc_byte2, mlt_tab);
			}

			rv = vp->curval[VT_VCO2_PWIDTH];
		}

		break;
	}

	return(rv);
}

/*
+++ =======================================================================
+++	set_vcf() -- setup VCF parameters
+++
+++	Prototype:
+++
+++		WORD set_vcf(vp, nf)
+++		struct voice *vp;	voice structure pointer
+++		WORD nf;			filter number
+++
+++	on entry:
+++
+++		ipc_byte1	parameter number
+++		ipc_byte2	data value
+++
+++	returns:
+++
+++		value to be modulated
+++
+++	Calls:
+++
+++		do_mod_src
+++ =======================================================================
*/

WORD set_vcf(vp, nf)
struct voice *vp;
WORD nf;
{
	WORD		nc;			/* case value */
	WORD		np;			/* patch number */
	WORD		rv;			/* return value */
	INT			mv;			/* multiplier value */
	struct vcf	*fp;		/* filter pointer */

	rv = (WORD)ipc_byte2 << 8;			/* rv = input expanded to 16 bits */

	if (nf EQ MM_VCF)					/* check VCF number */
		nc = (WORD)ipc_byte1 - MM_BASE;	/* set MM_VCF case value */
	else if (nf EQ OB_VCF)
		nc = (WORD)ipc_byte1 - OB_BASE;	/* set OB_VCF case value */
	else
		return(rv);						/* ERROR:  just return rv */

	fp = &vp->vcfs[nf];					/* set VCF pointer */

	mv = pml_tab[(WORD)ipc_byte2] << 1;	/* set possible multiplier value */

	switch (nc) {

	case VCF_VCO1:		fp->vco1	= ipc_byte2;	break;

	case VCF_VCO2:		fp->vco2	= ipc_byte2;	break;

	case VCF_NOISE:		fp->noise	= ipc_byte2;	break;

	case VCF_FREQ:		fp->freq	= ipc_byte2;

		rv = ((WORD)ipc_byte2 << 7) + MMOB_BASE;

		break;

	case VCF_RESON:		fp->reson	= ipc_byte2;	break;

	case VCF_ENVFM:		fp->envfm	= ipc_byte2;

		if (nf EQ MM_VCF) {

			do_mod_src(vp, VT_MM_ENV1FM, mv);
			rv = vp->curval[VT_MM_FREQ];			/* MM_VCF ENV1 -> FREQ */

		} else {

			do_mod_src(vp, VT_OB_ENV2FM, mv);
			rv = vp->curval[VT_OB_FREQ];			/* OB_VCF ENV2 -> FREQ */
		}

		break;

	case VCF_LFOFM:		fp->lfofm	= ipc_byte2;

		if (nf EQ MM_VCF) {

			do_mod_src(vp, VT_MM_LFO1FM, mv);
			rv = vp->curval[VT_MM_FREQ];			/* MM_VCF LFO1 -> FREQ */

		} else {

			do_mod_src(vp, VT_OB_LFO2FM, mv);
			rv = vp->curval[VT_OB_FREQ];			/* OB_VCF LFO2 -> FREQ */
		}

		break;

	case VCF_TRACK:		fp->kbtrk	= ipc_byte2;

		if (nf EQ MM_VCF)
			rv = vp->curval[VT_MM_FREQ];			/* MM_VCF NOTE -> FREQ */
		else
			rv = vp->curval[VT_OB_FREQ];			/* OB_VCF NOTE -> FREQ */

		break;
	}

	return(rv);
}

/*
+++ =======================================================================
+++	set_lfo() -- setup LFO parameters
+++
+++	Prototype:
+++
+++		WORD set_lfo(vp, nl)
+++		struct voice *vp;	VOICE structure pointer
+++		WORD nl;			LFO number
+++
+++	on entry:
+++
+++		ipc_byte1	parameter number
+++		ipc_byte2	data value
+++
+++	returns:
+++
+++		value to be modulated.
+++ =======================================================================
*/

WORD set_lfo(vp, nl)
struct voice *vp;
WORD nl;
{
	WORD nc;				/* case value */
	WORD rv;				/* return value */
	struct lfo *lp;			/* LFO structure pointer */

	rv = ipc_byte2 << 8;				/* expand input to 16 bits */

	if (nl EQ LFO_1)					/* check LFO number */
		nc = ipc_byte1 - LFO1_BASE;		/* set LFO_1 case value */
	else if (nl EQ LFO_2)
		nc = ipc_byte1 - LFO2_BASE;		/* set LFO_2 case value */
	else if (nl EQ LFO_3)
		nc = ipc_byte1 - LFO3_BASE;		/* set LFO_3 case value */
	else
		return(rv);						/* ERROR:  just return rv */

	lp = &vp->lfos[nl];					/* set LFO pointer */

	switch (nc) {

	case LFO_DELAY:		lp->delay	= ipc_byte2;
						lp->dtcnt	= l_ticks[ipc_byte2];
						rv			= l_incrs[ipc_byte2];	break;

	case LFO_RATE:		lp->rate	= ipc_byte2;
						lp->tcnt	= r_ticks[ipc_byte2];
						rv			= r_incrs[ipc_byte2];	break;

	case LFO_OFFSET:	lp->offset	= ipc_byte2;
						rv			= off_val[ipc_byte2];	break;

	case LFO_S_H:		lp->quant	= ipc_byte2;
						rv			= lfosh[ipc_byte2];		break;

	case LFO_SHAPE:		lp->shape	= ipc_byte2;			break;

	}

	return(rv);
}

/*
+++ =======================================================================
+++	set_env() -- setup ENV parameters
+++
+++	Prototype:
+++
+++		WORD set_env(vp, ne)
+++		struct voice *vp;	VOICE structure pointer
+++		WORD ne;			envelope number
+++
+++	on entry:
+++
+++		ipc_byte1	parameter number
+++
+++	returns:
+++
+++		value to be modulated
+++ =======================================================================
*/

WORD set_env(vp, ne)
struct voice *vp;
WORD ne;
{
	WORD		nc;				/* case value */
	WORD		rv;				/* return value temporary */
	struct env	*ep;			/* ENV pointer */

	rv = (WORD)ipc_byte2;		/* setup default return value */

	if (ne EQ ENV_1) {

		nc = ipc_byte1 - ENV1_BASE;	/* map parameter number to case value */
		ep = &vp->envs[ENV_1];		/* point at the ENV */

	} else if (ne EQ ENV_2) {

		nc = ipc_byte1 - ENV2_BASE;	/* map parameter number to case value */
		ep = &vp->envs[ENV_2];		/* point at the ENV */

	} else if (ne EQ ENV_3) {

		nc = ipc_byte1 - ENV3_BASE;	/* map parameter number to case value */
		ep = &vp->envs[ENV_3];		/* point at the ENV */

	} else if (ne EQ ENV_4) {

		nc = ipc_byte1 - ENV4_BASE;	/* map parameter number to case value */
		ep = &vp->envs[ENV_4];		/* point at the ENV */

	} else
		return(rv);

	switch (nc) {

	case ENV_MODE:

		ep->mode = (ep->mode & 0xE0) | (ipc_byte2 & 0x1F);
		break;

	case ENV_ATTACK:	ep->attack		= ipc_byte2;
						rv				= t_incrs[ep->attack];		break;

	case ENV_ATCK_DEL:	ep->atck_del	= ipc_byte2;
						rv				= t_incrs[ep->atck_del];	break;

	case ENV_DECAY:		ep->decay		= ipc_byte2;
						rv				= t_incrs[ep->decay];		break;

	case ENV_DCAY_DEL:	ep->dcay_del	= ipc_byte2;
						rv				= t_incrs[ep->dcay_del];	break;

	case ENV_SUSTAIN:	ep->sustain		= ipc_byte2;
						rv				= ipc_byte2 << 8;			break;

	case ENV_SUS_DCAY:	ep->sus_dcay	= ipc_byte2;

		rv = t_incrs[ep->sus_dcay];

		switch (ne) {

		case ENV_1:

			vp->curval[VT_ENV1_SUS_DCAY] = rv;
			vp->outval[VT_ENV1_SUS_DCAY] = rv;

			break;

		case ENV_2:

			vp->curval[VT_ENV2_SUS_DCAY] = rv;
			vp->outval[VT_ENV2_SUS_DCAY] = rv;

			break;

		case ENV_3:

			vp->curval[VT_ENV3_SUS_DCAY] = rv;
			vp->outval[VT_ENV3_SUS_DCAY] = rv;

			break;

		case ENV_4:

			vp->curval[VT_ENV4_SUS_DCAY] = rv;
			vp->outval[VT_ENV4_SUS_DCAY] = rv;

			break;
		}

		break;

	case ENV_RELEASE:	ep->release		= ipc_byte2;
						rv				= t_incrs[ep->release];		break;

	case ENV_VEL_SENS:	ep->vel_sens	= ipc_byte2;

		rv = ((long)mlt_tab[64 + (ipc_byte2 >> 1)] * VELSCALE) / 1000;

		switch (ne) {

		case ENV_1:

			vp->curval[VT_ENV1_VEL_SENS] = rv;
			vp->outval[VT_ENV1_VEL_SENS] = rv;

			break;

		case ENV_2:

			vp->curval[VT_ENV2_VEL_SENS] = rv;
			vp->outval[VT_ENV2_VEL_SENS] = rv;

			break;

		case ENV_3:

			vp->curval[VT_ENV3_VEL_SENS] = rv;
			vp->outval[VT_ENV3_VEL_SENS] = rv;

			break;

		case ENV_4:

			vp->curval[VT_ENV4_VEL_SENS] = rv;
			vp->outval[VT_ENV4_VEL_SENS] = rv;

			break;
		}

		break;
	}

	return(rv);
}

/*+ ************************ REDUCTION ROUTINES ************************ */

/*
+++ =======================================================================
+++	preset_param() -- process the receipt of a preset parameter
+++
+++	Prototype:
+++
+++		void preset_param(vb)
+++		BYTE vb;	voice number, VA = 0 or VB = 1
+++
+++	on entry:
+++
+++		ipc_byte1 contains the 1st data byte
+++		ipc_byte2 contains the 2nd data byte
+++
+++	Calls:
+++
+++		do_mod_dst()
+++		do_mod_src()
+++		mod_vca()
+++		set_env()
+++		set_lfo()
+++		set_pan()
+++		set_vcf()
+++		set_vco()
+++		write_cv()
+++ =======================================================================
*/

void preset_param(vb)
BYTE vb;
{
	WORD			cvnum;			/* CV number temporary */
	INT				mval;			/* modulated value */
	WORD			tval;			/* temporary value */
	WORD			pval;			/* previous value */
	WORD			uval;			/* un-modulated value */
	WORD			vctls;			/* VCO control bits */
	struct voice	*vp;			/* VOICE pointer */

	vp = &v[(WORD)vb];				/* point at the voice structure */

	switch (ipc_byte1) {			/* swtich on preset parameter number */

	case VCO1_PITCH:
	case VCO1_FINE:

		uval = set_vco(vp, VCO_1);						/* set VCO parameter */
		do_mod_src(vp, VT_VCO1_ADJUST, uval);			/* do mods: VCO1_PITCH, _FINE */
		break;

	case VCO1_PWIDTH:
	case VCO1_VCO2FM:

		uval	= set_vco(vp, VCO_1);					/* set VCO parameter */
		mval	= do_mod_dst(vp, ipc_byte1, uval);		/* do mods: VCO1_PWIDTH, _VCO2FM */
		cvnum	= parmap[ipc_byte1];					/* map parameter to CV */
		write_cv(vb, cvnum, (mval >> 3));				/* send it on its way */
		break;

	case VCO1_PORT:

		uval = set_vco(vp, VCO_1);						/* set VCO parameter */
		(void)do_mod_dst(vp, VCO1_PORT, uval);			/* do mods: VCO1_PORT */
		break;

	case VCO1_TRACK:

		(void)set_vco(vp, VCO_1);						/* set VCO parameter */
		break;

	case VCO1_ENV1FM:
	case VCO1_LFO1FM:

		uval = set_vco(vp, VCO_1);						/* set VCO parameter */
		do_mod_src(vp, par_val[(WORD)ipc_byte1], uval);	/* do mods: VCO1_TRACK, _ENV1FM, _LFO1FM */
		break;

	case VCO1_PWM:

		uval = set_vco(vp, VCO_1);						/* set VCO parameter */
		mval = do_mod_dst(vp, VCO1_PWIDTH, uval);		/* do mods: VCO1_PWM */
		write_cv(vb, HW_VCO1_PW, (mval >> 3));			/* send it on its way */
		break;

	case VCO1_SHAPE:

		(void)set_vco(vp, VCO_1);						/* set VCO parameter */

		if (vb EQ VA) {

			ctltable[8]		= ipc_byte2 & 0x0F;

			vctls			= ctltable[8] & 0x0F
							| ((ctltable[9] & 0x0F) << 4);

			/* swap bits to fix the hardware */

			vctls 			= ((vctls & 0x80) >> 4)
							| ((vctls & 0x08) << 4) 
							| (vctls & 0x77);

			/* invert waveshape bits to fix the hardware */

			VA_CTL		= vctls ^ 0x77;

		} else if (vb EQ VB) {

			ctltable[10]	= ipc_byte2 & 0x0F;

			vctls			= ctltable[10] & 0x0F
							| ((ctltable[11] & 0x0F) << 4);

			/* swap bits to fix the hardware */

			vctls 			= ((vctls & 0x80) >> 4)
							| ((vctls & 0x08) << 4) 
							| (vctls & 0x77);

			/* invert waveshape bits to fix the hardware */

			VB_CTL			= vctls ^ 0x77;
		}

		break;

	case VCO2_PITCH:
	case VCO2_FINE:

		uval = set_vco(vp, VCO_2);						/* set VCO parameter */
		do_mod_src(vp, VT_VCO2_ADJUST, uval);			/* do mods: VCO2_PITCH, _FINE */
		break;

	case VCO2_PWIDTH:
	case VCO2_VCO1FM:

		uval	= set_vco(vp, VCO_2);					/* set VCO parameter */
		mval	= do_mod_dst(vp, ipc_byte1, uval);		/* do mods: VCO2_PWIDTH, _VCO1FM */
		cvnum	= parmap[ipc_byte1];					/* map parameter to CV */
		write_cv(vb, cvnum, (mval >> 3));				/* send it on its way */
		break;

	case VCO2_PORT:

		uval = set_vco(vp, VCO_2);						/* set VCO parameter */
		(void)do_mod_dst(vp, VCO2_PORT, uval);			/* do mods: VCO2_PORT */
		break;

	case VCO2_TRACK:

		(void)set_vco(vp, VCO_2);						/* set VCO parameter */
		break;

	case VCO2_ENV1FM:
	case VCO2_LFO1FM:

		uval = set_vco(vp, VCO_2);						/* set VCO parameter */
		do_mod_src(vp, par_val[(WORD)ipc_byte1], uval);	/* do mods: VCO2_TRACK, _ENV1FM, _LFO1FM */
		break;

	case VCO2_PWM:

		uval = set_vco(vp, VCO_2);						/* set VCO parameter */
		mval = do_mod_dst(vp, VCO2_PWIDTH, uval);		/* do mods: VCO2_PWM */
		write_cv(vb, HW_VCO2_PW, (mval >> 3));			/* send it on its way */
		break;

	case VCO2_SHAPE:

		set_vco(vp, VCO_2);								/* set VCO parameter */

		if (vb EQ VA) {

			ctltable[9]		= ipc_byte2 & 0x0F;

			vctls			= ctltable[8] & 0x0F
							| ((ctltable[9] & 0x0F) << 4);

			/* swap bits to fix the hardware */

			vctls 			= ((vctls & 0x80) >> 4)
							| ((vctls & 0x08) << 4) 
							| (vctls & 0x77);

			/* invert waveshape bits to fix the hardware */

			VA_CTL			= vctls ^ 0x77;

		} else if (vb EQ VB) {

			ctltable[11]	= ipc_byte2 & 0x0F;

			vctls			= ctltable[10] & 0x0F
							| ((ctltable[11] & 0x0F) << 4);

			/* swap bits to fix the hardware */

			vctls 			= ((vctls & 0x80) >> 4)
							| ((vctls & 0x08) << 4) 
							| (vctls & 0x77);

			/* invert waveshape bits to fix the hardware */

			VB_CTL			= vctls ^ 0x77;
		}

		break;

	case MM_VCO1:
	case MM_VCO2:
	case MM_NOISE:
	case MM_FREQ:
	case MM_RESON:

		uval	= set_vcf(vp, MM_VCF);					/* set VCF parameter */
		mval	= do_mod_dst(vp, ipc_byte1, uval);		/* do mods: MM_VCO1, _VCO2, _NOISE, _FREQ, _RESON */
		cvnum	= parmap[ipc_byte1];					/* map parameter to CV */
		write_cv(vb, cvnum, (mval >> 3));				/* send it on its way */
		break;

	case MM_ENV1FM:
	case MM_LFO1FM:
	case MM_TRACK:

		uval	= set_vcf(vp, MM_VCF);					/* set VCF parameter */
 		mval	= do_mod_dst(vp, MM_FREQ, uval);		/* do mods: MM_ENV1FM, _LFO1FM, _TRACK */
		write_cv(vb, HW_MM_FREQ, (mval >> 3));			/* send it on its way */
		break;

	case OB_VCO1:
	case OB_VCO2:
	case OB_NOISE:
	case OB_FREQ:
	case OB_RESON:

		uval	= set_vcf(vp, OB_VCF);					/* set VCF parameter */
		mval	= do_mod_dst(vp, ipc_byte1, uval);		/* do mods: OB_VCO1, _VCO2, _NOISE, _FREQ, _RESON */
		cvnum	= parmap[ipc_byte1];					/* map parameter to CV */
		write_cv(vb, cvnum, (mval >> 3));				/* send it on its way */
		break;

	case OB_ENV2FM:
	case OB_LFO2FM:
	case OB_TRACK:

		uval	= set_vcf(vp, OB_VCF);					/* set VCF parameter */
		mval	= do_mod_dst(vp, OB_FREQ, uval);		/* do mods: OB_ENV2FM, _LFO2FM, _TRACK */
		write_cv(vb, HW_OB_FREQ, (mval >> 3));			/* send it on its way */
		break;

	case MIX_LP:
	case MIX_BP:
	case MIX_HP:
	case MIX_MM:

		uval	= (WORD)ipc_byte2 << 8;					/* setup filter level */
		mval	= do_mod_dst(vp, ipc_byte1, uval);		/* do mods: MIX_LP, _BP, _HP, _MM */
		cvnum	= parmap[ ipc_byte1 ];					/* map parameter to CV */
		write_cv(vb, cvnum, (mval >> 3));				/* send it on its way */
		break;

	case MIX_LEVEL:

		uval	= (WORD)ipc_byte2 << 8;					/* setup mix level */
		mval	= do_mod_dst(vp, MIX_LEVEL, uval);		/* do mods: MIX_LEVEL */
		mval	= mod_vca(vp, mval);					/* adjust for ENV4 */
		write_cv(vb, HW_VCA, (mval >> 3));				/* send it on its way */
		break;

	case MIX_PAN:

		vp->v_pan = (WORD)ipc_byte2;					/* setup pan position */
		uval	= set_pan(vb);
		mval	= do_mod_dst(vp, MIX_PAN, uval);		/* do mods: MIX_PAN */
		write_cv(vb, HW_PAN, (mval >> 3));				/* send it on its way */
		break;

	case LFO1_DELAY:
	case LFO1_RATE:
	case LFO1_OFFSET:

		uval = set_lfo(vp, LFO_1);						/* set LFO parameter */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: LFO1_DELAY, _RATE, _OFFSET */
		break;

	case LFO1_S_H:

		uval = set_lfo(vp, LFO_1);						/* set LFO parameter */
		vp->curval[VT_LFO1_S_H] = uval;
		vp->outval[VT_LFO1_S_H] = uval;
		break;

	case LFO1_SHAPE:

		(void)set_lfo(vp, LFO_1);						/* set LFO parameter */
		break;

	case LFO2_DELAY:
	case LFO2_RATE:
	case LFO2_OFFSET:

		uval = set_lfo(vp, LFO_2);						/* set LFO parameter */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: LFO2_DELAY, _RATE, _OFFSET */
		break;

	case LFO2_S_H:

		uval = set_lfo(vp, LFO_2);						/* set LFO parameter */
		vp->curval[VT_LFO2_S_H] = uval;	
		vp->outval[VT_LFO2_S_H] = uval;
		break;

	case LFO2_SHAPE:

		set_lfo(vp, LFO_2);								/* set LFO parameter */
		break;

	case LFO3_DELAY:
	case LFO3_RATE:
	case LFO3_OFFSET:

		uval = set_lfo(vp, LFO_3);						/* set LFO parameter */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: LFO3_DELAY, _RATE, _OFFSET */
		break;

	case LFO3_S_H:

		uval = set_lfo(vp, LFO_3);						/* set LFO parameter */
		vp->curval[VT_LFO3_S_H] = uval;
		vp->outval[VT_LFO3_S_H] = uval;
		break;

	case LFO3_SHAPE:

		set_lfo(vp, LFO_3);								/* set LFO parameter */
		break;

	case ENV1_ATTACK:
	case ENV1_DECAY:
	case ENV1_SUSTAIN:
	case ENV1_RELEASE:
	case ENV1_ATCK_DEL:
	case ENV1_DCAY_DEL:

		uval = set_env(vp, ENV_1);						/* update the ENV */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: ENV1_ATTACK, _DECAY, _SUSTAIN, _RELEASE, _ATCK_DEL, _DCAY_DEL */
		break;

	case ENV1_SUS_DCAY:
	case ENV1_VEL_SENS:
	case ENV1_MODE:

		(void)set_env(vp, ENV_1);						/* update the ENV */
		break;

	case ENV2_ATTACK:
	case ENV2_DECAY:
	case ENV2_SUSTAIN:
	case ENV2_RELEASE:
	case ENV2_ATCK_DEL:
	case ENV2_DCAY_DEL:

		uval = set_env(vp, ENV_2);						/* update the ENV */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: ENV2_ATTACK, _DECAY, _SUSTAIN, _RELEASE, _ATCK_DEL, _DCAY_DEL */
		break;

	case ENV2_SUS_DCAY:
	case ENV2_VEL_SENS:
	case ENV2_MODE:

		(void)set_env(vp, ENV_2);						/* update the ENV */
		break;

	case ENV3_ATTACK:
	case ENV3_DECAY:
	case ENV3_SUSTAIN:
	case ENV3_RELEASE:
	case ENV3_ATCK_DEL:
	case ENV3_DCAY_DEL:

		uval = set_env(vp, ENV_3);						/* update the ENV */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: ENV3_ATTACK, _DECAY, _SUSTAIN, _RELEASE, _ATCK_DEL, _DCAY_DEL */
		break;

	case ENV3_SUS_DCAY:
	case ENV3_VEL_SENS:
	case ENV3_MODE:

		(void)set_env(vp, ENV_3);						/* update the ENV */
		break;

	case ENV4_ATTACK:
	case ENV4_DECAY:
	case ENV4_SUSTAIN:
	case ENV4_RELEASE:
	case ENV4_ATCK_DEL:
	case ENV4_DCAY_DEL:

		uval = set_env(vp, ENV_4);						/* update the ENV */
		(void)do_mod_dst(vp, ipc_byte1, uval);			/* do mods: ENV4_ATTACK, _DECAY, _SUSTAIN, _RELEASE, _ATCK_DEL, _DCAY_DEL */
		break;

	case ENV4_SUS_DCAY:
	case ENV4_VEL_SENS:
	case ENV4_MODE:

		(void)set_env(vp, ENV_4);						/* update the ENV */
		break;
	}
}

/*
+++ =======================================================================
+++	user_mod() -- process the receipt of a user modulation
+++
+++	Prototype:
+++
+++		void user_mod(vb)
+++		BYTE vb;	voice number, VA = 0 or VB = 1
+++
+++	on entry:
+++
+++		ipc_byte1	item (0..2) and user MOD number (0..11)		(0iiimmmm)
+++		ipc_byte2	new value for item (..127)					(0vvvvvvv)
+++
+++	Calls:
+++
+++		mod_ins()
+++		mod_rmv()
+++ =======================================================================
*/

void user_mod(vb)
BYTE vb;
{
	struct voice	*vp;		/* VOICE pointer */
	struct mod		*mp;		/* MOD pointer */
	WORD			umnum;		/* user MOD number */
	WORD			mnum;		/* MOD table index */
	WORD			cvn;		/* control voltage (CV) number */
	WORD			val;		/* value table index */
	WORD			cval;		/* current value */

	umnum = ipc_byte1 & 0x0F;		/* extract user MOD number */

	if (umnum > (N_UMODS - 1))		/* check for limit on MOD number */
		return;						/* don't do MOD if it's wrong */

	mnum = umnum + N_FMODS;			/* create MOD table index */

	vp = &v[vb];					/* point at the VOICE structure */
	mp = &vp->mods[mnum];			/* point at the MOD structure */

	switch ((ipc_byte1 >> 4) & 0x0F) {		/* switch on item */

	case MOD_SRC: 					/* process source (SRC) */

		if  (ipc_byte2 GE N_SRCS)			/* set source if valid */
			mp->src = NO_SRC;
		else
			mp->src = ipc_byte2;

		mp->srp = &vp->outval[mp->src];		/* set SRC value pointer */

		/* check for active patch */

		if ((mp->src NE NO_SRC) AND
			(mp->dst NE NO_DST) AND
			(mp->mlt NE 0)) {				/* active patch */

			mod_ins(vp, mp);				/* insert patch on DST chain */
			
		} else {							/* inactive patch */

			mod_rmv(vp, mp);				/* remove patch from DST chain */
			mp->mlt = 0;					/* clear multiplier */
		}

		break;

	case MOD_DST: 					/* process destination (DST) */


		if (mp->dst NE NO_DST) {			/* disconnect old patch */

			val = dst_val[mp->dst];				/* get VT number */
			cval = vp->curval[val];				/* get current value */
			vp->outval[val] = cval;				/* reset outval */

			if (0x00FF NE (cvn = dst_cvn[mp->dst]))
				write_cv(vb, cvn, (cval >> 3));	/* send CV to DAC */
		}

		mod_rmv(vp, mp);					/* remove old patch from DST chain */

		if (ipc_byte2 GE N_DSTS)			/* set destination if valid */
			mp->dst	= UM_NONE;
		else
			mp->dst	= ipc_byte2;

		val = dst_val[mp->dst];				/* get VT number */

		mp->dsp = &vp->outval[val];			/* set DST value pointers */
		mp->cvp = &vp->curval[val];

		cvn = dst_cvn[mp->dst];				/* get CV number */

		if (0x00FF NE cvn) {				/* set cvtable pointer */

			if (vb EQ VA)
				mp->dac = &cvtable[dacmap[cvn]];		/* voice A CV */
			else
				mp->dac = &cvtable[dacmap[cvn + 32]];	/* voice B CV */

		} else
			mp->dac = &cvtable[BIT_BUCKET];				/* no CV */

		/* check for valid patch */

		if ((mp->src NE NO_SRC) AND
			(mp->dst NE NO_DST) AND
			(mp->mlt NE 0)) {			/* active patch */

			mod_ins(vp, mp);			/* insert patch on DST chain */

		} else {						/* inactive patch */

			mp->mlt = 0;				/* set multiplier to 0 */
		}

		break;

	case MOD_MLT: 						/* process multiplier (MLT) */

		switch (mp->dst) {				/* set multiplier */

		case UM_VCO1_PITCH:
		case UM_VCO2_PITCH:
		case UM_MM_FREQ:
		case UM_OB_FREQ:

			set_mlt(vp, mnum, (WORD)ipc_byte2, pml_tab);	/* pitches */

			break;

		default:

			set_mlt(vp, mnum, (WORD)ipc_byte2, mlt_tab);	/* others */
		}

		if (mp->mlt EQ 0) {

			mod_rmv(vp, mp);			/* remove patch from DST chain */

		} else if ((mp->src NE NO_SRC) AND (mp->dst NE NO_DST)) {

			mod_ins(vp, mp);			/* insert patch on DST chain */
		}

		break;
	}
}

/*
+++ =======================================================================
+++	perform_param() -- process the receipt of a performance parameter
+++
+++	Prototype:
+++
+++		perform_param(vn)
+++		BYTE vn;	vn is the voice number, VA = 0 or VB = 1
+++
+++	Calls:
+++
+++		do_mod_dst()
+++		do_mod_src()
+++		mod_vca()
+++		set_pan()
+++		set_transpose()
+++		write_cv()
+++ =======================================================================
*/

void perform_param(vn)
BYTE vn;
{
	struct voice	*vp;			/* VOICE pointer */
	INT				val;			/* scratch value */

	vp = &v[(WORD)vn];

	/* validate IPC input */

	if (((ipc_byte1 GT PP_MIDI_D) AND (ipc_byte1 LT PP_SUST_P)) OR
		(ipc_byte1 GE PP_NUM_PARAM))
		return;

	if (ipc_byte1 EQ PP_SUST_P) {				/* handle SUSTAIN footswitch */

		if (ipc_byte2 > 0x3F)					/* check against MIDI threshold */
			vp->pedal = M_GATE;					/* make it look like gate on */
		else
			vp->pedal = 0;						/* make it look like gate off */

	} else if (ipc_byte1 EQ PP_PORT_P) {		/* handle PORTAMENTO footswitch */

		if (ipc_byte2 > 0x3F)					/* check against MIDI threshold */
			vp->port = 1;						/* turn portamento on */
		else
			vp->port = 0;						/* turn portamento off */

	} else if (ipc_byte1 EQ PP_PAN) {			/* handle PAN pedal */

		vp->m_pan = (WORD)ipc_byte2;			/* setup MIDI pan */
		val = set_pan(vn);						/* adjust for part pan, etc. */
		val = do_mod_dst(vp, MIX_PAN, val);		/* do mods: MIX_PAN */
		write_cv(vn, HW_PAN, (val >> 3));		/* send it on its way */

	} else if (ipc_byte1 EQ PP_VOLUME) {		/* handle VOLUME pedal */

		vp->m_level = ipc_byte2 << 7;			/* setup MIDI level */
		val = vp->outval[VT_MIX_LEVEL];			/* get current master level */
		val = mod_vca(vp, val);					/* adjust for ENV4, etc. */
		write_cv(vn, HW_VCA, (val >> 3));		/* send it on its way */

	} else {									/* handle OTHER inputs */

		if (ipc_byte1 EQ PP_PITCHWHL)			/* see if it's the pitch wheel */
			val = val_tab[ipc_byte2];			/* if so, get signed value */
		else
			val = ipc_byte2 << 8;				/* otherwise, use positive values only */

		do_mod_src(vp, (WORD)ipc_byte1, val);	/* do mods: PP_????? */

		if (ipc_byte1 EQ PP_PITCHWHL) 			/* if it's the pitch wheel ... */
			set_transpose(vn);					/* ... setup VT_TRANSPOSE */
	}
}

/* The End */
