//
// Created by Leon on 2019/8/13.
//

#include <jni.h>
#include <cstring>

jstring str2jstring(JNIEnv *env, const char *pat) {
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("UTF-8");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

//jstring chartoJstring(JNIEnv *env, const char *pat) {
//    jclass strClass = (env)->FindClass("java/lang/String");
//    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
//    jbyteArray bytes = (*env)->NewByteArray(env, (jsize) strlen(pat));
//    (*env)->SetByteArrayRegion(env, bytes, 0, (jsize) strlen(pat), (jbyte *) pat);
//    jstring encoding = (*env)->NewStringUTF(env, "utf-8");
//    return (jstring) (*env)->NewObject(env, strClass, ctorID, bytes, encoding);
//}

