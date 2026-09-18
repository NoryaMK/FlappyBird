#include "flappy/PipeManager.hpp"

#include "flappy/Config.hpp"
#include "flappy/Random.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>

namespace flappy {

void PipeManager::reset()
{
    pipes_.clear();
    spawnTimer_ = 0.f;
    spawn();   // 开局先放一根，位置在屏幕右侧之外
}

void PipeManager::spawn()
{
    const float minCenter = config::PipeMinTop + config::PipeGap / 2.f;
    const float maxCenter = config::GroundY - config::PipeMinBottom - config::PipeGap / 2.f;
    const float center    = Random::uniform(minCenter, maxCenter);

    pipes_.emplace_back(static_cast<float>(config::WindowWidth) + 40.f, center);
}

void PipeManager::update(float dt)
{
    spawnTimer_ += dt;
    if (spawnTimer_ >= config::PipeSpawnInterval) {
        spawnTimer_ -= config::PipeSpawnInterval;
        spawn();
    }

    for (auto& pipe : pipes_) {
        pipe.update(dt);
    }

    pipes_.erase(std::remove_if(pipes_.begin(), pipes_.end(),
                                [](const Pipe& p) { return p.isOffScreen(); }),
                 pipes_.end());
}

int PipeManager::consumeScore(float birdX)
{
    int gained = 0;
    for (auto& pipe : pipes_) {
        if (!pipe.scored() && pipe.right() < birdX) {
            pipe.markScored();
            ++gained;
        }
    }
    return gained;
}

bool PipeManager::collides(const sf::FloatRect& bounds) const
{
    for (const auto& pipe : pipes_) {
        if (bounds.intersects(pipe.topBounds()) || bounds.intersects(pipe.bottomBounds())) {
            return true;
        }
    }
    return false;
}

void PipeManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& pipe : pipes_) {
        target.draw(pipe, states);
    }
}

} // namespace flappy
