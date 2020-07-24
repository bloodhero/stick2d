#pragma once

#include "Core/Event.h"

#include <SDL.h>
#include <string>
#include <vector>


namespace stick2d {
    class Event;
    class SceneStack;
    class Window;
    class Logger;
    class Bootstrap;
    class ImGuiManager;
    struct AppConfiguration;

    class Application
    {
    public:
        int start(Bootstrap* booter);
        friend Application* theApplication();
        friend class Director;

    private:
        void run();
        void onConfig();
        void onEvent(Event& e);
        void onClose();


        SceneStack* getSceneStack() { return m_scene_stack; }

        Application();
        ~Application();

        AppConfiguration* m_app_cfg;
        SceneStack* m_scene_stack;
        Window* m_window;
        Logger* m_logger;
        ImGuiManager* m_imgui_manager;
        bool m_running;
        bool m_minimized;
        float m_last_frame_time;

    };

    extern Application* theApplication();
}