#include "pch.h"

#include "Core/Director.h"
#include "Core/Scene.h"
#include "Core/SceneStack.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Core/Application.h"
#include "Core/Window.h"

namespace stick2d {
    Director::Director()
        :m_app(theApplication()),
        m_window(theWindow())
    {

    }


    Director::~Director()
    {

    }

    Director* theDirector()
    {
        static Director instance;
        return &instance;
    }

    void Director::runWithScene(Scene* scene)
    {
        m_app->getSceneStack()->runWithScene(scene);
    }

    void Director::replaceScene(Scene* scene)
    {
        m_app->getSceneStack()->replaceScene(scene);
    }

    void Director::pushScene(Scene* scene)
    {
        m_app->getSceneStack()->pushScene(scene);
    }

    void Director::popScene()
    {
        m_app->getSceneStack()->popScene();
    }

    void Director::PushLayer(Layer* layer)
    {
        m_app->getSceneStack()->getCurrentScene()->getLayerStack()->PushLayer(layer);
    }

    void Director::PushOverlay(Layer* overlay)
    {
        m_app->getSceneStack()->getCurrentScene()->getLayerStack()->PushOverlay(overlay);
    }

    void Director::PopLayer(Layer* layer)
    {
        m_app->getSceneStack()->getCurrentScene()->getLayerStack()->PopLayer(layer);
    }

    void Director::PopOverlay(Layer* overlay)
    {
        m_app->getSceneStack()->getCurrentScene()->getLayerStack()->PopOverlay(overlay);
    }

    void Director::setResolution(int width, int height)
    {
        m_window->setResolution({ width, height });
    }

    void Director::setFullScreen(bool fullScreen)
    {
        m_window->setFullscreen(fullScreen);
    }

    void Director::clearScreen()
    {
        m_window->clearScreen();
    }

    void Director::updateScreen()
    {
        m_window->updateScreen();
    }

}