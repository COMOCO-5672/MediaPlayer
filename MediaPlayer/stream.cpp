#include "stream.h"

static stream_base *getStreamBase(AVInputFormat *ifmt) { return new stream_normal(); }

stream::stream() {}

stream::~stream() {}

bool stream::openByUrl(const std::string url)
{
    if (!openInput(url.c_str())) {
        return false;
    }
    pStream_ = getStreamBase(pFmtCtx_->iformat);
    if (!pStream_->open(pFmtCtx_)) {
        // TODO:Close
        return false;
    }

    if (!pStream_->start(idMapDevice_)) {
        // TODO::CLOSE
        return false;
    }
    recv_working_.store(true);
    working_thread_ = std::thread(&stream::recvPkt, this);
    return true;
}

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

bool stream::closeInput() { return false; }

void stream::recvPkt()
{
    while (recv_working_) {
        PacketPtr pkt(av_packet_alloc());
        if (pkt == nullptr) {
            recv_working_.store(false);
        }
        int ret = av_read_frame(pFmtCtx_, pkt.get());
        if (ret != 0) {
            continue;
        }
        pStream_->pushPacket(std::move(pkt));
    }
}
