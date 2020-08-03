#pragma once

#include <array>
#include <string>

namespace stick2d {
    class AudioSource;
    class AudioBuffer;
    class MixChunk;

    class Audio
    {
    public:
        Audio();
        ~Audio();
        void playSFX(MixChunk* chunk);
        void playMUS(MixChunk* music, bool loop);
    private:
        static const int NUM_SOURCES = 32;
        std::array<AudioSource*, NUM_SOURCES> m_SFX;
        AudioSource* m_music;
    };

    class MixChunk
    {
    public:
        MixChunk(std::string_view filename);
        ~MixChunk();

        unsigned int getBufferID();
    private:
        AudioBuffer* m_buffer;
    };
}