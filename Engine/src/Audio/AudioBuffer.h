#pragma once

#include <string>
typedef int ALenum;


namespace stick2d {
    class AudioBuffer
    {
    public:
        AudioBuffer(void* data, int buf_size, int sample_rate, const char* format_name, int channels);
        ~AudioBuffer();

        unsigned getBufferId() const { return m_buffer_id; }
        int getNumChannels() const { return m_num_channels; }
        int getFrequency() const { return m_frequency; }
        unsigned getBufferSize() const { return m_buffer_size; }

    private:

        ALenum getFormat(std::string_view format_name, int channels);
        unsigned m_buffer_id;
        int m_num_channels;
        int m_frequency;
        unsigned m_buffer_size;
    };
}