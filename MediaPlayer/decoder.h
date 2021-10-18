#ifndef DECODER_H
#define DECODER_H

#include "ffmpeg_util.h"

class decoder
{
public:
    decoder();
    ~decoder();
    bool start();
};

#endif // DECODER_H
