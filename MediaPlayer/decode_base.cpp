#include "decode_base.h"

DecoderBase::DecoderBase(AVStream *st)
    : codecId_(st->codecpar->codec_id), width_(st->codecpar->width), height_(st->codecpar->height)
{
}

DecoderBase::~DecoderBase() {}

bool DecoderBase::open(AVStream *st, AVBufferRef *device, AVDictionary *dict)
{
    if (device != nullptr) {
        if () {
            /* code */
        }
        this->createBuffer(device, width_, height_);
    }
}

bool DecoderBase::createBuffer(AVBufferRef *device, int width, int height) { return false; }