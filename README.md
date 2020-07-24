# stick2d 游戏引擎
专注2d的游戏引擎。

依赖的库：
* entt
* ffmpeg
* glad
* glm
* imgui
* json
* nuklear
* openal-soft
* opengl 3.3
* SDL2
* stb_image
* spdlog

# 开始
推荐使用 Visual Studio 2019，本游戏主要发布在windos平台。

使用 git 克隆本仓库：

`git clone --recursive git@github.com:bloodhero/stick2d.git`

执行 scripts/Win-GenProjects.bat 生成工程文件

使用 vs2019 打开 stick2d.sln 即可。

# 开发原则
1. 能不重新造轮子就不重新造轮子

# 命名规范
- 类名 每个单词首字母大写，不包含下划线 MyEvent
- 函数命名 驼峰模式， 首字母小写 onClose
- 结构体成员变量 同函数命名 mouseButton
- 局部变量 一律小写, 单词之间用下划线连接. mouse_button
- 类成员变量 以 m_ 开头 m_mouse_button
- 静态成员变量 首字母大写 以 s_ 开头 s_mouse_button
- 常量、枚举、宏命名 全部大写，包含下划线 LOOP_ONCE
- 命名空间命名 小写 shark
- 文件名 使用类名规范

# 计划
1. 先做战旗游戏
2. 尝试做ARPG游戏
