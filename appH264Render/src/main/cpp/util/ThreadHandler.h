//
// Created by yuhanxun on 2018/6/19.
//

#ifndef SAMPLEJNI_THREADHANDLER_H
#define SAMPLEJNI_THREADHANDLER_H

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <jni.h>
#include "SyncQueue.hpp"
#include "Queue2.hpp"
#include <JniHelper.h>

#include "ByteData.hpp"
#include "YuvData.hpp"


class ThreadHandler {
public:
    class ICallback {
    public:
        virtual void onCallback(JNIEnv *jniEnv, jobject jobject, YuvData* data) = 0;
    };
public:
    ThreadHandler(JavaVM* javaVM,jobject jobject1);
    void start();
    void stop();
    //外部传入h264帧
    void putData(u_int8_t* p_data,uint32_t size);
    //让子类做解码操作
    virtual YuvData* handleData(ByteData* data) = 0;
    void setCallback(ICallback* callback);
public:
    bool isStop;
    SyncQueue<ByteData>* syncQueue;
//    Queue2<ByteData>* syncQueue;

    ICallback* callback;
    JavaVM *javaVM;
    jobject jobj;
    JNIEnv *jniEnv;
};


#endif //SAMPLEJNI_THREADHANDLER_H
