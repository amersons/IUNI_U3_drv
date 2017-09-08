#ifndef __FACETRACKINGH__
#define __FACETRACKINGH__

#include <malloc.h>

#include "ammem.h"
#include "amcomdef.h"
#include "asvloffscreen.h"
#include "arcsoft_face_tracking.h"

#define MAX_FACE_TRACK_NUMBER	30

class CFaceTracking
{
private:
	MVoid*			mpMemBuff;
	MHandle			mhMemMgr;
	AFT_ENGINE		mfaceEngine;
	ASVLOFFSCREEN	mimageData;
	AFT_FACERES		mfaceRes;

	int mnW;
	int mnH;

public:
	CFaceTracking();
	~CFaceTracking();

	int init(int w, int h);
	void uninit();

	int detectOffscreen(LPASVLOFFSCREEN pFrame, LPAFT_FACERES& pFaceRes);
};

#endif