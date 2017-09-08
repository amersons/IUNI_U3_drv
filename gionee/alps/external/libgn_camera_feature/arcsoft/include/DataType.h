#ifndef __CAMCONSTANTTABLEH__
#define __CAMCONSTANTTABLEH__

const int ARCCAMERA_MSG_ERROR = 0x0001;            // notifyCallback
const int ARCCAMERA_MSG_SHUTTER = 0x0002;          // notifyCallback
const int ARCCAMERA_MSG_FOCUS = 0x0004;            // notifyCallback
const int ARCCAMERA_MSG_ZOOM = 0x0008;             // notifyCallback
const int ARCCAMERA_MSG_PREVIEW_FRAME = 0x0010;    // dataCallback
const int ARCCAMERA_MSG_VIDEO_FRAME = 0x0020;      // data_timestamp_callback
const int ARCCAMERA_MSG_POSTVIEW_FRAME = 0x0040;   // dataCallback
const int ARCCAMERA_MSG_RAW_IMAGE = 0x0080;        // dataCallback
const int ARCCAMERA_MSG_COMPRESSED_IMAGE = 0x0100; // dataCallback
const int ARCCAMERA_MSG_RAW_IMAGE_NOTIFY = 0x0200; // dataCallback
const int ARCCAMERA_MSG_PREVIEW_METADATA = 0x0400; // dataCallback
const int ARCCAMERA_MSG_ALL_MSGS = 0xFFFF;

const int	COMPRESSED_BASE			= 0x00100000;
const int	COMPRESSED_JPEG			= COMPRESSED_BASE + 1;
const int	COMPRESSED_PNG			= COMPRESSED_BASE + 2;


#endif	//end of __CAMCONSTANTTABLEH__