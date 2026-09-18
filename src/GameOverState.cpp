#include "flappy/GameOverState.hpp"

#include "flappy/Config.hpp"
#include "flappy/DigitRenderer.hpp"
#include "flappy/ScoreBoard.hpp"
#include "flappy/StateMachine.hpp"
#include "flappy/TextRenderer.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace flappy {

namespace {
constexpr float kInputDelay = 0.6f;
}

GameOverState::GameOverState(StateMachine& machine, Context context)
    : State(machine, context)
{
}

void GameOverState::handleEvent(const sf::Event& event)
{
    if (elapsed_ < kInputDelay) {
        return;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        machine_.clear();
        machine_.push(StateID::Menu);
        return;
    }

    const bool restart =
        (event.type == sf::Event::KeyPressed &&
         (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::R)) ||
        (event.type == sf::Event::MouseButtonPressed &&
         event.mouseButton.button == sf::Mouse::Left);

    if (restart) {
        machine_.clear();
        machine_.push(StateID::Play);
    }
}

void GameOverState::update(float dt)
{
    elapsed_ += dt;
}

void GameOverState::draw(sf::RenderTarget& target) const
{
    sf::RectangleShape veil({static_cast<float>(config::WindowWidth),
                             static_cast<float>(config::WindowHeight)});
    veil.setFillColor(sf::Color(0, 0, 0, 90));
    target.draw(veil);

    TextRenderer::drawPanel(target, 300.f, 300.f, 250.f);
    TextRenderer::drawCentered(target, *context_.resources, "GAME OVER", 210.f, 40);

    TextRenderer::drawCentered(target, *context_.resources, "SCORE", 258.f, 18,
                               sf::Color(255, 255, 255, 200));
    DigitRenderer::draw(target, context_.score->current(),
                        {config::WindowWidth / 2.f, 296.f}, 40.f);

    TextRenderer::drawCentered(target, *context_.resources,
                               context_.score->isNewRecord() ? "NEW BEST!" : "BEST",
                               344.f, 18, sf::Color(255, 230, 120));
    DigitRenderer::draw(target, context_.score->best(),
                        {config::WindowWidth / 2.f, 380.f}, 30.f);

    if (elapsed_ >= kInputDelay) {
        TextRenderer::drawCentered(target, *context_.resources,
                                   "SPACE / Click : retry", 470.f, 20);
        TextRenderer::drawCentered(target, *context_.resources,
                                   "ESC : menu", 500.f, 18,
                                   sf::Color(255, 255, 255, 190));
    }
}

} // namespace flappy
