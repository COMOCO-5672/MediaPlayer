#ifndef DECODE_BASE_H
#define DECODE_BASE_H

#include "ffmpeg_util.h"

class DecoderBase {
  private:
    int id_;
    int codecId_;
    int width_;
    int height_;

  public:
    DecoderBase(AVStream *st);
    ~DecoderBase();

    bool open(AVStream *st, AVBufferRef *device, AVDictionary *dict);

  private:
    bool createBuffer(AVBufferRef *device, int width, int height);
};

#endif