#include "flappy/PlayState.hpp"

#include "flappy/Config.hpp"
#include "flappy/DigitRenderer.hpp"
#include "flappy/ScoreBoard.hpp"
#include "flappy/StateMachine.hpp"
#include "flappy/TextRenderer.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace flappy {

PlayState::PlayState(StateMachine& machine, Context context)
    : State(machine, context)
{
    context_.score->reset();
    pipes_.reset();
}

void PlayState::handleEvent(const sf::Event& event)
{
    const bool flap =
        (event.type == sf::Event::KeyPressed &&
         (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)) ||
        (event.type == sf::Event::MouseButtonPressed &&
         event.mouseButton.button == sf::Mouse::Left);

    if (flap) {
        onFlap();
    }
}

void PlayState::onFlap()
{
    started_ = true;
    bird_.flap();
}

void PlayState::update(float dt)
{
    if (!started_) {
        bird_.updateIdle(dt);
        return;
    }

    bird_.update(dt);
    pipes_.update(dt);

    context_.score->add(pipes_.consumeScore(bird_.getPosition().x));

    const sf::FloatRect bounds = bird_.getBounds();
    const bool hitGround = bounds.top + bounds.height >= config::GroundY;

    if (hitGround || pipes_.collides(bounds)) {
        die();
    }
}

void PlayState::die()
{
    if (dead_) {
        return;
    }
    dead_ = true;
    machine_.push(StateID::GameOver);   // 压在本状态之上，画面保留最后一帧
}

void PlayState::draw(sf::RenderTarget& target) const
{
    target.draw(pipes_);
    target.draw(bird_);

    DigitRenderer::draw(target, context_.score->current(),
                        {config::WindowWidth / 2.f, 80.f}, 46.f);

    if (!started_) {
        TextRenderer::drawCentered(target, *context_.resources,
                                   "Tap to fly", 300.f, 24);
    }
}

} // namespace flappy
