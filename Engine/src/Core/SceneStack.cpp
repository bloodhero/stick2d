#include "pch.h"
#include "Core/SceneStack.h"
#include "Core/Scene.h"

namespace stick2d {
    SceneStack::~SceneStack()
    {
        for (auto s : m_Scenes)
        {
            s->onCleanup();
            delete s;
        }
    }

    void SceneStack::runWithScene(Scene* scene)
    {
        if (m_Scenes.size() == 0)
        {
            m_Scenes.push_back(scene);
            m_Scenes.back()->onInit();
        }

    }

    void SceneStack::replaceScene(Scene* scene)
    {
        // cleanup the current state
        if (!m_Scenes.empty())
        {
            m_Scenes.back()->onCleanup();
            m_Scenes.pop_back();
        }

        // store and init the new state
        m_Scenes.push_back(scene);
        m_Scenes.back()->onInit();
    }

    void SceneStack::pushScene(Scene* scene)
    {
        // pause current state
        if (!m_Scenes.empty())
        {
            m_Scenes.back()->onPause();
        }

        // store and init the new state
        m_Scenes.push_back(scene);
        m_Scenes.back()->onInit();
    }

    void SceneStack::popScene()
    {
        // cleanup the current state
        if (!m_Scenes.empty())
        {
            m_Scenes.back()->onCleanup();
            m_Scenes.pop_back();
        }

        // resume previous state
        if (!m_Scenes.empty())
        {
            m_Scenes.back()->onResume();
        }
    }

    Scene* SceneStack::getCurrentScene()
    {
        return m_Scenes.back();
    }

}