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
        avformat_close_input(&pFmtCtx_);
        qWarning("avformat_open_input error");
        return false;
    }

    if (!CH_FFMPEG(avformat_find_stream_info(pFmtCtx_, nullptr))) {
        qWarning("avformat_find_stream_info error");
        return false;
    }
    av_dump_format(pFmtCtx_, 0, url, 0);
    return true;
}