#include "ExampleScene.h"
#include "MyBootstrap.h"
#include "stick2d.h"

namespace stick2d {

    void MyBootstrap::configApp(AppConfiguration* config)
    {
        config->isFullscreen = false;
        config->isResizable = false;
        config->windowTitle = "Sandbox";
        config->windowIconFilename = "";
        config->resolution = { (20 * 18)*2 , (20 * 12)*2 };
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