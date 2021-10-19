#include "decoder.h"

decoder::decoder()
{
}
decoder::~decoder()
{
}
bool decoder::start()
{
    AVFormatContext *pFormatCtx;    // 封装格式上下文结构体，也是统领全局的结构体，保存了视频文件封装 格式相关信息
    int i = 0, videoindex;
    AVCodecContext  *pCodecCtx;     // 编码器上下文结构体，保存了视频（音频）编解码相关信息
    AVCodec         *pCodec;        // AVcodec是存储编解码器信息的结构体
    AVFrame *pFrame, *pFrameYUV;    // AVFrame是包含码流参数较多的结构体
    unsigned char   *out_buffer;    
    AVPacket        *packet;        // AVPacket是存储压缩编码数据相关信息的结构体

    int y_size;
    int ret,got_picture;

    // struct SwsContext 结构体位于libswscale类库，该类库主要用于处理图片像素数据，可以完成图片像素格式的转换，图片的拉伸等工作
    struct SwsContext *img_convert_ctx;
    char filepath[] = "";
    FILE *fp_yuv = fopen("","wb+");
    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();
    if(avformat_open_input(&pFormatCtx,"",NULL,NULL)!=0)
    {
        printf("Couldn't open input stream.\n");
        avformat_network_deinit();
        return false;
    }

    if(avformat_find_stream_info(pFormatCtx,NULL)<0)
    {
        printf("Couldn't fins stream information.\n");
        avformat_network_deinit();
        return false;
    }

    videoindex = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoindex = i;
            break;
        }
    }
    if(videoindex == -1)
    {
        printf("");
        avformat_network_deinit();
        return false;
    }
    
    pCodecCtx = pFormatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);  // 查找符合ID的已注册解码器
    if(pCodec == NULL)
    {
        printf("Codec not found.\n");
        return false;
    }

    if(avcodec_open2(pCodecCtx,pCodec,NULL)<0)
    {
        printf("Coundn't not open codec.\n");
        return false;
    }

    pFrame = av_frame_alloc();
    pFrameYUV = av_frame_alloc();
    out_buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,pCodecCtx->width,pCodecCtx->height,1));
    // 根据指定的图像参数和提供的数组设置参数指针和linesize大小
    av_image_fill_arrays(pFrameYUV->data,pFrameYUV->linesize,out_buffer,AV_PIX_FMT_YUV420P,pCodecCtx->width,pCodecCtx->height,1);
    packet = (AVPacket *)av_malloc(sizeof(AVPacket));
    // Output info
    printf("-----------file informattion----------\n");
    av_dump_format(pFormatCtx,0,0,0);
    return false;
}
