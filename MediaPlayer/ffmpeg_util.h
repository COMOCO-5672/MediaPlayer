#ifndef FFMPEG_UTIL_H
#define FFMPEG_UTIL_H

#include <QDebug>
#include <atomic>
#include <memory>
#include <mutex>

#ifdef __cplusplus
extern "C" {
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/log.h>
#include <libavutil/time.h>
#include <libswscale/swscale.h>

#ifdef __cplusplus
}
#endif

struct FD {
    FD() {}
    FD(const FD &) {}
    FD(FD &&) {}
    FD &operator=(const FD &) { return *this; }
    FD &operator=(FD &&) { return *this; }
    void operator()(AVFrame *p) const;
};

struct PD {
    PD() {}
    PD(const PD &) {}
    PD(PD &&) {}
    PD &operator=(const PD &) { return *this; }
    PD &operator=(PD &&) { return *this; }
    void operator()(AVPacket *p) const;
};

class FramePtr : public std::unique_ptr<AVFrame, FD> {
  public:
    explicit FramePtr(AVFrame *p = nullptr);
    FramePtr(FramePtr &&_R);
    FramePtr(const FramePtr &_R) = delete;
    FramePtr clone();
};

class PacketPtr : public std::unique_ptr<AVPacket, PD> {
  public:
    explicit PacketPtr(AVPacket *p = nullptr);
    PacketPtr(PacketPtr &&_R);
    PacketPtr(const PacketPtr &_R) = delete;
    PacketPtr clone();
};

std::string avErrStr(int code);
#define AV_ERR(code) avErrStr(code).c_str()

bool check_ffmpeg(int err, const char *func, const char *file, int line, const char *call);
#define CH_FFMPEG(x) check_ffmpeg((x), #x, __FILE__, __LINE__, __FUNCTION__)

#endif
