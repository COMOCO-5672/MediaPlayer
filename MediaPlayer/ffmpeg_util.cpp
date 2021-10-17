#include "ffmpeg_util.h"

void FD::operator()(AVFrame *p) const
{
    if (p)
    {
        av_frame_free(&p);
    }
}

FramePtr::FramePtr(AVFrame *p) : std::unique_ptr<AVFrame, FD>(p, FD())
{
}

FramePtr::FramePtr(FramePtr &&_R)
    : std::unique_ptr<AVFrame, FD>(_R.release(), std::forward<FD>(_R.get_deleter()))
{
}

FramePtr FramePtr::clone()
{
    return FramePtr(av_frame_clone(this->get()));
}

void PD::operator()(AVPacket *p) const
{
    if (p)
        av_packet_free(&p);
}

PacketPtr::PacketPtr(AVPacket *p)
    : std::unique_ptr<AVPacket, PD>(p, PD())
{
}

PacketPtr::PacketPtr(PacketPtr &&_R)
    : std::unique_ptr<AVPacket, PD>(_R.release(), std::forward<PD>(_R.get_deleter()))
{
}

PacketPtr PacketPtr::clone()
{
    return PacketPtr(av_packet_clone(this->get()));
}

std::string avErrStr(int code)
{
    static std::mutex mtx;
    static char str[256] = {0};

    std::lock_guard<std::mutex> lg(mtx);
    (void)lg;

    memset(str, 0, sizeof(str));
    av_strerror(code, str, sizeof(str));
    return std::string(str);
}

bool check_ffmpeg(int err, const char *func, const char *file, int line, const char *call)
{
    if (err < 0)
    {
        qWarning() << file << "[" << line << "] call" << func << "error" << AV_ERR(err) << "(" << err << ")";
        return false;
    }
    return true;
}
