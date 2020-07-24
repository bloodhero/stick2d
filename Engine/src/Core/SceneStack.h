#pragma once

#include <vector>

namespace stick2d {
    class Scene;


    class SceneStack
    {
    public:
        SceneStack() = default;
        ~SceneStack();
        void runWithScene(Scene* scene);
        void replaceScene(Scene* scene);
        void pushScene(Scene* scene);
        void popScene();
        Scene* getCurrentScene();
    private:
        std::vector<Scene*> m_Scenes;
    };
}