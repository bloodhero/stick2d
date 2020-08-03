#pragma once


namespace stick2d {
    struct app_configuration;
    class Scene;

    class Bootstrap
    {
    public:
        virtual ~Bootstrap() = default;
        virtual void configApp(app_configuration* config) = 0;
        virtual Scene* firstScene() = 0;
        virtual void onInit() = 0;
        virtual void onShutdown() = 0;
    };

    // To be defined in CLIENT
    Bootstrap* createBootstrap();
}