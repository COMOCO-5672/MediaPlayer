#ifndef DECODE_BASE_H
#define DECODE_BASE_H

#include "ffmpeg_util.h"
#include <atomic>
#include <queue>

class DecoderBase {
  private:
    int id_;
    int codecId_;
    int width_;
    int height_;

    AVCodec *codec_;
    AVCodecContext *avctx_;

    std::queue<FramePtr> frames_;

    std::atomic_bool dec_working_ { false };
    std::thread dec_work_thread;

  public:
    std::queue<PacketPtr> pkts_;

  public:
    DecoderBase(AVStream *st);
    ~DecoderBase();

    bool parsePacket(PacketPtr pkt);

    bool open(AVStream *st, AVBufferRef *device, AVDictionary *dict);

    bool createBuffer(AVBufferRef *device, int width, int height);

    bool openDecoder(AVStream *st, AVBufferRef *device);

    bool closeDecoder();

    bool receiveFrame();

    void pushFrame(FramePtr fp);

    void work();

    void pushPacket(PacketPtr pkt);

  protected:
};

#endif