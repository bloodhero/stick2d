#pragma once

#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <vector>

struct nk_context;

namespace stick2d {
    class Event;
    class SceneStack;
    class Window;
    class Logger;
    class Bootstrap;
    class ImGuiManager;
    class NuklearManager;
    class AudioDevice;

    struct app_configuration
    {
        std::string windowTitle = "";
        std::string windowIconFilename = "";
        std::string logFile;
        std::string dataPath;
        glm::ivec2 resolution = { 800, 600 };
        bool isFullscreen = false;
        bool isResizable = false;
        glm::u8vec3 color;
    };

    class Application
    {
    public:
        int start(Bootstrap* booter);
        friend Application* theApplication();
        friend class Director;
        friend class AudioPlayer;

        SDL_Window* getNativeWindow();
        SDL_GLContext* getGLContext();
        int getWidth();
        int getHeight();
        nk_context* getNuklearContext();

    private:
        void run();
        void onConfig();
        void onEvent(Event& e);
        void onClose();


        SceneStack* getSceneStack() { return m_scene_stack; }

        Application();
        ~Application();

        app_configuration* m_app_cfg;
        SceneStack* m_scene_stack;
        Window* m_window;
        Logger* m_logger;
        AudioDevice* m_audio;
        ImGuiManager* m_imgui_manager;
        NuklearManager* m_nuklear_manager;
        bool m_running;
        bool m_minimized;
        float m_last_frame_time;

    };

    extern Application* theApplication();
}