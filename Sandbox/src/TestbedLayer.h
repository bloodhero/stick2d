#pragma once
#include "stick2d.h"
#include <entt/entt.hpp>

namespace stick2d {
    class TestbedLayer :public Layer
    {
    public:
        TestbedLayer();
        ~TestbedLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onDraw() override;
        virtual void onUpdate(Timestep& ts) override;
        virtual void onEvent(Event& event) override;
    private:
        entt::registry m_registry;
    };
}