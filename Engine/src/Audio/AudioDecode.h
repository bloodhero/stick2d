#pragma once

#include <string>
#include <vector>

extern "C" {
    struct AVFormatContext;
    struct AVCodecContext;
    enum   AVSampleFormat;
    struct SwrContext;
}

namespace stick2d {
    class AudioDecode
    {
    public:

        AudioDecode(std::string_view filename);
        ~AudioDecode();
        void* getData() { return m_out_buffer_data.data(); }
        int getSize() { return m_out_buffer_size; }
        int getSampleRate() { return m_out_sample_rate; }
        int getChannels() { return m_out_channels; }
        const char* getFormatName() { return m_out_format_name.c_str(); }

    private:
        int getNumChannels(uint64_t channel_layout);
        AVSampleFormat getOutFormat(AVSampleFormat fmt);
        SwrContext* m_swr_ctx;
        AVFormatContext* m_av_format_ctx;
        AVCodecContext* m_av_codec_ctx;

        int64_t m_out_channel_layout;
        AVSampleFormat m_out_sample_fmt;
        bool m_status;
        std::string m_out_format_name;
        size_t m_out_buffer_size;
        int m_out_sample_rate;
        int m_out_channels;
        std::vector<uint8_t> m_out_buffer_data;
    };
}