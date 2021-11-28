#ifndef STREAM_H
#define STREAM_H

#include "stream_normal.h"
#include <atomic>

class stream {
  private:
    AVFormatContext *pFmtCtx_ { nullptr };
    AVDictionary *pFmtDict_ { nullptr };
    stream_base *pStream_ { nullptr };

    std::map<int, AVBufferRef *> idMapDevice_;

    std::atomic_bool recv_working_ { false };
    std::thread working_thread_;

  public:
    stream();
    ~stream();

    bool openByUrl(const std::string url);

    bool openInput(const char *url);

    bool closeInput();

    void recvPkt();
};
#endif