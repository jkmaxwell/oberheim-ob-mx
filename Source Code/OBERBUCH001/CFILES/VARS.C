/*
+++ ============================================================================
+++	File:		VARS.C
+++	Purpose:	OB-MX variable definitions and register variable clear code
+++	Original:		1993-06-29	D.N. Lynx Crowe
+++	Revision:	21	1993-12-15	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		varz()				clear assembler register and RAM variables
+++
+++		aoff				composite tuning offset work area A
+++		boff				composite tuning offset work area B
+++		ctltable[]			control register table
+++		cur_cv				current CV for update
+++		cur_ctl				current controller for update
+++		cvtable[]			control voltage table
+++		first_var			beginning of VARS.C variables
+++		ipc_addr			voice or channel
+++		ipc_fifo[]		 	IPC FIFO buffer area
+++		ipc_stat			status byte type
+++		ipc_state			next ipc state processor
+++		parmap[]			preset parameter to DAC map
+++		tpa					pointer to next word in A tuning table
+++		tpb					pointer to next word in B tuning table
+++		v[2]				voice data structures
+++		vchan1				channel, voice A
+++		vchan2				channel, voice B
+++		vid1				voice ID, voice A
+++		vid2				voice ID, voice B
+++		vpart1				part, voice A
+++		vpart2				part, voice B
+++		wca					tuning table A word counter
+++		wcb					tuning table B word counter
+++
+++	WARNING:  The variables must appear in VARS.H as externals.
+++ ============================================================================
*/

#include "voice.h"

/*+ =================== RAM variables we define here ====================== */

WORD			first_var;			/*+ beginning of VARS.C variables */

WORD			vid1;				/*+ voice ID, voice A */
WORD			vid2;				/*+ voice ID, voice B */

WORD			vchan1;				/*+ channel, voice A */
WORD			vchan2;				/*+ channel, voice B */

WORD			vpart1;				/*+ part, voice A */
WORD			vpart2;				/*+ part, voice B */

WORD			ipc_stat;			/*+ status byte type */
WORD			ipc_addr;			/*+ voice or channel */

WORD			cur_cv;				/*+ current CV for update */
WORD			cur_ctl;			/*+ current controller for update */

WORD			wca;				/*+ tuning table A word counter */
WORD			wcb;				/*+ tuning table B word counter */

WORD			*tpa;				/*+ pointer to next word in A tuning table */
WORD			*tpb;				/*+ pointer to next word in B tuning table */

WORD			aoff;				/*+ composite tuning offset work area A */
WORD			boff;				/*+ composite tuning offset work area B */

void			(*ipc_state)();		/*+ next ipc state processor */

BYTE			parmap[MAPLEN];		/*+ preset parameter to DAC map */

WORD			cvtable[64];		/*+ control voltage table */

BYTE			ctltable[16];		/*+ control register table */

struct voice	v[2];				/*+ voice data structures */

BYTE			ipc_fifo[0x800];	/*+ IPC FIFO buffer area */

/*+ ======================== external functions ============================ */

extern void	init_regs();			/*+ clear register variables */
extern void	init_adata();			/*+ clear RAM area */

/*
+++ ============================================================================
+++	varz() -- clear assembler register and RAM variables
+++
+++	Prototype:
+++
+++		void varz()
+++
+++
+++	Calls:
+++
+++		init_adata()
+++		init_regs()
+++
+++	The main reason for this function was so that the ICE-196 would know where
+++	to find the variables...
+++
+++	We now clear the assembler register and RAM variables here.
+++ ============================================================================
*/

void varz()
{
	init_regs();			/* clear register variables */
	init_adata();			/* clear RAM area */

	first_var = 0x1234;		/* make the ICE box happy... */
}

/* The End */
