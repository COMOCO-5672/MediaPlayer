#include "decode_base.h"
#include <memory>

namespace {
AVPixelFormat getPixFmt(AVHWDeviceType type, AVCodec *pc)
{
    if (!pc || type == AV_HWDEVICE_TYPE_NONE) {
        return AV_PIX_FMT_NONE;
    }
    AVPixelFormat pix = AV_PIX_FMT_NONE;
    for (int i = 0;; i++) {
        const AVCodecHWConfig *config = avcodec_get_hw_config(pc, i);
        if (!config) {
            break;
        }
        if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
            config->device_type == type) {
            pix = config->pix_fmt;
            break;
        }
    }
    return pix;
}
} // namespace

DecoderBase::DecoderBase(AVStream *st)
    : codecId_(st->codecpar->codec_id), width_(st->codecpar->width), height_(st->codecpar->height)
{
}

DecoderBase::~DecoderBase() {}

bool DecoderBase::parsePacket(PacketPtr pkt)
{

    bool ret = true;
    int send_ret = 0;
    bool is_error_data = false;
    clock_t start_clock = clock();

    for (;;) {
        send_ret = avcodec_send_packet(avctx_, pkt.get());
        if (send_ret >= 0) {

        } else if (send_ret == AVERROR(EAGAIN)) {
            receiveFrame();
            continue;
        }
        break;
    }
    ret = receiveFrame();
    return ret;
}

bool DecoderBase::open(AVStream *st, AVBufferRef *device, AVDictionary *dict)
{
    if (device != nullptr) {
        if (!this->createBuffer(device, width_, height_)) {
            return false;
        }
    }

    if (this->openDecoder(st, device)) {
        dec_working_.store(true);
        dec_work_thread = std::thread(&DecoderBase::work, this);
        return true;
    }
    return false;
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
        qWarning("index:%d,avcodec_find_decoder error", st->index);
        goto err;
    }
    avctx_ = avcodec_alloc_context3(codec_); // 申请AVCodecContext
    if (!avctx_) {
        avcodec_free_context(&avctx_);
        qWarning("avcodec_alloc_context3 error");
        goto err;
    }
    if (!st->codecpar->extradata) {
        qWarning("no extradata");
    }

    auto ret = avcodec_parameters_to_context(avctx_, st->codecpar);
    if (ret < 0) {
        qWarning("avcodec_parameters_to_context error");
        goto err;
    }

    if (device) {
        auto phwdc = reinterpret_cast<AVHWDeviceContext *>(device->data);
        if (!phwdc) {
            qWarning("index:%s, AVHWDeviceContext change error", ret);
            goto err;
        }
        auto pix = getPixFmt(phwdc->type, codec_);
        if (pix == AV_PIX_FMT_NONE) {
            goto err;
        }

        avctx_->sw_pix_fmt = pix;
        avctx_->hw_device_ctx = av_buffer_ref(device);
        avctx_->extra_hw_frames = 10;
    }
    if (!CH_FFMPEG(avcodec_open2(avctx_, codec_, nullptr))) {
        goto err;
    }
    return true;
err:
    return false;
}

void DecoderBase::work()
{
    while (dec_working_) {
        if (pkts_.empty())
            continue;

        PacketPtr pkt(std::move(pkts_.front()));
        pkts_.pop();
        if (!(pkt.get()->flags & AV_PKT_FLAG_KEY)) { // 如果第一帧为非关键帧
            if (!frames_.empty()) {
                frames_.front()->pts = pkt->pts;
                frames_.front()->pkt_pts = pkt->pts;
                frames_.front()->pkt_dts = pkt->dts;
                frames_.front()->pkt_pos = pkt->pos;
                frames_.front()->pkt_size = pkt->size;
                frames_.front()->pkt_duration = pkt->duration;
            }
            continue;
        }
        if (!this->parsePacket(std::move(pkt))) {
            continue;
        }
    }
    dec_working_.store(false);
}

bool DecoderBase::receiveFrame()
{
    auto ret = 0;
    while (ret >= 0) {
        FramePtr fp(av_frame_alloc());
        ret = avcodec_receive_frame(avctx_, fp.get());
        if (ret == 0) {
            this->pushFrame(std::move(fp));
        } else if (ret == AVERROR_EOF) {
            avcodec_flush_buffers(avctx_);
        } else if (ret != AVERROR(EAGAIN)) {
            qWarning("avcodec_receive_frame error:%d", ret);
            return false;
        }
    }
    return true;
}

void DecoderBase::pushFrame(FramePtr fp) { frames_.push(std::move(fp)); }

void DecoderBase::pushPacket(PacketPtr pkt) { pkts_.push(std::move(pkt)); }

FramePtr DecoderBase::getFrame()
{
    FramePtr ret = std::move(frames_.front());
    frames_.pop();
    return ret;
}
