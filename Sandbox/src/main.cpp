#include "stick2d.h"
int main()
{
    stick2d::Logger::Init();
    LOG_CORE_INFO("hello,world {}", 2233);
    LOG_INFO("hello, world");
}