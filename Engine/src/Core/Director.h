#pragma once

namespace stick2d {
    class Scene;
    class Layer;
    class Director;
    class Application;
    class Window;

    class Director
    {
    public:
        friend Director* theDirector();
        void runWithScene(Scene* scene);
        void replaceScene(Scene* scene);
        void pushScene(Scene* scene);
        void popScene();
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);
        void setResolution(int width, int height);
        void setFullScreen(bool fullScreen);
        void clearScreen();
        void updateScreen();

    private:
        Director();
        ~Director();
        Application* m_app;
        Window* m_window;
    };

    extern Director* theDirector();
}