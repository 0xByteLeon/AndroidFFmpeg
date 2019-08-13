#include <jni.h>
#include <android/log.h>
#include <string>
#include "string-utils.h"
//http://www.voidcn.com/article/p-elqeblog-bps.html 各种格式字段内容解析
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#define TAG "FFMPEG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型

extern "C" JNIEXPORT jstring JNICALL
Java_com_leon_androidffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_leon_androidffmpeg_FFmpegPlayer_playMedia(
        JNIEnv *env,
        jclass type,
        jstring url_) {
    const char *url = env->GetStringUTFChars(url_, nullptr);
    env->ReleaseStringUTFChars(url_, url);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_leon_androidffmpeg_Test_testString(JNIEnv *env, jclass type, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, nullptr);

    env->ReleaseStringUTFChars(url_, url);
    return env->NewStringUTF("dfa");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_leon_androidffmpeg_FFmpegPlayer_printFFmpegInfo(JNIEnv *env, jclass type) {
    char info[4000] = {0};
    LOGD("Start");
//    const AVCodec *c_temp = av_codec_iterate(nullptr);
//    LOGD("Start 1");
//
//    while (c_temp != NULL) {
//        if (c_temp->decode != NULL) {
//            sprintf(info, "%s[Dec]", info);
//        } else {
//            sprintf(info, "%s[Enc]", info);
//        }
//        switch (c_temp->type) {
//            case AVMEDIA_TYPE_VIDEO:
//                sprintf(info, "%s[Video]", info);
//                break;
//            case AVMEDIA_TYPE_AUDIO:
//                sprintf(info, "%s[Audio]", info);
//                break;
//            default:
//                sprintf(info, "%s[Other]", info);
//                break;
//        }
//        sprintf(info, "%s[%10s]\n", info, c_temp->name);
//        c_temp = c_temp->next;
//    }
    __android_log_print(ANDROID_LOG_DEBUG, "myTag", "info:\n%d", avcodec_version());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_leon_androidffmpeg_FFmpegPlayer_getVideoInfo(JNIEnv *env, jclass type, jstring url_) {
    using namespace std;
    const char *url = env->GetStringUTFChars(url_, JNI_FALSE);
    LOGE("%s", url);
    std::string result = std::string("");

    int angle = -1;
//1.注册所有组件
//    av_register_all();
//封装格式上下文
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    //2.打开输入视频文件
    LOGE("准备打开文件");
    if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
        LOGE("%s", "无法打开输入视频文件");
        return env->NewStringUTF(result.append("无法打开输入视频文件").c_str());
    }
    LOGE("文件一打开");
//3.获取视频文件信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGE("%s", "无法获取视频信息");
        return env->NewStringUTF(result.append("无法获取视频信息").c_str());
    }
    LOGE("获取视频文件信息");
//获取视频流的索引位置
    int v_stream_idx = -1;
    int i = 0;
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            v_stream_idx = i;
            break;
        }
    }
    LOGE("获取视频流的索引位置");

//获取视频方向数据
    AVDictionaryEntry *tag = NULL;
    tag = av_dict_get(pFormatCtx->streams[v_stream_idx]->metadata, "rotate", tag, 0);
    if (tag != NULL) {
        angle = atoi(tag->value);
        LOGE("%d", angle);
    }
    LOGE("获取视频方向数据");
    if (v_stream_idx != -1) {
        //宽度
        LOGE("视频流index ： %d", v_stream_idx);
        result.append("\nfile name : ").append(pFormatCtx->url)
                .append("\nwidth : ").append(std::to_string(pFormatCtx->streams[v_stream_idx]->codecpar->width))
                .append("\nheight : ").append(std::to_string(pFormatCtx->streams[v_stream_idx]->codecpar->height))
                .append("\nprofile : ").append(
                        avcodec_profile_name(pFormatCtx->streams[v_stream_idx]->codecpar->codec_id,
                                             pFormatCtx->streams[v_stream_idx]->codecpar->profile)
                        ? avcodec_profile_name(pFormatCtx->streams[v_stream_idx]->codecpar->codec_id,
                                               pFormatCtx->streams[v_stream_idx]->codecpar->profile)
                        : "null"
                )
                .append("\nlevel : ").append(to_string(pFormatCtx->streams[v_stream_idx]->codecpar->level))
                .append("\nbits_per_coded_sample : ").append(
                        to_string(pFormatCtx->streams[v_stream_idx]->codecpar->bits_per_coded_sample))
                .append("\nformat : ").append(to_string(pFormatCtx->streams[v_stream_idx]->codecpar->format))
                .append("\nvideo encode int : ").append(to_string(pFormatCtx->streams[v_stream_idx]->codecpar->codec_id))
                .append("\nframe_size : ").append(
                        to_string(pFormatCtx->streams[v_stream_idx]->codecpar->frame_size))
                .append("\nbit rate : ").append(to_string(pFormatCtx->streams[v_stream_idx]->codecpar->bit_rate))
                .append("\navg_frame_rate num : ").append(
                        std::to_string(pFormatCtx->streams[v_stream_idx]->avg_frame_rate.num))
                .append("\navg_frame_rate den : ").append(
                        std::to_string(pFormatCtx->streams[v_stream_idx]->avg_frame_rate.den))
                .append("\nfps : ").append(std::to_string(av_q2d(pFormatCtx->streams[v_stream_idx]->r_frame_rate)))
                .append("\nformat name : ").append(pFormatCtx->iformat->name)
                .append("\nformat extensions : ").append(
                        pFormatCtx->iformat->extensions ? pFormatCtx->iformat->extensions : "null")
                .append("\nformat long_name : ").append(pFormatCtx->iformat->long_name);
        LOGE("AV_PIX_FMT_YUV420P format int : %d",AV_PIX_FMT_YUV420P);
        LOGE("H264 encode int : %d",AV_CODEC_ID_H264);
//分辨率
        LOGE("width : %d", pFormatCtx->streams[v_stream_idx]->codecpar->width);
        LOGE("height : %d", pFormatCtx->streams[v_stream_idx]->codecpar->height);
        LOGE("profile : %s", avcodec_profile_name(pFormatCtx->streams[v_stream_idx]->codecpar->codec_id,
                                                  pFormatCtx->streams[v_stream_idx]->codecpar->profile));
        LOGE("level : %d", pFormatCtx->streams[v_stream_idx]->codecpar->level);
        LOGE("bits_per_coded_sample : %d", pFormatCtx->streams[v_stream_idx]->codecpar->bits_per_coded_sample);
        LOGE("format : %d", pFormatCtx->streams[v_stream_idx]->codecpar->format);
        LOGE("frame_size : %d", pFormatCtx->streams[v_stream_idx]->codecpar->frame_size);
        LOGE("format name : %s", pFormatCtx->iformat->name);
        LOGE("format extensions : %s", pFormatCtx->iformat->extensions);
        LOGE("format long_name : %s", pFormatCtx->iformat->long_name);
        LOGE("bit_rate : %"
                     PRId64, pFormatCtx->streams[v_stream_idx]->codecpar->bit_rate);
        LOGD("%s", result.c_str());
    } else {
        result.append("获取视频流失败！");
    }

    env->ReleaseStringUTFChars(url_, url);
    avformat_free_context(pFormatCtx);
    return env->NewStringUTF(result.c_str());
}

//extern "C"
//JNIEXPORT jint JNICALL
//Java_com_leon_androidffmpeg_FFmpegPlayer_playMedia__Ljava_lang_String_2Landroid_view_Surface_2(JNIEnv *env, jclass type,
//                                                                                               jstring url_,
//                                                                                               jobject surface) {
//    const char *url = env->GetStringUTFChars(url_, 0);
//
//    int i;
//    AVCodec *vCodec;
//    char input_str[500]={0};
//    //读取输入的视频频文件地址
//    sprintf(input_str, "%s", env->GetStringUTFChars(url_, NULL));
//    //初始化
//    av_register_all();
//    //分配一个AVFormatContext结构
//    AVFormatContext *pFormatCtx = avformat_alloc_context();
//    //打开文件
//    if(avformat_open_input(&pFormatCtx,input_str,NULL,NULL)!=0){
//        LOGD("Couldn't open input stream.\n");
//        return -1;
//    }
//    //查找文件的流信息
//    if(avformat_find_stream_info(pFormatCtx,NULL)<0){
//        LOGD("Couldn't find stream information.\n");
//        return -1;
//    }
//    //在流信息中找到视频流
//    int videoindex = -1;
//    for(i=0; i<pFormatCtx->nb_streams; i++) {
//        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
//            videoindex = i;
//            break;
//        }
//    }
//    if(videoindex == -1){
//        LOGD("Couldn't find a video stream.\n");
//        return -1;
//    }
//    //获取相应视频流的解码器
//    AVCodecContext *vCodecCtx=pFormatCtx->streams[videoindex]->codec;
//    vCodec = avcodec_find_decoder(vCodecCtx->codec_id);
//    assert(vCodec != NULL);
//    //打开解码器
//    if(avcodec_open2(vCodecCtx, vCodec,NULL)<0){
//        LOGD("Couldn't open codec.\n");
//        return -1;
//    }
//    //获取界面传下来的surface
//    nativeWindow = ANativeWindow_fromSurface(env, surface);
//    if (0 == nativeWindow){
//        LOGD("Couldn't get native window from surface.\n");
//        return -1;
//    }
//    int width = vCodecCtx->width;
//    int height = vCodecCtx->height;
//    //分配一个帧指针，指向解码后的原始帧
//    AVFrame *vFrame = av_frame_alloc();
//    AVPacket * vPacket = (AVPacket *)av_malloc(sizeof(AVPacket));
//    AVFrame *pFrameRGBA = av_frame_alloc();
//    //绑定输出buffer
//    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, width, height, 1);
//    uint8_t *v_out_buffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));
//    av_image_fill_arrays(pFrameRGBA->data, pFrameRGBA->linesize, v_out_buffer, AV_PIX_FMT_RGBA, width, height, 1);
//    img_convert_ctx = sws_getContext(width, height, vCodecCtx->pix_fmt,
//                                     width, height, AV_PIX_FMT_RGBA, SWS_BICUBIC, NULL, NULL, NULL);
//    if (0 > ANativeWindow_setBuffersGeometry(nativeWindow,width,height,WINDOW_FORMAT_RGBA_8888)){
//        LOGD("Couldn't set buffers geometry.\n");
//        ANativeWindow_release(nativeWindow);
//        return -1;
//    }
//    //读取帧
//    while(av_read_frame(pFormatCtx, vPacket)>=0){
//        if(vPacket->stream_index==videoindex){
//            //视频解码
//            int ret = avcodec_send_packet(vCodecCtx, vPacket);
//            if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
//                return -1;
//            ret = avcodec_receive_frame(vCodecCtx, vFrame);
//            if (ret < 0 && ret != AVERROR_EOF)
//                return -1;
//            //转化格式
//            sws_scale(img_convert_ctx, (const uint8_t* const*)vFrame->data, vFrame->linesize, 0, vCodecCtx->height,
//                      pFrameRGBA->data, pFrameRGBA->linesize);
//            if (ANativeWindow_lock(nativeWindow, &windowBuffer, NULL) < 0) {
//                LOGD("cannot lock window");
//            } else {
//                //将图像绘制到界面上，注意这里pFrameRGBA一行的像素和windowBuffer一行的像素长度可能不一致
//                //需要转换好，否则可能花屏
//                uint8_t *dst = (uint8_t *) windowBuffer.bits;
//                for (int h = 0; h < height; h++)
//                {
//                    memcpy(dst + h * windowBuffer.stride * 4,
//                           v_out_buffer + h * pFrameRGBA->linesize[0],
//                           pFrameRGBA->linesize[0]);
//                }
//                ANativeWindow_unlockAndPost(nativeWindow);
//
//            }
//        }
//        av_packet_unref(vPacket);
//    }
//    //释放内存
//    sws_freeContext(img_convert_ctx);
//    av_free(vPacket);
//    av_free(pFrameRGBA);
//    avcodec_close(vCodecCtx);
//    avformat_close_input(&pFormatCtx);
//
//    env->ReleaseStringUTFChars(url_, url);
//    return 0;
//}