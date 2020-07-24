#include "stick2d.h"
#include "TestbedLayer.h"
#include <fstream>
#include <imgui.h>

namespace stick2d {


    TestbedLayer::TestbedLayer()
        :Layer("Testbed layer")
    {

    }

    TestbedLayer::~TestbedLayer()
    {

    }

    void TestbedLayer::onAttach()
    {

    }

    void TestbedLayer::onDetach()
    {

    }

    void TestbedLayer::onDraw()
    {

    }

    void TestbedLayer::onUpdate(Timestep& ts)
    {
        static bool show_demo_window = true;
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);



    }

    void TestbedLayer::onEvent(Event& event)
    {

    }

}