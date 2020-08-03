#pragma once
#include <glm/glm.hpp>

namespace stick2d {
    class Pipeline
    {
    public:
        Pipeline() {  }
        void Scale(float ScaleX, float ScaleY, float ScaleZ) {  }
        void WorldPos(float x, float y, float z) {  }
        void Rotate(float RotateX, float RotateY, float RotateZ) {  }
        const glm::mat4* GetTrans();
    private:
        glm::vec3 m_scale;
        glm::vec3 m_worldPos;
        glm::vec3 m_rotateInfo;
        glm::vec3 m_transformation;
    };

    // 可以设置脏页和缓存，避免不需要的计算
}