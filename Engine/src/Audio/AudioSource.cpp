#include "pch.h"

#include "Audio/AudioSource.h"
#include "Core/Logger.h"

#include <AL/al.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace stick2d {

    AudioSource::AudioSource():
        m_buffer_id(0),
        m_gain(1.0),
        m_loop(false),
        m_pitch(1.0),
        m_position{0,0,0},
        m_source_id(0)
    {
        alGetError();
        alGenSources(1, &m_source_id);
        const ALenum error = alGetError();
        ASSERT(error == AL_NO_ERROR, "alGenSources failed: {}", error);

        alSourcef(m_source_id, AL_GAIN, 1.0f);
        alSourcef(m_source_id, AL_PITCH, 1.0f);
        alSource3f(m_source_id, AL_POSITION, 0.0f, 0.0f, 0.0f);
    }

    AudioSource::~AudioSource()
    {
        stop();
        alSourcei(m_source_id, AL_BUFFER, AL_NONE);
        alDeleteSources(1, &m_source_id);
    }

    void AudioSource::play(unsigned int buffer)
    {
        stop();
        alSourcei(m_source_id, AL_BUFFER, buffer);
        alSourcePlay(m_source_id);
    }

    void AudioSource::setVolume(float volume)
    {
        m_gain = volume;
        alSourcef(m_source_id, AL_GAIN, volume);
    }

    void AudioSource::setPitch(float pitch)
    {
        m_pitch = pitch;
        alSourcef(m_source_id, AL_PITCH, pitch);
    }

    void AudioSource::setPosition(float x, float y, float z)
    {
        m_position = { x, y, z };
        alSourcefv(m_source_id, AL_POSITION, glm::value_ptr(m_position));
    }

    void AudioSource::setPosition(glm::vec3 position)
    {
        m_position = position;
        alSourcefv(m_source_id, AL_POSITION, glm::value_ptr(m_position));
    }

    void AudioSource::setLooping(bool loop)
    {
        m_loop = loop;
        alSourcei(m_source_id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    }

    bool AudioSource::isPlaying()
    {
        int state;
        alGetSourcei(m_source_id, AL_SOURCE_STATE, &state);
        return state == AL_PLAYING;
    }

    void AudioSource::pause()
    {
        alSourcePause(m_source_id);
    }

    void AudioSource::resume()
    {
        alSourcePlay(m_source_id);
    }

    void AudioSource::stop()
    {
        alSourceStop(m_source_id);
    }

}