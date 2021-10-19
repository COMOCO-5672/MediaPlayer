#include <string>
#include "ffmpeg_util.h"

class stream_base
{
private:
    /* data */
public:
    stream_base(/* args */);
    ~stream_base();

    bool open(AVFormatContext *avFmt);

protected:
    virtual bool open_impl(AVFormatContext *avFmt) = 0;

    virtual bool close_impl() = 0;

    virtual bool start_impl(const std::map<int, AVBufferRef *> &idMapDevice) = 0;

    virtual bool stop_impl() = 0;
};