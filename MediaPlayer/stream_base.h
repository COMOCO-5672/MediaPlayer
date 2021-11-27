#ifndef STREAM_BASE_H
#define STREAM_BASE_H

#include "decode_base.h"
#include <string>

class stream_base {
  private:
    /* data */
  public:
    stream_base(/* args */);
    ~stream_base();

    bool open(AVFormatContext *avFmt);

    bool start(const std::map<int, AVBufferRef *> &idMapDevice);

    void stop();

  protected:
    virtual bool open_impl(AVFormatContext *avFmt) = 0;

    virtual bool close_impl() = 0;

    virtual bool start_impl(const std::map<int, AVBufferRef *> &idMapDevice) = 0;

    virtual bool stop_impl() = 0;
};
#endif