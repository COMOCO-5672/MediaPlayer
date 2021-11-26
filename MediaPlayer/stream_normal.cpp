#include "stream_normal.h"

stream_normal::stream_normal(/* args */) {}

stream_normal::~stream_normal() {}

bool stream_normal::open_impl(AVFormatContext *avFmt) { return false; }

bool stream_normal::close_impl() { return false; }

bool stream_normal::start_impl(const std::map<int, AVBufferRef *> &idMapDevice)
{
    int i = 0;
    if (idMapDevice.empty()) {
    }
    return false;
}

bool stream_normal::stop_impl() { return false; }
