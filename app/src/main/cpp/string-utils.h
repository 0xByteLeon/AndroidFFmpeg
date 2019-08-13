//
// Created by Leon on 2019/8/13.
//

#ifndef ANDROIDFFMPEG_STRING_UTILS_H
#define ANDROIDFFMPEG_STRING_UTILS_H

#include "../../../../../../../Env/Android/Sdk/ndk-bundle/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include/jni.h"

jstring str2jstring(JNIEnv *env, const char *pat);
#endif //ANDROIDFFMPEG_STRING_UTILS_H
