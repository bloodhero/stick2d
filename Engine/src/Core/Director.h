#pragma once

namespace stick2d {
    class Scene;
    class Layer;
    class Director;
    class Application;
    class Window;
    class Audio;
    class MixChunk;

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
        void playSFX(MixChunk* sfx);
        void playMUS(MixChunk* mus, bool loop);

    private:
        Director();
        ~Director() = default;
        Application* m_app;
        Audio* m_audio;
    };

    extern Director* theDirector();
}