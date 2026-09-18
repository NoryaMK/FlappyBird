#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <array>

namespace flappy {

// 天空、云和滚动的地面。纯装饰，不参与玩法逻辑（地面碰撞在 Config 中定义）。
class Background : public sf::Drawable {
public:
    Background();

    void update(float dt);
    void setScrolling(bool scrolling) { scrolling_ = scrolling; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Cloud {
        float x = 0.f;
        float y = 0.f;
        float scale = 1.f;
    };

    std::array<Cloud, 4> clouds_{};
    float groundOffset_ = 0.f;
    bool  scrolling_    = true;
};

} // namespace flappy
