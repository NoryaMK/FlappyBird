#include "flappy/Bird.hpp"

#include "flappy/Config.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <cmath>

namespace flappy {

Bird::Bird()
{
    reset();
}

void Bird::reset()
{
    position_  = {config::BirdX, config::WindowHeight * 0.42f};
    baseY_     = position_.y;
    velocity_  = 0.f;
    rotation_  = 0.f;
    idleTimer_ = 0.f;
}

void Bird::flap()
{
    velocity_ = config::FlapVelocity;
}

void Bird::update(float dt)
{
    velocity_ += config::Gravity * dt;
    velocity_  = std::min(velocity_, config::MaxFallSpeed);
    position_.y += velocity_ * dt;

    // 撞到天花板就停住，不允许飞出屏幕。
    if (position_.y < config::BirdRadius) {
        position_.y = config::BirdRadius;
        velocity_   = 0.f;
    }

    const float target = velocity_ < 0.f ? config::MinRotation : config::MaxRotation;
    const float speed  = velocity_ < 0.f ? 12.f : 4.f;
    rotation_ += (target - rotation_) * std::min(1.f, speed * dt);

    wingTimer_ += dt;
    if (wingTimer_ > 0.09f) {
        wingTimer_ = 0.f;
        wingFrame_ = (wingFrame_ + 1) % 3;
    }
}

void Bird::updateIdle(float dt)
{
    idleTimer_ += dt;
    position_.y = baseY_ + std::sin(idleTimer_ * 3.2f) * 10.f;
    rotation_   = std::sin(idleTimer_ * 3.2f) * 6.f;

    wingTimer_ += dt;
    if (wingTimer_ > 0.12f) {
        wingTimer_ = 0.f;
        wingFrame_ = (wingFrame_ + 1) % 3;
    }
}

sf::FloatRect Bird::getBounds() const
{
    // 碰撞盒略小于视觉大小，手感更宽容。
    const float r = config::BirdRadius * 0.86f;
    return {position_.x - r, position_.y - r, r * 2.f, r * 2.f};
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.translate(position_);
    states.transform.rotate(rotation_);

    const float r = config::BirdRadius;

    sf::CircleShape body(r);
    body.setOrigin(r, r);
    body.setFillColor(sf::Color(250, 208, 46));
    body.setOutlineThickness(2.f);
    body.setOutlineColor(sf::Color(70, 50, 10));
    target.draw(body, states);

    const float wingOffset = (wingFrame_ == 0 ? -4.f : (wingFrame_ == 1 ? 0.f : 4.f));
    sf::CircleShape wing(r * 0.45f);
    wing.setOrigin(r * 0.45f, r * 0.45f);
    wing.setScale(1.3f, 0.75f);
    wing.setPosition(-r * 0.25f, wingOffset);
    wing.setFillColor(sf::Color(240, 240, 240));
    wing.setOutlineThickness(1.5f);
    wing.setOutlineColor(sf::Color(70, 50, 10));
    target.draw(wing, states);

    sf::CircleShape eyeWhite(r * 0.32f);
    eyeWhite.setOrigin(r * 0.32f, r * 0.32f);
    eyeWhite.setPosition(r * 0.35f, -r * 0.35f);
    eyeWhite.setFillColor(sf::Color::White);
    eyeWhite.setOutlineThickness(1.f);
    eyeWhite.setOutlineColor(sf::Color(70, 50, 10));
    target.draw(eyeWhite, states);

    sf::CircleShape pupil(r * 0.13f);
    pupil.setOrigin(r * 0.13f, r * 0.13f);
    pupil.setPosition(r * 0.45f, -r * 0.35f);
    pupil.setFillColor(sf::Color(30, 30, 30));
    target.draw(pupil, states);

    sf::ConvexShape beak;
    beak.setPointCount(3);
    beak.setPoint(0, {r * 0.75f, -r * 0.05f});
    beak.setPoint(1, {r * 1.45f, r * 0.15f});
    beak.setPoint(2, {r * 0.75f, r * 0.35f});
    beak.setFillColor(sf::Color(235, 110, 40));
    beak.setOutlineThickness(1.5f);
    beak.setOutlineColor(sf::Color(70, 50, 10));
    target.draw(beak, states);
}

} // namespace flappy
