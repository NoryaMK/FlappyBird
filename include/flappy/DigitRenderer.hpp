#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

namespace flappy {

// 用矩形拼出七段数码管风格的数字，使游戏在没有字体文件时也能显示分数。
class DigitRenderer {
public:
    static void draw(sf::RenderTarget& target,
                     int number,
                     sf::Vector2f center,
                     float digitHeight,
                     sf::Color color = sf::Color::White);

    static float measureWidth(int number, float digitHeight);
};

} // namespace flappy
