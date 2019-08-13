package com.leon.androidffmpeg;

import android.view.Surface;

/**
 * @time:2019/8/12 16:30
 * @author:Leon
 * @description:
 */
public class FFmpegPlayer {
    FFmpegPlayer() {
        System.loadLibrary("avutil");
        System.loadLibrary("swresample");
        System.loadLibrary("avcodec");
        System.loadLibrary("avformat");
        System.loadLibrary("swscale");
        System.loadLibrary("avfilter");
        byte[] bytes = new byte[]{};
        new String(bytes);
    }
    public static native void playMedia(String url);

//    public static native int playMedia(String url, Surface surface);

    public static native void printFFmpegInfo();

    public static native String getVideoInfo(String url);
}
