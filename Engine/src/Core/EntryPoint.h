#pragma once

#include "Core/Application.h"
#include "Core/Bootstrap.h"


extern stick2d::Bootstrap* stick2d::createBootstrap();

int main(int argc, char** argv)
{
    auto app = stick2d::theApplication();
    return (app->start(stick2d::createBootstrap()));
}
