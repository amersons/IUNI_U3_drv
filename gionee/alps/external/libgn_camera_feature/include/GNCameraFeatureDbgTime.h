/*************************************************************************************
 * 
 * Description:
 *      Defines API to debug timer.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2014-02-28
 *
 *************************************************************************************/

#ifndef GN_CAMERA_FEATURE_DGB_TIME_H
#define GN_CAMERA_FEATURE_DGB_TIME_H

#include <time.h>

#include "GNCameraFeatureDefs.h"

namespace android {         

class GNCameraFeatureDbgTime {

public:
	GNCameraFeatureDbgTime() 
		: mStartMS(getMS())
		, mEndMS(getMS())
	{
	}

	inline int32 getMS() {
		struct timeval tv;
		gettimeofday(&tv, NULL); 

		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	}

	inline void print(const char* title = "") {
		mEndMS = getMS();
		PRINTD("[%s] : spendTime = %ld ms", title, (mEndMS - mStartMS));
	}
private:
	int32 mStartMS;
	int32 mEndMS;
};

};


#endif //GN_CAMERA_FEATURE_DGB_TIME_H
