#include "stick2d.h"
#include "ExampleScene.h"
#include "TestbedLayer.h"
namespace stick2d {

    ExampleScene::ExampleScene()
        :Scene("Example Scene")
    {

    }

    ExampleScene::~ExampleScene()
    {
        LOG_TRACE("scene exit....");
    }

    void ExampleScene::onInit()
    {
        LOG_TRACE("scene init....");
        theDirector()->PushLayer(new TestbedLayer());
    }

    void ExampleScene::onCleanup()
    {
        LOG_TRACE("scene cleanup...");
    }

    void ExampleScene::onPause()
    {
        LOG_TRACE("scene pause...");
    }

    void ExampleScene::onResume()
    {
        LOG_TRACE("resume");
    }

}