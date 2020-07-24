#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace stick2d {

    struct AppConfiguration
    {
        std::string windowTitle = "";
        std::string windowIconFilename = "";
        std::string logFile;
        std::string dataPath;
        glm::uvec2 resolution = { 800, 600 };
        bool isFullscreen = false;
        bool isResizable = false;
        glm::u8vec3 color;
    };
}