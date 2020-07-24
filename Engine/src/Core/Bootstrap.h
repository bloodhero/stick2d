#pragma once


namespace stick2d {
    struct AppConfiguration;
    class Scene;

    class Bootstrap
    {
    public:
        virtual ~Bootstrap() = default;
        virtual void configApp(AppConfiguration* config) = 0;
        virtual Scene* firstScene() = 0;
        virtual void onInit() = 0;
        virtual void onShutdown() = 0;
    };

    // To be defined in CLIENT
    Bootstrap* createBootstrap();
}