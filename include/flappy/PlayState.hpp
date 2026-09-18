#pragma once

#include "flappy/Bird.hpp"
#include "flappy/PipeManager.hpp"
#include "flappy/State.hpp"

namespace flappy {

class PlayState : public State {
public:
    PlayState(StateMachine& machine, Context context);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) const override;

private:
    void onFlap();
    void die();

    Bird        bird_;
    PipeManager pipes_;
    bool        started_ = false;   // 第一次点击之前不下落
    bool        dead_    = false;
};

} // namespace flappy
