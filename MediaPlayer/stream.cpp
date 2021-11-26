#include "stream.h"

stream::stream() {}

stream::~stream() {}

bool stream::openByUrl(const std::string url) { return false; }

bool stream::openInput(const char *url)
{
    pFmtCtx_ = avformat_alloc_context();
    pFmtCtx_->flags |= AVFMT_FLAG_NONBLOCK;
    pFmtCtx_->interrupt_callback.opaque = this;

    if (!CH_FFMPEG(avformat_open_input(&pFmtCtx_, url, nullptr, &pFmtDict_))) {
    }
    return false;
}