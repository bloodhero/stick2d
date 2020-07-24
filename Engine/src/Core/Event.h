#pragma once

#include <SDL.h>
#include <functional>
#include <cstdint>

namespace stick2d {

    class Event
    {
    public:
        Event() = delete;
        ~Event() = default;

        Event(SDL_Event& e) :
            event(e),
            handled(false)
        {}
        bool handled;
        SDL_Event& event;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& e)
            : m_event(e)
        {}

        bool dispatch(SDL_EventType type, std::function<bool(Event& e)> handler)
        {
            if (m_event.event.type == type)
            {
                m_event.handled = handler(m_event);
                return true;
            }

            return false;
        }
    private:
        Event& m_event;
    };
}

