#include "decode_base.h"

namespace{
    AVPixelFormat getPixFmt(AVHWDeviceType type,AVCodec *pc)
    {
        if (!pc || type==AV_HWDEVICE_TYPE_NONE)
        {
            return AV_PIX_FMT_NONE;
        }
        AVPixelFormat pix = AV_PIX_FMT_NONE;
        for (int i = 0; ; i++)
        {
            const AVCodecHWConfig *config = avcodec_get_hw_config(pc,i);
            if (!config)
            {
                break;
            }
            if(config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX
            && config->device_type==type)
            {
                pix = config->pix_fmt;
                break;
            }
        }
        return pix;
    }
}

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
        codec_ = avcodec_find_decoder(st->codecpar->codec_id);
    }
    if (!codec_) {
        qWarning("index:%d,avcodec_find_decoder error",st->index);
        goto err;
    }
    avctx_ = avcodec_alloc_context3(codec_); // 申请AVCodecContext
    if (!avctx_)
    {
        avcodec_free_context(&avctx_);
        qWarning("avcodec_alloc_context3 error");
        goto err;
    }
    
    auto ret = avcodec_parameters_to_context(avctx_,st->codecpar);
    if (ret <= 0)
    {
        qWarning("avcodec_parameters_to_context error");
        goto err;
    }

    if(device) {
        auto phwdc= reinterpret_cast<AVHWDeviceContext*>(device->data);
        if (!phwdc) {
            qWarning("index:%s, AVHWDeviceContext change error",ret);
            goto err;
        }
        auto pix = getPixFmt(phwdc->type,codec_);
        if(pix == AV_PIX_FMT_NONE)
        {
            goto err;
        }

        avctx_->pix_fmt=pix;
        

    }
    
    
err:
    return false;
}
