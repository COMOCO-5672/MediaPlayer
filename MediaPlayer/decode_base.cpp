#include "decode_base.h"

DecoderBase::DecoderBase(AVStream *st)
    : codecId_(st->codecpar->codec_id), width_(st->codecpar->width), height_(st->codecpar->height)
{
}

DecoderBase::~DecoderBase() {}

bool DecoderBase::open(AVStream *st, AVBufferRef *device, AVDictionary *dict)
{
    if (device != nullptr) {
        if (!this->createBuffer(device, width_, height_)) {
            return false;
        }
    }
}

bool DecoderBase::createBuffer(AVBufferRef *device, int width, int height) { return false; }

bool DecoderBase::openDecoder(AVStream *st, AVBufferRef *device)
{
    if (device) {
        std::string codeName;
        switch (st->codecpar->codec_id) {
        case AV_CODEC_ID_H264:
            codeName.assign("h264_cuvid");
            // codeName.assign("h264_qsv");
            break;
        case AV_CODEC_ID_HEVC:
            codeName.assign("hevc_cuvid");
            // codeName.assign("hevc_qsv");
            break;
        default:
            qWarning("can not get hardware decoder");
            return false;
        }
        codec_ = avcodec_find_decoder_by_name(codeName.c_str());
    } else {
    }
}
