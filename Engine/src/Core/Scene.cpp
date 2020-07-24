#include "pch.h"
#include "Core/Event.h"
#include "Core/Scene.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"


namespace stick2d {

    Scene::Scene(std::string_view name)
        :m_name(name),
        m_layerStack(new LayerStack())
    {

    }


    Scene::~Scene()
    {
        delete m_layerStack;
    }

    void Scene::onEvent(Event& e)
    {
        for (auto it = m_layerStack->rbegin(); it != m_layerStack->rend(); ++it)
        {
            if (e.handled)
                break;
            (*it)->onEvent(e);
        }
    }


    void Scene::onUpdate(Timestep& timestep)
    {
        for (Layer* layer : *m_layerStack)
            layer->onUpdate(timestep);
    }

    void Scene::onDraw()
    {
        for (auto it = m_layerStack->begin(); it != m_layerStack->end(); ++it)
        {
            (*it)->onDraw();
        }
    }

}