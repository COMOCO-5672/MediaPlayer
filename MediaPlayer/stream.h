#ifndef STREAM_H
#define STREAM_H

#include "stream_normal.h"

class stream {
  private:
    AVFormatContext *pFmtCtx_ { nullptr };
    AVDictionary *pFmtDict_ { nullptr };
    stream_base *pStream_ { nullptr };

    std::map<int, AVBufferRef *> idMapDevice_;

  public:
    stream();
    ~stream();

    bool openByUrl(const std::string url);

    bool openInput(const char *url);

    bool closeInput();
};
#endif