#pragma once


#include <string>

namespace stick2d {
    class Event;
    class LayerStack;
    class Timestep;
    class Director;

    class Scene
    {
    public:
        Scene(std::string_view name = "Scene");
        virtual ~Scene();
        virtual void onInit() = 0;
        virtual void onCleanup() = 0;
        virtual void onPause() = 0;
        virtual void onResume() = 0;
        void onEvent(Event& e);
        void onDraw();
        void onUpdate(Timestep& ts);
        friend class Director;

    protected:
        LayerStack* getLayerStack(){ return m_layerStack; }
        LayerStack* m_layerStack;
        std::string m_name;

    };
}