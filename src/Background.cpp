#include "flappy/Background.hpp"

#include "flappy/Config.hpp"
#include "flappy/Random.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace flappy {

Background::Background()
{
    for (std::size_t i = 0; i < clouds_.size(); ++i) {
        clouds_[i].x     = Random::uniform(0.f, static_cast<float>(config::WindowWidth));
        clouds_[i].y     = Random::uniform(50.f, 260.f);
        clouds_[i].scale = Random::uniform(0.7f, 1.4f);
    }
}

void Background::update(float dt)
{
    if (!scrolling_) {
        return;
    }

    groundOffset_ += config::GroundScrollSpeed * dt;
    if (groundOffset_ > 40.f) {
        groundOffset_ -= 40.f;
    }

    for (auto& cloud : clouds_) {
        cloud.x -= config::CloudScrollSpeed * cloud.scale * dt;
        if (cloud.x < -120.f) {
            cloud.x     = static_cast<float>(config::WindowWidth) + 60.f;
            cloud.y     = Random::uniform(50.f, 260.f);
            cloud.scale = Random::uniform(0.7f, 1.4f);
        }
    }
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    const float w = static_cast<float>(config::WindowWidth);

    // 渐变天空
    sf::VertexArray sky(sf::TriangleStrip, 4);
    const sf::Color top(104, 194, 232);
    const sf::Color bottom(176, 226, 240);
    sky[0] = sf::Vertex({0.f, 0.f}, top);
    sky[1] = sf::Vertex({w, 0.f}, top);
    sky[2] = sf::Vertex({0.f, config::GroundY}, bottom);
    sky[3] = sf::Vertex({w, config::GroundY}, bottom);
    target.draw(sky, states);

    // 云
    for (const auto& cloud : clouds_) {
        const float r = 22.f * cloud.scale;
        for (int i = 0; i < 3; ++i) {
            sf::CircleShape puff(r * (i == 1 ? 1.25f : 1.f));
            puff.setOrigin(puff.getRadius(), puff.getRadius());
            puff.setPosition(cloud.x + static_cast<float>(i) * r * 1.1f, cloud.y);
            puff.setFillColor(sf::Color(255, 255, 255, 205));
            target.draw(puff, states);
        }
    }

    // 远处的矮树丛
    for (int i = -1; i < 10; ++i) {
        sf::CircleShape bush(34.f);
        bush.setOrigin(34.f, 34.f);
        bush.setPosition(static_cast<float>(i) * 62.f + 20.f, config::GroundY + 6.f);
        bush.setFillColor(sf::Color(126, 200, 106));
        target.draw(bush, states);
    }

    // 地面
    sf::RectangleShape ground({w, config::GroundHeight});
    ground.setPosition(0.f, config::GroundY);
    ground.setFillColor(sf::Color(222, 199, 129));
    target.draw(ground, states);

    sf::RectangleShape grass({w, 14.f});
    grass.setPosition(0.f, config::GroundY);
    grass.setFillColor(sf::Color(150, 212, 100));
    target.draw(grass, states);

    // 滚动的地面条纹
    for (int i = -1; i < static_cast<int>(w / 40.f) + 2; ++i) {
        sf::RectangleShape stripe({20.f, 10.f});
        stripe.setPosition(static_cast<float>(i) * 40.f - groundOffset_, config::GroundY + 20.f);
        stripe.setFillColor(sf::Color(206, 180, 112));
        target.draw(stripe, states);
    }
}

} // namespace flappy
