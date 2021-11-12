#include "stream_base.h"

stream_base::stream_base(/* args */) {}

stream_base::~stream_base() {}

bool stream_base::open(AVFormatContext *avFmt)
{
    if (!open_impl(avFmt))
        return false;
    return true;
}

bool stream_base::start(const std::map<int, AVBufferRef *> &idMapDevice)
{
    return this->start_impl(idMapDevice);
}

void stream_base::stop() { this->stop_impl(); }