#pragma once

#include "flappy/Bird.hpp"
#include "flappy/State.hpp"

namespace flappy {

class MenuState : public State {
public:
    MenuState(StateMachine& machine, Context context);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;

private:
    Bird  bird_;
    float blinkTimer_ = 0.f;
};

} // namespace flappy
