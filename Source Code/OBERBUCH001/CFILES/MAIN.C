/*
+++ ==========================================================================
+++	File:		MAIN.C
+++	Purpose:	OB-MX voice card root module
+++	Original:		1993-05-25	D.N. Lynx Crowe
+++	Revision:	45	1994-05-19	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		main()			this is where it all begins ...
+++		init_lfos()		initialize LFO data structures
+++		init_misc()		initialize miscellaneous voice variables
+++		init_mods()		initialize MOD data structures
+++		init_tts()		initialize tuning tables
+++ ==========================================================================
*/

#include "voice.h"
#include "vars.h"

/*+ ========================= external function references ================ */

extern void		background();	/*+ background processing - main scan loop */
extern WORD		get_id();		/*+ get board ID */
extern void		hdw_go();		/*+ enable interrupts */
extern void		init_envs();	/*+ initialize ENV data structures */
extern void		init_hdw();		/*+ initialize hardware */
extern void		init_ipc();		/*+ initialize IPC parser */
extern WORD		set_lfo();		/*+ set LFO parameters */
extern WORD		set_pan();		/*+ set PAN */
extern void		srand();		/*+ seed the random number generator */
extern void		tuner();		/*+ tune the instrument */

/*
+++ =======================================================================
+++	main() -- this is where it all begins ...
+++
+++
+++	Prototype:
+++
+++		void main()
+++
+++
+++	Calls:
+++
+++		background()
+++		get_id()
+++		hdw_go()
+++		init_envs()
+++		init_hdw()
+++		init_ipc()
+++		srand()
+++		tuner()
+++		varz()
+++
+++	WARNING:  varz() MUST be the first thing to happen.  Don't put any
+++	executable code in front of the call to varz().  Things will stop
+++	working and blow up in strange ways if you do...
+++
+++	(HINT:  varz() clears assembler RAM and REGISTER variables.)
+++
+++	NOTE:  background() never returns.
+++ =======================================================================
*/

void main()
{
	WORD i;							/* general purpose index */
	WORD j;							/* general purpose index */
	WORD k;							/* general purpose index */
	WORD cvn;						/* control voltage number */
	WORD uval;						/* unmodulated value */
	INT pv;							/* pan value */
	struct voice *vp;				/* VOICE pointer */
	struct mod *mp;					/* MOD pointer */

	varz();							/* FIRST clear our variables */

	vid1 = get_id();				/* setup the voice IDs */
	vid2 = vid1 + 1;

	for (i = 0; i < 64; i++)		/* clear the DAC CV table to 0 */
		cvtable[i] = 0;

	init_hdw();						/* initialize hardware */
	init_ipc();						/* init IPC parser */

	/* initialize misc. voice variables */

	for (i = 0; i < 2; i++) {			/* update each voice */

		vp = &v[i];						/* point at the voice */

		vp->legato		= 1;			/* legato = OFF */
		vp->port		= 1;			/* portamento = ENABLED */

		vp->pwsens		= 12;			/* pitch wheel sensitivity = 12 semitones */

		vp->m_level		= 0x3F80;		/* MIDI level = full on */
		vp->p_level		= 0x3F80;		/* part level = full on */

		vp->m_pan		= 0x0040;		/* MIDI pan = centered */
		vp->p_pan		= 0x0040;		/* part pan = centered */
		vp->v_pan		= 0x0040;		/* voice pan = centered */
		pv = set_pan(i);				/* setup pan CV value */
		vp->curval[VT_MIX_PAN] = pv;	/* update pan in curval[] */
		vp->outval[VT_MIX_PAN] = pv;	/* update pan in outval[] */
		write_cv(i, HW_PAN, (pv >> 3));	/* output pan CV */
	}

	/* initialize lfos */

	for (i = 0; i < 2; i++) {					/* for each VOICE ... */

		vp = &v[i];								/* point at the VOICE */

		/* LFO_1 */

		ipc_byte1 = LFO1_DELAY;						/* initilaize Delay */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_1);
		vp->curval[VT_LFO1_DELAY] = uval;
		vp->outval[VT_LFO1_DELAY] = uval;

		ipc_byte1 = LFO1_RATE;						/* initilaize Rate */
		ipc_byte2 = INIT_LFO_RATE;
		uval = set_lfo(vp, LFO_1);
		vp->curval[VT_LFO1_RATE] = uval;
		vp->outval[VT_LFO1_RATE] = uval;

		ipc_byte1 = LFO1_OFFSET;					/* initilaize Offset */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_1);
		vp->curval[VT_LFO1_OFFSET] = uval;
		vp->outval[VT_LFO1_OFFSET] = uval;

		ipc_byte1 = LFO1_S_H;						/* initilaize S/H */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_1);
		vp->curval[VT_LFO1_S_H] = uval;
		vp->outval[VT_LFO1_S_H] = uval;

		ipc_byte1 = LFO1_SHAPE;						/* initilaize Waveshape */
		ipc_byte2 = INIT_LFO_SHAPE;
		(void)set_lfo(vp, LFO_1);

		/* LFO_2 */

		ipc_byte1 = LFO2_DELAY;						/* initilaize Delay */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_2);
		vp->curval[VT_LFO2_DELAY] = uval;
		vp->outval[VT_LFO2_DELAY] = uval;

		ipc_byte1 = LFO2_RATE;						/* initilaize Rate */
		ipc_byte2 = INIT_LFO_RATE;
		uval = set_lfo(vp, LFO_2);
		vp->curval[VT_LFO2_RATE] = uval;
		vp->outval[VT_LFO2_RATE] = uval;

		ipc_byte1 = LFO2_OFFSET;					/* initilaize Offset */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_2);
		vp->curval[VT_LFO2_OFFSET] = uval;
		vp->outval[VT_LFO2_OFFSET] = uval;

		ipc_byte1 = LFO2_S_H;						/* initilaize S/H */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_2);
		vp->curval[VT_LFO2_S_H] = uval;
		vp->outval[VT_LFO2_S_H] = uval;

		ipc_byte1 = LFO2_SHAPE;						/* initilaize Waveshape */
		ipc_byte2 = INIT_LFO_SHAPE;
		(void)set_lfo(vp, LFO_2);

		/* LFO_3 */

		ipc_byte1 = LFO3_DELAY;						/* initilaize Delay */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_3);
		vp->curval[VT_LFO3_DELAY] = uval;
		vp->outval[VT_LFO3_DELAY] = uval;

		ipc_byte1 = LFO3_RATE;						/* initilaize Rate */
		ipc_byte2 = INIT_LFO_RATE;
		uval = set_lfo(vp, LFO_3);
		vp->curval[VT_LFO3_RATE] = uval;
		vp->outval[VT_LFO3_RATE] = uval;

		ipc_byte1 = LFO3_OFFSET;					/* initilaize Offset */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_3);
		vp->curval[VT_LFO3_OFFSET] = uval;
		vp->outval[VT_LFO3_OFFSET] = uval;

		ipc_byte1 = LFO3_S_H;						/* initilaize S/H */
		ipc_byte2 = 0;
		uval = set_lfo(vp, LFO_3);
		vp->curval[VT_LFO3_S_H] = uval;
		vp->outval[VT_LFO3_S_H] = uval;

		ipc_byte1 = LFO3_SHAPE;						/* initilaize Waveshape */
		ipc_byte2 = INIT_LFO_SHAPE;
		(void)set_lfo(vp, LFO_3);
	}

	init_envs();					/* initialize envelopes */

	/* initialize modulations */

	for (i = 0; i < 2; i++) {					/* for each VOICE ... */

		vp = &v[i];								/* point at the VOICE */

		for (j = 0; j < N_DSTS; j++)			/* clear DST pointers  */
			vp->dstptr[j] = (struct mod *)0;

		for (j = 0; j < N_FMODS; j++) {			/* for each fixed MOD ... */

			mp = &vp->mods[j];					/* point at the fixed MOD */

			mp->flg = 0;						/* clear flag */

			mp->src = fixed_mods[j].src;		/* copy default from fixed_mods[] */
			mp->dst = fixed_mods[j].dst;
			mp->mlt = fixed_mods[j].mlt;

			mp->nxd = (struct mod *)0;			/* clear next DST pointer */

			mp->srp = &vp->outval[mp->src];		/* set value pointers */

			mp->dsp = &vp->outval[dst_val[mp->dst]];
			mp->cvp = &vp->curval[dst_val[mp->dst]];

			cvn = dst_cvn[mp->dst];				/* get CV number */

			if (0x00FF NE cvn) {				/* set cvtable pointer */

				if (vp EQ &v[0])
					mp->dac = &cvtable[dacmap[cvn]];		/* voice A */
				else
					mp->dac = &cvtable[dacmap[cvn + 32]];	/* voice B */

			} else {

				mp->dac = &cvtable[BIT_BUCKET];				/* no DAC output */
			}

			/* setup the destination type in mp->flg */

			mp->flg = (mp->flg & MOD_F_NXD) | (WORD)dst_typ[mp->dst];
		}

		for (j = N_FMODS; j < N_MODS; j++) {	/* for each user MOD ... */

			mp = &vp->mods[j];					/* point at the user MOD */

			mp->flg = 0;						/* setup a null patch */
			mp->src = PP_NONE;
			mp->dst = UM_NONE;
			mp->mlt = 0;

			mp->nxd = (struct mod *)0;			/* clear next DST pointer */

			mp->srp = &vp->outval[VT_NONE];		/* set value pointers */
			mp->dsp = &vp->outval[VT_NONE];

			mp->cvp = &vp->curval[VT_NONE];

			mp->dac = &cvtable[BIT_BUCKET];		/* set cvtable pointer */
		}
	}

	/* initialize tuning tables */

	for (j = 0; j < 128; j++) {

		k = j << 8;

		v[VA].tunetab[j] = k;
		v[VB].tunetab[j] = k;
	}

	srand(TIMER1);					/* seed the random number generator */

	hdw_go();						/* enable interrupts */

	/* NOTE:  background() never returns */

	background();					/* here's where it all happens ... */
}

/* The End */
