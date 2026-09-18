#include "flappy/MenuState.hpp"

#include "flappy/Config.hpp"
#include "flappy/DigitRenderer.hpp"
#include "flappy/ScoreBoard.hpp"
#include "flappy/StateMachine.hpp"
#include "flappy/TextRenderer.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace flappy {

MenuState::MenuState(StateMachine& machine, Context context)
    : State(machine, context)
{
}

void MenuState::handleEvent(const sf::Event& event)
{
    const bool start =
        (event.type == sf::Event::KeyPressed &&
         (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)) ||
        (event.type == sf::Event::MouseButtonPressed &&
         event.mouseButton.button == sf::Mouse::Left);

    if (start) {
        machine_.clear();
        machine_.push(StateID::Play);
    }
}

void MenuState::update(float dt)
{
    bird_.updateIdle(dt);
    blinkTimer_ += dt;
}

void MenuState::draw(sf::RenderTarget& target) const
{
    TextRenderer::drawCentered(target, *context_.resources, "FLAPPY BIRD", 140.f, 48);
    TextRenderer::drawCentered(target, *context_.resources, "C++ / SFML", 190.f, 20,
                               sf::Color(255, 255, 255, 200));

    target.draw(bird_);

    if (std::fmod(blinkTimer_, 1.2f) < 0.8f) {
        TextRenderer::drawCentered(target, *context_.resources,
                                   "Press SPACE or Click to start", 400.f, 22);
    }

    TextRenderer::drawCentered(target, *context_.resources, "BEST", 470.f, 18,
                               sf::Color(255, 255, 255, 200));
    DigitRenderer::draw(target, context_.score->best(),
                        {config::WindowWidth / 2.f, 510.f}, 34.f);
}

} // namespace flappy
