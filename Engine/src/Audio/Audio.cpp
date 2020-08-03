#include "pch.h"
#include "Audio/Audio.h"
#include "Audio/AudioSource.h"
#include "Audio/AudioBuffer.h"
#include "Audio/AudioDecode.h"

namespace stick2d {

    Audio::Audio() :
        m_music(nullptr)
    {
        for (auto& player : m_SFX)
        {
            player = new AudioSource();
        }

        m_music = new AudioSource();
    }

    Audio::~Audio()
    {
        for (auto player : m_SFX)
        {
            delete player;
        }

        delete m_music;
    }

    void Audio::playSFX(MixChunk* chunk)
    {
        for (auto next_availble_source : m_SFX)
        {
            if (next_availble_source->isPlaying() == false)
            {
                next_availble_source->play(chunk->getBufferID());
                break;
            }
        }
    }

    void Audio::playMUS(MixChunk* music, bool loop)
    {
        m_music->play(music->getBufferID());
        m_music->setLooping(loop);
    }


    MixChunk::MixChunk(std::string_view filename)
    {
        auto audio = new AudioDecode(filename);
        m_buffer = new AudioBuffer(audio->getData(), audio->getSize(), audio->getSampleRate(), audio->getFormatName(), audio->getChannels());
        delete audio;
    }

    MixChunk::~MixChunk()
    {
        delete m_buffer;
    }

    unsigned int MixChunk::getBufferID()
    {
        return m_buffer->getBufferId();
    }

}