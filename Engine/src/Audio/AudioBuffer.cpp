#include "pch.h"

#include "Audio/AudioBuffer.h"
#include "Core/Logger.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace stick2d {

    AudioBuffer::AudioBuffer(void* data, int buf_size, int sample_rate, const char* format_name, int channels):
        m_num_channels(0),
        m_frequency(0),
        m_buffer_id(0),
        m_buffer_size(0)
    {
        alGetError();
        alGenBuffers(1, &m_buffer_id);
        auto error = alGetError();
        ASSERT(error == AL_NO_ERROR, "alGenBuffers failed: {}", error);


        alGetError();
        alBufferData(m_buffer_id, getFormat(format_name, channels), (const ALvoid*)data, buf_size, sample_rate);
        m_buffer_size = buf_size;
        m_frequency = sample_rate;
        m_num_channels = channels;
        error = alGetError();
        ASSERT(error == AL_NO_ERROR, "alBuffers submit data failed: {}", error);
    }

    AudioBuffer::~AudioBuffer()
    {
        alDeleteBuffers(1, &m_buffer_id);
    }

    ALenum AudioBuffer::getFormat(std::string_view format_name, int channels)
    {
        if (format_name == "u8" && channels == 1)
        {
            return AL_FORMAT_MONO8;
        }

        if (format_name == "s16" && channels == 1)
        {
            return AL_FORMAT_MONO16;
        }

        if (format_name == "u8" && channels == 2)
        {
            return AL_FORMAT_STEREO8;
        }

        if (format_name == "s16" && channels == 2)
        {
            return AL_FORMAT_STEREO16;
        }

        if (format_name == "flt" && channels == 1)
        {
            return AL_FORMAT_MONO_FLOAT32;
        }

        if (format_name == "flt" && channels == 2)
        {
            return AL_FORMAT_STEREO_FLOAT32;
        }

        if (format_name == "dbl" && channels == 1)
        {
            return AL_FORMAT_MONO_DOUBLE_EXT;
        }

        if (format_name == "dbl" && channels == 2)
        {
            return AL_FORMAT_STEREO_DOUBLE_EXT;
        }

        ASSERT(false, "AudioBuffer: unknown buffer format {}", format_name);
    }
}