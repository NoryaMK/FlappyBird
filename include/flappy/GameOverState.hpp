#pragma once

#include "flappy/State.hpp"

namespace flappy {

class GameOverState : public State {
public:
    GameOverState(StateMachine& machine, Context context);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;

private:
    float elapsed_ = 0.f;   // 短暂延迟，防止玩家误触立刻重开
};

} // namespace flappy
