#include "pch.h"

#include "Core/AppConfiguration.h"
#include "Core/Application.h"
#include "Core/Timestep.h"
#include "Core/Director.h"
#include "Core/Scene.h"
#include "Core/SceneStack.h"
#include "Core/Bootstrap.h"
#include "Core/Window.h"
#include "ImGui/ImGuiManager.h"


#include <SDL.h>

namespace stick2d {
    Application::Application() :
        m_running(true),
        m_minimized(false),
        m_app_cfg(new AppConfiguration()),
        m_scene_stack(new SceneStack()),
        m_window(nullptr),
        m_logger(nullptr)
    {
        m_logger = theLogger();
        m_window = theWindow();
        m_imgui_manager = theImGuiManager();
    }


    Application::~Application()
    {
        delete m_scene_stack;
        delete m_app_cfg;
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
        while (m_running)
        {
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                Event e(event);
                onEvent(e);
                m_imgui_manager->onEvent(e);
                m_scene_stack->getCurrentScene()->onEvent(e);
            }


            float time = (float)SDL_GetTicks();
            Timestep timestep = time - m_last_frame_time;
            m_last_frame_time = time;

            theDirector()->clearScreen();

            m_imgui_manager->begin();
            m_scene_stack->getCurrentScene()->onUpdate(timestep);
            m_scene_stack->getCurrentScene()->onDraw();
            m_imgui_manager->end();

            theDirector()->updateScreen();
        }
        m_imgui_manager->onDetach();
    }




    void Application::onClose()
    {
        m_running = false;
    }



    Application* theApplication()
    {
        static Application instance;
        return &instance;
    }


}
