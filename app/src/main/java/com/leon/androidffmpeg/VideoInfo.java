package com.leon.androidffmpeg;

/**
 * @time:2019/8/8 16:50
 * @author:Leon
 * @description:
 */
public class VideoInfo {
//    KEY_MIME 格式类型
//    KEY_MAX_INPUT_SIZE 输出缓冲区的最大字节数
//    KEY_BIT_RATE 比特率
//    KEY_WIDTH    视频宽度
//    KEY_HEIGHT   视频高度
//    KEY_DURATION  内容持续时间（以微妙为单位）
//    KEY_CORLOR_FORMAT   视频内容颜色空间
//    KEY_FRAME_RATE   视频帧率
//    KEY_I_FRAME_INTERVAL   关键之间的时间间隔
//    KEY_ROTATION  视频旋转顺时针角度
//    KEY_BITRATE     码率/比特率(画质和文件体积)
//    KEY_BITRATE_MODE    比特率模式
//    KEY_CHANNEL_COUNT   通道数
//    KEY_SAMPLE_RATE   采样率
//    KEY_DURATION   内容持续时间（以微妙为单位

//    常见的MIME类型多媒体格式如下（以audio开头的是音频，以video开头的是视频）：
//
//    “video/x-vnd.on2.vp8” - VP8 video (i.e. video in .webm)
//    “video/x-vnd.on2.vp9” - VP9 video (i.e. video in .webm)
//    “video/avc” - H.264/AVC video  对应H264
//    “video/mp4v-es” - MPEG4 video
//    “video/3gpp” - H.263 video
//    “audio/3gpp” - AMR narrowband audio
//    “audio/amr-wb” - AMR wideband audio
//    “audio/mpeg” - MPEG1/2 audio layer III
//    “audio/mp4a-latm” - AAC audio (note, this is raw AAC packets, not packaged in LATM!)
//    “audio/vorbis” - vorbis audio
//    “audio/g711-alaw” - G.711 alaw audio
//    “audio/g711-mlaw” - G.711 ulaw audio

    public int width;//视频宽
    public int height;//视频高
    public int bitRate;//码率
    public String videoMime;//视频文件类型
    public String audioMime;//音频文件类型

}
