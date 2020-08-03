#include "ExampleScene.h"
#include "MyBootstrap.h"
#include "stick2d.h"

namespace stick2d {

    void MyBootstrap::configApp(app_configuration* config)
    {
        config->isFullscreen = false;
        config->isResizable = true;
        config->windowTitle = "Sandbox";
        config->windowIconFilename = "";
        config->resolution = { 1280, 720};
    }

    Scene* MyBootstrap::firstScene()
    {
        return new ExampleScene();
    }

    void MyBootstrap::onInit()
    {

    }

    void MyBootstrap::onShutdown()
    {

    }

}