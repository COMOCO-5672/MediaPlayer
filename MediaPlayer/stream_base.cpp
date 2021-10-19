#include "stream_base.h"

stream_base::stream_base(/* args */)
{
}

stream_base::~stream_base()
{
}

bool stream_base::open(AVFormatContext *avFmt)
{
    if (!open_impl(avFmt))
        return false;
    return true;
}
