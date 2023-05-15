#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "include//curl.h"
#include <string>
using namespace std ;

#include <android/log.h>



#define TAG "CURLLIB"
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO, TAG, FORMAT, ##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR, TAG, FORMAT, ##__VA_ARGS__);

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    ((std::string*)userdata)->append(ptr, nmemb);
    return nmemb;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_sherlockshi_curldemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_sherlockshi_curldemo_MainActivity_curlHttpGet(
        JNIEnv* env,
        jobject /* this */, jstring url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    std::string response_data;
    if (curl)
    {
        jboolean  b = JNI_TRUE ;
        const char *nativeString = (const char *)env->GetStringUTFChars(url, &b);
        curl_easy_setopt(curl, CURLOPT_URL, nativeString);

        // no certificate, not verify server certificate
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }
        else
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("response code %ld \n", response_code);
            printf("response data : \n ");
            printf("%s",response_data.c_str());
            LOGI("%ld-%s",response_code,response_data.c_str())
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return  env->NewStringUTF(response_data.c_str());
}
