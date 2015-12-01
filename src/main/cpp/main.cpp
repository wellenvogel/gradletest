//
// Created by andreas on 01.12.15.
//

#include "main.h"
#include "stdio.h"
#include <jni.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
#define MAXCP 64000
int main(int argc, char ** argv)
{
    cout << "CPPMAIN: Hello!" << endl;

       JavaVMOption jvmopt[1];
       char buffer[MAXCP];
       snprintf(buffer,MAXCP,"-Djava.class.path=%s",getenv("CLASSPATH"));
       jvmopt[0].optionString=buffer;

       JavaVMInitArgs vmArgs;
       vmArgs.version = JNI_VERSION_1_2;
       vmArgs.nOptions = 1;
       vmArgs.options = jvmopt;
       vmArgs.ignoreUnrecognized = JNI_TRUE;

       // Create the JVM
       JavaVM *javaVM;
       JNIEnv *jniEnv;
       long flag = JNI_CreateJavaVM(&javaVM, (void**)
          &jniEnv, &vmArgs);
       if (flag == JNI_ERR) {
          cout << "Error creating VM. Exiting...\n";
          return 1;
       }

       jclass jcls = jniEnv->FindClass("de/wellenvogel/gtest/main/GTestMain");
       if (jcls == NULL) {
          jniEnv->ExceptionDescribe();
          javaVM->DestroyJavaVM();
          return 1;
       }
       if (jcls != NULL) {
          jmethodID methodId = jniEnv->GetStaticMethodID(jcls,
             "main", "([Ljava/lang/String;)V");
          if (methodId != NULL) {
            jclass stringCls = jniEnv->FindClass("Ljava/lang/String;");
            if (stringCls == NULL) {
              cout << "unable to find String class"<<endl;
              return 1;
            }

            jobject args = jniEnv->NewObjectArray(0, stringCls, NULL);
             jniEnv->CallStaticVoidMethod(jcls, methodId, args);
             if (jniEnv->ExceptionCheck()) {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
             }
          }
          else{
            cout <<"unable to find main "<<endl;
          }
       }

       javaVM->DestroyJavaVM();
       return 0;
    }

