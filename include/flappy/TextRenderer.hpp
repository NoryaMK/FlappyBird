#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

namespace flappy {

class ResourceManager;

// 文字绘制的统一入口。没有字体时自动退化为“画一个提示条”，
// 保证游戏在任何环境下都能跑起来。
class TextRenderer {
public:
    static void drawCentered(sf::RenderTarget& target,
                             const ResourceManager& resources,
                             const std::string& text,
                             float centerY,
                             unsigned int characterSize,
                             sf::Color color = sf::Color::White);

    static void drawPanel(sf::RenderTarget& target,
                          float centerY, float width, float height,
                          sf::Color fill = sf::Color(0, 0, 0, 110));
};

} // namespace flappy
