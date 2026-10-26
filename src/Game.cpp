#include "flappy/Game.hpp"

#include "flappy/Config.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>

namespace flappy {
    
Game::Game()
    : window_(sf::VideoMode(config::WindowWidth, config::WindowHeight),
              config::WindowTitle,
              sf::Style::Titlebar | sf::Style::Close)
    , states_(Context{&window_, &resources_, &scoreBoard_})
{
    window_.setFramerateLimit(config::FrameRate);
    states_.push(StateID::Menu);
}

void Game::run()
{
    sf::Clock clock;
    while (window_.isOpen()) {
        // 限制单帧步长，避免窗口拖动后出现“穿墙”。
        const float dt = std::min(clock.restart().asSeconds(), 0.05f);

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q &&
            event.key.control) {
            window_.close();
        }
        states_.handleEvent(event);
    }
}

void Game::update(float dt)
{
    background_.update(dt);
    states_.update(dt);

    if (states_.isEmpty()) {
        window_.close();
    }
}

void Game::render()
{
    window_.clear();
    window_.draw(background_);
    states_.draw(window_);
    window_.display();
}

} // namespace flappy
