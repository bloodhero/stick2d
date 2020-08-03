#include "stick2d.h"
#include "TestbedLayer.h"

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
        auto a = new MixChunk("data/M1.SAF_b16_r22050_c1_0.raw.wav");
        auto b = new MixChunk("data/M1.SAF_b16_r22050_c1_1.raw.wav");
        auto c = new MixChunk("data/M2.SAF_b16_r22050_c1_0.raw.wav");
        auto d = new MixChunk("data/M2.SAF_b16_r22050_c1_1.raw.wav");
        auto e = new MixChunk("data/M2.SAF_b16_r22050_c1_2.raw.wav");
        auto f = new MixChunk("data/M2.SAF_b16_r22050_c1_3.raw.wav");

        auto m = new MixChunk("data/Music_00.mp3");

        theDirector()->playMUS(m, false);
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