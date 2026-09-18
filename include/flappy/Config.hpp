#pragma once

// 所有可调参数集中在这里，便于调整手感，避免魔法数字散落在各个类中。
namespace flappy::config {

// 窗口
inline constexpr unsigned int WindowWidth  = 480;
inline constexpr unsigned int WindowHeight = 640;
inline constexpr const char*  WindowTitle  = "Flappy Bird - C++/SFML";
inline constexpr unsigned int FrameRate    = 60;

// 地面
inline constexpr float GroundHeight = 96.f;
inline constexpr float GroundY      = static_cast<float>(WindowHeight) - GroundHeight;

// 小鸟
inline constexpr float BirdX          = 120.f;
inline constexpr float BirdRadius     = 16.f;
inline constexpr float Gravity        = 1700.f;   // px / s^2
inline constexpr float FlapVelocity   = -480.f;   // px / s
inline constexpr float MaxFallSpeed   = 900.f;    // px / s
inline constexpr float MaxRotation    = 70.f;     // 角度
inline constexpr float MinRotation    = -25.f;    // 角度

// 管道
inline constexpr float PipeWidth         = 70.f;
inline constexpr float PipeGap           = 160.f;
inline constexpr float PipeSpeed         = 180.f; // px / s
inline constexpr float PipeSpawnInterval = 1.45f; // 秒
inline constexpr float PipeMinTop        = 70.f;  // 上管道最小长度
inline constexpr float PipeMinBottom     = 90.f;  // 下管道最小长度

// 背景滚动
inline constexpr float GroundScrollSpeed = PipeSpeed;
inline constexpr float CloudScrollSpeed  = 22.f;

// 存档
inline constexpr const char* HighScoreFile = "highscore.dat";

} // namespace flappy::config
