/*************************************************************************************
 * 
 * Description:
 * 	Defines listerner.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#ifndef GN_CAMERA_FEATURE_LISTENER_H
#define GN_CAMERA_FEATURE_LISTENER_H

#include <utils/String8.h>
#include <utils/Errors.h>

#include "GNCameraFeatureDefs.h"

namespace android {         

class GNCameraFeatureListener {

public:
	/*************************************************************************************
	 * @brief:
	 * 	callback message to HAL;
	 *
     	 * @param msgType
	 * 	Specify camera type in @GNCameraMsgType.
	 *
	 * @param ext1/ext2
	 *	Reserved argument.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/

	virtual void notify(GNCameraMsgType_t msgType, int32 ext1, int32 ext2, int32 ext3 = 0, void* ext4 = 0) = 0;

	virtual ~GNCameraFeatureListener() {};
};
};

#endif /* GN_CAMERA_FEATURE_LISTENER_H */
