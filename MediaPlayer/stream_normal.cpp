#include "stream_normal.h"

stream_normal::stream_normal(/* args */) {}

stream_normal::~stream_normal() {}

bool stream_normal::open_impl(AVFormatContext *avFmt)
{

    if (!find_stream(avFmt)) {
        return false;
    }
    decs_.push_back(new DecoderBase(st_));
    return true;
}

bool stream_normal::close_impl() { return false; }

bool stream_normal::start_impl(const std::map<int, AVBufferRef *> &idMapDevice)
{
    int i = 0;
    if (idMapDevice.empty()) {
        decs_.at(0)->open(st_, nullptr, nullptr);
    }

    return false;
}

bool stream_normal::stop_impl() { return false; }

bool stream_normal::find_stream(AVFormatContext *avfmt)
{
    // find video stream
    for (uint32_t i = 0; i < avfmt->nb_streams; i++) {
        auto st = avfmt->streams[i];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            st_ = st;
            break;
        }
    }
    if (!st_) {
        return false;
    }
    return true;
}