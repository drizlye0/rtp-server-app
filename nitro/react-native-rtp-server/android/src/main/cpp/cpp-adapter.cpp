#include <jni.h>
#include "rtpserverOnLoad.hpp"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void*) {
  return margelo::nitro::rtpserver::initialize(vm);
}
