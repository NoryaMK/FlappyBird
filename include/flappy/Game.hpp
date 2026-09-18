#pragma once

#include "flappy/Background.hpp"
#include "flappy/ResourceManager.hpp"
#include "flappy/ScoreBoard.hpp"
#include "flappy/StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace flappy {

// 只负责主循环：事件 -> 更新 -> 渲染，以及持有各个子系统。
class Game {
public:
    Game();

    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window_;
    ResourceManager  resources_;
    ScoreBoard       scoreBoard_;
    Background       background_;
    StateMachine     states_;
};

} // namespace flappy
