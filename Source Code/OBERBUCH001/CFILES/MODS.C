/*
+++ ============================================================================
+++	File:		MODS.C
+++	Purpose:	OB-MX MOD structure DST list fucntions
+++	Original:		1993-07-09	D.N. Lynx Crowe
+++	Revision:	12	1993-12-06	D.N. Lynx Crowe
+++
+++	Contents:
+++
+++		mod_ins()	insert a MOD structure in the DST list
+++		mod_rmv()	remove a MOD structure from the DST list
+++ ============================================================================
*/

#include "voice.h"
#include "vars.h"

/*
+++ ============================================================================
+++	mod_ins() -- insert a MOD structure in the DST list
+++
+++	Prototype:
+++
+++		void mod_ins(vp, mp)
+++		struct voice *vp;	VOICE pointer
+++		struct mod *mp;		MOD pointer
+++ ============================================================================
*/

void mod_ins(vp, mp)
struct voice *vp;
struct mod *mp;
{
	if (mp->dst EQ NO_DST)				/* if there's no DST, quit */
		return;

	/* setup the destination type in mp->flg */

	mp->flg = (mp->flg & DT_MASK) | (WORD)dst_typ[mp->dst];

	if (mp->mlt EQ 0)					/* if the multiplier is 0, quit */
		return;

	if (mp->flg & MOD_F_NXD)			/* if it's already on the list, quit */
		return;

	mp->nxd = vp->dstptr[mp->dst];		/* update next DST pointer */
	vp->dstptr[mp->dst] = mp;			/* update DST list head */
	mp->flg |= MOD_F_NXD;				/* indicate MOD is on the list */
}

/*
+++ ============================================================================
+++	mod_rmv() -- remove a MOD structure from the DST list
+++
+++	Prototype:
+++
+++		void mod_rmv(vp, mp)
+++		struct voice *vp;	VOICE pointer
+++		struct mod *mp;		MOD pointer
+++ ============================================================================
*/

void mod_rmv(vp, mp)
struct voice *vp;
struct mod *mp;
{
	struct mod *cp;							/* current pointer */
	struct mod *pp;							/* predecessor pointer */

	if (mp->dst EQ NO_DST)					/* if there's no DST, quit */
		return;

	if ((mp->flg & MOD_F_NXD) EQ 0)			/* if it's not on the list, quit */
		return;

	mp->flg = 0;							/* indicate it's not on the list */

	/* if the list is empty, quit */

	if ((struct mod *)0 EQ (cp = vp->dstptr[mp->dst]))
		return;

	if (cp EQ mp) {							/* see if it's first on the list */

		vp->dstptr[mp->dst] = cp->nxd;		/* update DST list head */
		cp->nxd = (struct mod *)0;			/* clear mod DST pointer */
		return;
	}

	pp = cp;								/* make pp point at cp */

	do {									/* follow the DST list chain */

		if (cp EQ mp) {						/* see if we've found the entry */

			pp->nxd = cp->nxd;				/* update predecessor pointer */
			cp->nxd = (struct mod *)0;		/* clear mod DST pointer */
			return;
		}

		pp = cp;							/* indicate predecessor */

	} while ((struct mod *)0 NE (cp = pp->nxd));	/* follow nxd */
}

/* The End */
