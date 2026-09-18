#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace flappy {

// 一对（上下）管道。自己负责移动、碰撞盒和绘制。
class Pipe : public sf::Drawable {
public:
    Pipe(float x, float gapCenterY);

    void update(float dt);

    sf::FloatRect topBounds() const;
    sf::FloatRect bottomBounds() const;

    float x() const { return x_; }
    float right() const;
    bool  isOffScreen() const;

    bool scored() const { return scored_; }
    void markScored() { scored_ = true; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float x_;
    float gapCenterY_;
    bool  scored_ = false;
};

} // namespace flappy
