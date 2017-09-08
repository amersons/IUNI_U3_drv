#define LOG_TAG "CITJni"

#include "JNIHelp.h"
#include "jni.h"
#include "utils/Log.h"


namespace android {
  int register_gionee_factorytest_jni(JNIEnv* env);
};

using namespace android;


jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
  JNIEnv* env = NULL;
  jint result = -1;

  ALOGI("Enter JNI_OnLoad");

  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) 
  {
    ALOGE("GetEnv failed!");
    goto bail;
  }
  ALOG_ASSERT(env, "Could not retrieve the env!");
  if (register_gionee_factorytest_jni(env) < 0) 
  {
    ALOGE("ERROR: native registration failed\n");
    goto bail;
  } 
  result = JNI_VERSION_1_4;
  bail:
    return result;
}
