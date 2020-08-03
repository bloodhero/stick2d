#pragma once

#include <glm/vec3.hpp>
struct ALCdevice;
struct ALCcontext;
typedef unsigned int ALuint;

namespace stick2d {
    class AudioBuffer;
    class AudioPlayer;

    class AudioDevice
    {
    public:
        static const unsigned int UnavailableSource = ~0U;

        AudioDevice();
        ~AudioDevice();

        const char* getDeviceName();
        float getGain();
        glm::vec3 getPosition() { return m_position; }

        void setGain(float gain);
        void setPosition(glm::vec3 position);
    private:
        std::string m_device_name;
        ALCdevice* m_device;
        ALCcontext* m_context;
        float m_gain;
        glm::vec3 m_position;
    };
}