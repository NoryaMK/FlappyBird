#pragma once

#include "flappy/Pipe.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace flappy {

// 管理管道的生成、回收与碰撞查询。Bird 与 PipeManager 互不依赖，
// 由 PlayState 负责把两者撮合在一起。
class PipeManager : public sf::Drawable {
public:
    void reset();
    void update(float dt);

    // 返回本帧新通过的管道数量（用于加分）。
    int consumeScore(float birdX);

    bool collides(const sf::FloatRect& bounds) const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void spawn();

    std::vector<Pipe> pipes_;
    float spawnTimer_ = 0.f;
};

} // namespace flappy
