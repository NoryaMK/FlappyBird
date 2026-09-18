# Flappy Bird (C++ / SFML)

用现代 C++17 + SFML 2.6 写的 Flappy Bird 复刻版。代码按职责拆成独立的类，
没有任何二进制素材依赖（小鸟、管道、背景全部由图形绘制），克隆下来就能编译运行。

```
+-----------------------------+
|        FLAPPY BIRD          |
|                             |
|      ( >  ← 小鸟             |
|   ▮▮        ▮▮              |
|   ▮▮        ▮▮              |
|  Press SPACE to start       |
+-----------------------------+
```

## 特性

- 纯代码绘制：不需要下载贴图，仓库里没有任何图片资源
- 栈式状态机：菜单 / 游戏中 / 结束 三个状态相互独立，结束界面能看到最后一帧
- 最高分本地存档（`highscore.dat`）
- 帧率无关的物理（按 `dt` 积分），并限制单帧步长防止穿模
- 字体可选：找不到字体时分数用内置七段数码管绘制，游戏照常运行
- 跨平台：Linux / macOS / Windows，附带 GitHub Actions 三平台构建

## 操作

| 按键 | 作用 |
| --- | --- |
| `空格` / `↑` / 鼠标左键 | 起飞、扇翅膀、重新开始 |
| `R` | 结束界面重开一局 |
| `Esc` | 结束界面返回主菜单 |
| `Ctrl + Q` | 退出游戏 |

## 目录结构

```
flappybird-cpp/
├── CMakeLists.txt              # 构建脚本（本地找不到 SFML 会自动下载）
├── README.md
├── LICENSE
├── .gitignore
├── .github/
│   └── workflows/
│       └── build.yml           # CI：Linux / Windows / macOS 编译验证
├── assets/
│   └── fonts/
│       └── README.md           # 放置可选字体的说明
├── include/
│   └── flappy/
│       ├── Config.hpp          # 所有可调参数（重力、间隙、速度……）
│       ├── Random.hpp          # 随机数封装
│       ├── ResourceManager.hpp # 资源（字体）加载
│       ├── TextRenderer.hpp    # 文字绘制入口，无字体时自动降级
│       ├── DigitRenderer.hpp   # 七段数码管风格的数字
│       ├── ScoreBoard.hpp      # 当前分 / 最高分 + 存档
│       ├── Bird.hpp            # 小鸟：物理 + 外观
│       ├── Pipe.hpp            # 单对管道
│       ├── PipeManager.hpp     # 管道生成、回收、碰撞查询
│       ├── Background.hpp      # 天空、云、滚动地面
│       ├── State.hpp           # 状态基类 + 共享 Context
│       ├── StateMachine.hpp    # 栈式状态机
│       ├── MenuState.hpp
│       ├── PlayState.hpp
│       ├── GameOverState.hpp
│       └── Game.hpp            # 主循环与子系统持有
└── src/
    ├── main.cpp
    ├── Game.cpp
    ├── StateMachine.cpp
    ├── MenuState.cpp
    ├── PlayState.cpp
    ├── GameOverState.cpp
    ├── Bird.cpp
    ├── Pipe.cpp
    ├── PipeManager.cpp
    ├── Background.cpp
    ├── ScoreBoard.cpp
    ├── DigitRenderer.cpp
    ├── TextRenderer.cpp
    ├── ResourceManager.cpp
    └── Random.cpp
```

## 编译运行

需要 CMake ≥ 3.16 和支持 C++17 的编译器。

```bash
git clone https://github.com/<your-name>/flappybird-cpp.git
cd flappybird-cpp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/bin/flappybird
```

如果系统里没有安装 SFML，CMake 会自动从 GitHub 拉取 SFML 2.6.2 并一起编译
（首次构建会慢一些）。想禁用这个行为：`cmake -B build -DFLAPPY_FETCH_SFML=OFF`。

### 各平台的 SFML 依赖

**Ubuntu / Debian**

```bash
sudo apt-get install build-essential cmake libsfml-dev
```

**macOS**

```bash
brew install cmake sfml
```

**Windows**

推荐 Visual Studio 2019/2022 + CMake，直接用默认配置即可（SFML 会被自动下载编译）：

```powershell
cmake -B build
cmake --build build --config Release
.\build\bin\Release\flappybird.exe
```

## 设计说明

每个类只负责一件事，互相之间尽量不认识对方，方便单独修改或替换：

- **Bird** 只知道自己的速度、位置和长什么样，完全不知道管道和分数的存在。
- **Pipe / PipeManager** 只提供 `collides(bounds)` 和 `consumeScore(x)` 两个查询接口，
  不关心撞上来的是谁。
- **PlayState** 是唯一把两者撮合起来的地方 —— 玩法规则集中在这一个文件里。
- **StateMachine** 用栈管理状态：只有栈顶接收输入和更新，但整个栈都会被绘制，
  所以 `GameOverState` 压上去之后，背后仍是死亡瞬间的画面。
- **Config.hpp** 收纳了所有数值常量。想改手感（重力、间隙宽度、管道速度）
  只需要动这一个文件，不必在各个 cpp 里翻找魔法数字。
- **ScoreBoard / ResourceManager / Random** 都是可以单独拿去别的项目复用的小工具。

数据流大致是：

```
main → Game（窗口 + 主循环）
         ├── Background      每帧更新、最先绘制
         └── StateMachine    ── MenuState
                             ── PlayState   ── Bird
                             │               └── PipeManager ── Pipe
                             └── GameOverState
             共享 Context { window, ResourceManager, ScoreBoard }
```

## 可以继续做的事

- 加音效：SFML 的 `sfml-audio` 模块，在 `ResourceManager` 里加 `SoundBuffer` 缓存即可
- 换皮：把 `Bird::draw` / `Pipe::draw` 里的图形换成 `sf::Sprite`，其余代码不用动
- 难度曲线：在 `PipeManager` 里让 `PipeGap` 随分数递减
- 单元测试：`PipeManager`、`ScoreBoard` 不依赖窗口，可以直接用 Catch2 / GoogleTest 测
- 录像回放：`Random::seed()` 已经预留了固定种子的接口

## 许可证

MIT，见 [LICENSE](LICENSE)。把文件里的 `<Your Name>` 换成你自己的名字。
Flappy Bird 原作归 Dong Nguyen / .GEARS 所有，本项目仅为学习用途的复刻。
