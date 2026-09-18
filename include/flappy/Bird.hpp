#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace flappy {

// 只关心“一只鸟的物理与外观”，不知道管道、分数或游戏状态的存在。
class Bird : public sf::Drawable {
public:
    Bird();

    void reset();
    void flap();
    void update(float dt);
    void updateIdle(float dt);   // 菜单里上下浮动

    sf::FloatRect getBounds() const;
    sf::Vector2f  getPosition() const { return position_; }
    float         getVelocity() const { return velocity_; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f position_;
    float velocity_   = 0.f;
    float rotation_   = 0.f;
    float wingTimer_  = 0.f;
    int   wingFrame_  = 0;
    float idleTimer_  = 0.f;
    float baseY_      = 0.f;
};

} // namespace flappy
