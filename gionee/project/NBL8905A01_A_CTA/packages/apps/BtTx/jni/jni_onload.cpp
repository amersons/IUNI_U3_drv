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


  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) 
  {
    goto bail;
  }
  if (register_gionee_factorytest_jni(env) < 0) 
  {
    goto bail;
  } 
  result = JNI_VERSION_1_4;
  bail:
    return result;
}
