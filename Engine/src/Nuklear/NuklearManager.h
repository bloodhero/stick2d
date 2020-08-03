#pragma once

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear.h>

namespace stick2d {
    class Event;

    class NuklearManager
    {
    public:
        NuklearManager():m_ctx(nullptr) {}
        ~NuklearManager() = default;

        void onAttach();
        void onDetach();

        void begin();
        void end();
        void inputBegin();
        void inputEnd();
        void onEvent(Event& e);

        nk_context* getNuklearContext() { return m_ctx; }

    private:
        nk_context* m_ctx;
    };
}