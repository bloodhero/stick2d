#include "pch.h"

#include "Audio/AudioDecode.h"
#include "Core/Logger.h"

extern "C" {
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}


namespace stick2d {

    AudioDecode::AudioDecode(std::string_view filename) :
        m_av_format_ctx(nullptr),
        m_av_codec_ctx(nullptr),
        m_swr_ctx(nullptr),
        m_out_buffer_data(),
        m_status(true)
    {
        m_av_format_ctx = avformat_alloc_context();
        avformat_open_input(&m_av_format_ctx, filename.data(), NULL, NULL);
        avformat_find_stream_info(m_av_format_ctx, nullptr);

        int audio_stream_index = -1;
        AVStream* av_stream;

        for (unsigned i = 0; i < m_av_format_ctx->nb_streams; ++i)
        {
            av_stream = m_av_format_ctx->streams[i];
            if (av_stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                audio_stream_index = i;
                break;
            }
        }

        if (audio_stream_index == -1)
        {
            m_status = false;
            LOG_ERROR("Failed to find codec, {} may be not a audio file!", filename);
            return;
        }

        auto av_codec_params = av_stream->codecpar;
        auto av_codec = avcodec_find_decoder(av_codec_params->codec_id);
        m_av_codec_ctx = avcodec_alloc_context3(av_codec);

        avcodec_parameters_to_context(m_av_codec_ctx, av_codec_params);
        avcodec_open2(m_av_codec_ctx, av_codec, nullptr);

        m_out_sample_fmt = getOutFormat((AVSampleFormat)av_codec_params->format);

        if (av_codec_params->channel_layout == 0)
        {
            av_codec_params->channel_layout = av_get_default_channel_layout(av_codec_params->channels);
        }

        m_out_channel_layout = av_codec_params->channel_layout;
        m_out_format_name = av_get_sample_fmt_name(m_out_sample_fmt);
        m_out_sample_rate = av_codec_params->sample_rate;
        m_out_channels = av_codec_params->channels;


        m_swr_ctx = swr_alloc();
        swr_alloc_set_opts(m_swr_ctx,
            m_out_channel_layout, m_out_sample_fmt, m_out_sample_rate,
            av_codec_params->channel_layout, (AVSampleFormat)av_codec_params->format, av_codec_params->sample_rate,
            0, nullptr);

        swr_init(m_swr_ctx);

        AVPacket* av_packet = av_packet_alloc();
        AVFrame* av_frame = av_frame_alloc();

        while (av_read_frame(m_av_format_ctx, av_packet) >= 0)
        {
            avcodec_send_packet(m_av_codec_ctx, av_packet);

            int ret = avcodec_receive_frame(m_av_codec_ctx, av_frame);
            if (ret == AVERROR(EAGAIN)) {
                continue;
            }

            else if (ret < 0) {
                return;
            }

            if (av_packet->stream_index != audio_stream_index) {
                return;
            }

            uint8_t* out_buffer_data;

            auto dst_nb_samples = av_rescale_rnd(av_frame->nb_samples, m_out_sample_rate, av_frame->sample_rate, AV_ROUND_UP);

            av_samples_alloc(&out_buffer_data, NULL, m_out_channels, dst_nb_samples, m_out_sample_fmt, NULL);

            swr_convert(m_swr_ctx, &out_buffer_data, dst_nb_samples, (const uint8_t**)(av_frame->data), av_frame->nb_samples);

            auto size = av_samples_get_buffer_size(nullptr, m_out_channels, dst_nb_samples, m_out_sample_fmt, 1);

            m_out_buffer_data.insert(m_out_buffer_data.end(), (uint8_t*)out_buffer_data, (uint8_t*)out_buffer_data + size);


            av_freep(&out_buffer_data);

        }

        m_out_buffer_size = m_out_buffer_data.size();


        av_frame_free(&av_frame);
        av_packet_free(&av_packet);

    }

    AudioDecode::~AudioDecode()
    {
        avformat_close_input(&m_av_format_ctx);

        avcodec_close(m_av_codec_ctx);
        avcodec_free_context(&m_av_codec_ctx);

        swr_close(m_swr_ctx);
        swr_free(&m_swr_ctx);
    }


    int AudioDecode::getNumChannels(uint64_t channel_layout)
    {
        switch (channel_layout)
        {
        case AV_CH_LAYOUT_MONO:
            return 1;
        case AV_CH_LAYOUT_STEREO:
            return 2;
        default:
            LOG_ERROR("Unknown channel layout {}", av_get_channel_name(channel_layout));
            return 2;
        }
    }

    AVSampleFormat AudioDecode::getOutFormat(AVSampleFormat fmt)
    {
        switch (fmt) {
        case AV_SAMPLE_FMT_U8P:
            return AV_SAMPLE_FMT_U8;
        case AV_SAMPLE_FMT_S16P:
            return AV_SAMPLE_FMT_S16;
        case AV_SAMPLE_FMT_S32P:
            return AV_SAMPLE_FMT_FLT;
        case AV_SAMPLE_FMT_S64P:
            return AV_SAMPLE_FMT_DBL;
        case AV_SAMPLE_FMT_FLTP:
            return AV_SAMPLE_FMT_FLT;
        case AV_SAMPLE_FMT_DBLP:
            return AV_SAMPLE_FMT_DBL;
        default:
            return fmt;
        }
    }
}