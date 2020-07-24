#pragma once
#include "stick2d.h"

namespace stick2d {
    class MyBootstrap :public Bootstrap
    {
    public:
        virtual void configApp(AppConfiguration* config) override;
        virtual Scene* firstScene() override;
        virtual void onInit() override;
        virtual void onShutdown() override;
    };
}