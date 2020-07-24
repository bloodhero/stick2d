#pragma once
#include "stick2d.h"

namespace stick2d {
    class ExampleScene :public Scene
    {
    public:
        ExampleScene();
        ~ExampleScene();
        virtual void onInit() override;
        virtual void onCleanup() override;
        virtual void onPause() override;
        virtual void onResume() override;
    private:

    };
}