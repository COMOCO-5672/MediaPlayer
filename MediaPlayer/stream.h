#ifndef STREAM_H
#define STREAM_H

#include "stream_base.h"

class stream
{
private:
    /* data */
public:
    stream();
    ~stream();

    bool openByUrl(const std::string url);
};
#endif