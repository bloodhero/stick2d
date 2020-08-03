#include "pch.h"

#include "Core/Application.h"
#include "Core/Timestep.h"
#include "Core/Director.h"
#include "Core/Scene.h"
#include "Core/SceneStack.h"
#include "Core/Bootstrap.h"
#include "Core/Window.h"
#include "ImGui/ImGuiManager.h"
#include "Nuklear/NuklearManager.h"
#include "Audio/AudioDevice.h"

#include <SDL.h>

namespace stick2d {

    Application::Application() :
        m_running(true),
        m_minimized(false),
        m_app_cfg(nullptr),
        m_scene_stack(nullptr),
        m_window(nullptr),
        m_logger(nullptr),
        m_audio(nullptr),
        m_last_frame_time(0)
    {
        m_app_cfg = new app_configuration();
        m_scene_stack = new SceneStack();

        m_logger = new Logger();
        m_audio = new AudioDevice();
        m_window = new Window();
        m_imgui_manager = new ImGuiManager();
        m_nuklear_manager = new NuklearManager();
    }


    Application::~Application()
    {
        delete m_scene_stack;
        delete m_app_cfg;
        delete m_imgui_manager;
        delete m_nuklear_manager;
        delete m_window;
        delete m_audio;
        delete m_logger;
    }


    void Application::onConfig()
    {
        // 图形管理器
        m_window->setFullscreen(m_app_cfg->isFullscreen);
        m_window->setResizable(m_app_cfg->isResizable);
        m_window->setResolution(m_app_cfg->resolution);
        m_window->setWindowTitle(m_app_cfg->windowTitle);
        m_window->setWindowIcon(m_app_cfg->windowIconFilename);

        // 输入管理器

        // 视频管理器

        // 音效管理器

    }

    void Application::onEvent(Event& e)
    {
        if (e.event.type == SDL_QUIT)
            onClose();
    }

    int Application::start(Bootstrap* booter)
    {
        auto director = stick2d::theDirector();

        booter->onInit();
        booter->configApp(m_app_cfg);

        director->runWithScene(booter->firstScene());

        onConfig();
        run();

        booter->onShutdown();
        return 0;
    }

    void Application::run()
    {
        m_imgui_manager->onAttach();
        m_nuklear_manager->onAttach();
        while (m_running)
        {
            SDL_Event event;

            m_nuklear_manager->inputBegin();
            while (SDL_PollEvent(&event))
            {
                Event e(event);
                onEvent(e);
                m_imgui_manager->onEvent(e);
                m_nuklear_manager->onEvent(e);
                m_scene_stack->getCurrentScene()->onEvent(e);
            }
            m_nuklear_manager->inputEnd();


            float time = (float)SDL_GetTicks();
            Timestep timestep = time - m_last_frame_time;
            m_last_frame_time = time;

            theDirector()->clearScreen();

            m_imgui_manager->begin();
            m_nuklear_manager->begin();
            m_scene_stack->getCurrentScene()->onUpdate(timestep);
            m_scene_stack->getCurrentScene()->onDraw();
            m_nuklear_manager->end();
            m_imgui_manager->end();

            theDirector()->updateScreen();

        }
        m_nuklear_manager->onDetach();
        m_imgui_manager->onDetach();
    }

    void Application::onClose()
    {
        m_running = false;
    }

    SDL_GLContext* Application::getGLContext()
    {
        return m_window->getGLContext();
    }

    SDL_Window* Application::getNativeWindow()
    {
        return m_window->getNativeWindow();
    }

    int Application::getWidth()
    {
        return m_window->getWidth();
    }

    int Application::getHeight()
    {
        return m_window->getHeight();
    }

    nk_context* Application::getNuklearContext()
    {
        return m_nuklear_manager->getNuklearContext();
    }

    Application* theApplication()
    {
        static Application instance;
        return &instance;
    }
}
