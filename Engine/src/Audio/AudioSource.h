#pragma once

#include <glm/vec3.hpp>


namespace stick2d {
    class AudioSource
    {
    public:
        AudioSource();
        ~AudioSource();

        void play(unsigned int buffer);
        void setVolume(float volume);
        void setPitch(float pitch);
        void setPosition(float x, float y, float z);
        void setPosition(glm::vec3 position);
        void setLooping(bool loop);
        bool isPlaying();
        void pause();
        void resume();
        void stop();

    private:
        unsigned int m_source_id;
        unsigned int m_buffer_id;
        float m_gain;
        float m_pitch;
        glm::vec3 m_position;
        bool m_loop;
    };
}