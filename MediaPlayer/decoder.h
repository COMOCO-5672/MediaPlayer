#ifndef DECODER_H
#define DECODER_H

#ifdef _WIN32

extern "C"{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
};
#else

#ifdef __cplusplus
extern "C"
{
#endif

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

#ifdef __cplusplus
}
#endif
#endif

class decoder
{
public:
    decoder();
    ~decoder();
    bool start();
};

#endif // DECODER_H
