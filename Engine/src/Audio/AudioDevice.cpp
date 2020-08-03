#include "pch.h"

#include "Audio/AudioDevice.h"
#include "Core/Logger.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace stick2d {

    AudioDevice::AudioDevice() :
        m_context(nullptr),
        m_device(nullptr),
        m_device_name(""),
        m_gain(1.0),
        m_position{0,0,0}
    {
        m_device = alcOpenDevice(nullptr);
        ASSERT(m_device, "alcOpenDevice failed: {}", alGetError());

        m_device_name = alcGetString(m_device, ALC_DEVICE_SPECIFIER);

        m_context = alcCreateContext(m_device, nullptr);
        if (m_context == nullptr)
        {
            alcCloseDevice(m_device);
            ASSERT(m_context, "alcCreateContext failed: {}", alGetError());
        }

        if (!alcMakeContextCurrent(m_context))
        {
            alcDestroyContext(m_context);
            alcCloseDevice(m_device);
            ASSERT(false, "alcMakeContextCurrent failed: {}", alGetError());
        }

        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alListenerf(AL_GAIN, m_gain);

        LOG_TRACE("AudioDevice opened!");
    }

    AudioDevice::~AudioDevice()
    {

        alcDestroyContext(m_context);

        auto result = alcCloseDevice(m_device);
        ASSERT(result, "alcCloseDevice failed: {}", alGetError());

        LOG_TRACE("AudioDevice closed!");
    }

    const char* AudioDevice::getDeviceName()
    {
        return m_device_name.c_str();
    }

    void AudioDevice::setPosition(glm::vec3 position)
    {
        m_position = position;
        alListenerfv(AL_POSITION, glm::value_ptr(position));
    }

    float AudioDevice::getGain()
    {
        return m_gain;
    }

    void AudioDevice::setGain(float gain)
    {
        m_gain = gain;
        alListenerf(AL_GAIN, m_gain);
    }

}