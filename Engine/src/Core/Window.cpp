#include "pch.h"
#include "Core/Window.h"
#include "glad/glad.h"

namespace stick2d
{
    Window::Window() :
        m_window(nullptr),
        m_gl_context(nullptr)
    {
        int result = SDL_Init(SDL_INIT_VIDEO);
        ASSERT(!result, "SDL: Failed to initialize the SDL system. {}", SDL_GetError());

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        m_window = SDL_CreateWindow(m_props.title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_props.resolution.x,
            m_props.resolution.y,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        ASSERT(m_window, "SDL: Failed to initialize the SDL window. {}", SDL_GetError());

        m_gl_context = SDL_GL_CreateContext(m_window);

        SDL_GL_MakeCurrent(m_window, m_gl_context);
        SDL_GL_SetSwapInterval(m_props.isVsync ? 1 : 0);

        result = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
        ASSERT(result, "GLAD: Failed to initialize the OpenGL context.");

        LOG_TRACE("SDL: initialized.");
        LOG_TRACE("OpenGL version loaded: {}.{}", GLVersion.major, GLVersion.minor);
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(m_gl_context);
        SDL_DestroyWindow(m_window);

        SDL_Quit();

        LOG_TRACE("SDL: closed.");
    }

    void Window::onUpdate()
    {
        SDL_GL_SwapWindow(m_window);
    }


    void Window::setVSync(bool enabled)
    {
        if (m_props.isVsync != enabled)
        {
            m_props.isVsync = enabled;
            SDL_GL_SetSwapInterval(enabled ? 1 : 0);

            LOG_TRACE("Window VSync is {}", SDL_GL_GetSwapInterval() ? "enabled" : "disabled");
        }
    }


    void Window::setResizable(bool enabled)
    {
        if (m_props.isFullscreen == false && m_props.isResizable != enabled)
        {
            m_props.isResizable = enabled;
            SDL_SetWindowResizable(m_window, enabled ? SDL_TRUE : SDL_FALSE);

            LOG_TRACE("Window resizable is {}", enabled ? "enabled" : "disabled");
        }
    }


    void Window::setFullscreen(bool enabled)
    {
        if (m_props.isFullscreen != enabled)
        {
            m_props.isFullscreen = enabled;
            SDL_SetWindowFullscreen(m_window, enabled ? SDL_WINDOW_FULLSCREEN : 0);

            if (!enabled)
                SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

            LOG_TRACE("Window fullscreen is {}", enabled ? "enabled" : "disabled");
        }
    }


    void Window::setWindowTitle(std::string_view title)
    {
        if (!m_props.title.empty())
        {
            m_props.title = title;
            SDL_SetWindowTitle(m_window, title.data());

            LOG_TRACE("Window title : {}", title);
        }
    }


    void Window::setResolution(glm::ivec2 resolution)
    {

            // change resolution only in the case it really changes
            if (resolution == m_props.resolution)
                return;

            // asking for fullscreen mode that does not change current screen resolution
            if (resolution.x <= 0 || resolution.y <= 0)
            {
                setFullscreen(true);
            }
            else
            {
                m_props.resolution = resolution;

                SDL_SetWindowSize(m_window, resolution.x, resolution.y);
                SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            }

            int x = 0;
            int y = 0;
            SDL_GetWindowSize(m_window, &x, &y);

            LOG_TRACE("Window resized to {}x{}", x, y);
    }

    void Window::setWindowIcon(std::string_view icon_filename)
    {
        if (!icon_filename.empty())
        {
            m_props.icon = icon_filename;

            SDL_Surface* surface = SDL_LoadBMP(icon_filename.data());
            ASSERT(surface, "Load window icon failed: {}", SDL_GetError());
            SDL_SetWindowIcon(m_window, surface);
            SDL_FreeSurface(surface);

            LOG_TRACE("Window icon is {}", icon_filename);
        }
    }

    void Window::clearScreen()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::updateScreen()
    {
        SDL_GL_SwapWindow(m_window);
    }

}