/*----------------------------------------------------------------------------------------------
*
* This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary and
* confidential information.
*
* The information and code contained in this file is only for authorized ArcSoft employees
* to design, create, modify, or review.
*
* DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it.
*
* If you have received this file in error, please immediately notify ArcSoft and
* permanently delete the original and any copy of any file and any printout thereof.
*
*-------------------------------------------------------------------------------------------------*/
/*
* Asd.h
*
* Reference:
*
* Description:
*
* Create by yl6181 2013-11-04
*
*/

#ifndef __ASDH__
#define __ASDH__

#include <pthread.h>
#include <semaphore.h>

#include "FaceTracking.h"
#include "arcsoft_asd.h"

#define STATIC_MEM 10*1024*1024

typedef void (*PROCESS_CBFUN)(int result, void* pExt);

class ProcessCallback
{
public:
	virtual ~ProcessCallback(){};
	virtual void onCallback(int result) = 0;
};

class Asd
{
public:
	Asd();
	~Asd();

	int		init(int iWidth,int iHeight);
	void	uninit();
	int		process(LPASVLOFFSCREEN pData,int orientation);
	void 	setProcessCallback(PROCESS_CBFUN pCallbackFunc, void* pArg);
	void 	setProcessCallback(ProcessCallback* pCallbackInstant);
	void	setModeProfile(unsigned long modeProfile);
	
private:
	void allocAsvlOffScreen(LPASVLOFFSCREEN pFrame);
	void freeAsvlOffScreen(LPASVLOFFSCREEN pFrame);

private:
	MHandle				mhMemMgr;
	MVoid*				mpMem;
	MHandle				mhAsd;

	CFaceTracking		mFaceTracking;
	int					miPreivewWidth;
	int					miPreviewHeight;
	ASVLOFFSCREEN		mRenderFrame;
	PROCESS_CBFUN		mPCallBackFunc;
	void*				mpCallBackArg;
	ProcessCallback*	mpCallbackInstant;
	unsigned long		mModeProfile;		//each bit represent one kind of modes
	
	int					mDeviceOrientation;
	int					mSceneType;
	
	friend void* 		processThreadFunc(void* arg);
	pthread_t			mhThread;
	pthread_mutex_t		mMutex;
	bool				mbFinished;
	bool				mbThreadCreated;
	sem_t				mSem;
};

#endif //endof __ASDH__