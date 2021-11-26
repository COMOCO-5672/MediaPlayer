#ifndef STREAM_H
#define STREAM_H

#include "stream_base.h"

class stream {
  private:
    AVFormatContext *pFmtCtx_ { nullptr };
    AVDictionary *pFmtDict_ { nullptr };

  public:
    stream();
    ~stream();

    bool openByUrl(const std::string url);

    bool openInput(const char *url);
};
#endif