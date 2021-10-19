#include "stream_base.h"

class stream_normal : public stream_base
{
private:
    /* data */
public:
    stream_normal(/* args */);
    ~stream_normal();

protected:
    bool open_impl(AVFormatContext *avFmt) override;

    bool close_impl() override;

    bool start_impl(const std::map<int, AVBufferRef *> &idMapDevice) override;

    bool stop_impl() override;

private:
    bool find_stream();
};

stream_normal::stream_normal(/* args */)
{
}

stream_normal::~stream_normal()
{
}

bool stream_normal::open_impl(AVFormatContext *avFmt)
{
    return false;
}
