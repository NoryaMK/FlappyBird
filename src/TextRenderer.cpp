#include "flappy/TextRenderer.hpp"

#include "flappy/Config.hpp"
#include "flappy/ResourceManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace flappy {

void TextRenderer::drawCentered(sf::RenderTarget& target,
                                const ResourceManager& resources,
                                const std::string& text,
                                float centerY,
                                unsigned int characterSize,
                                sf::Color color)
{
    if (!resources.hasFont()) {
        // 没有字体：用一个简洁的横条代替文字，避免界面空白。
        const float width = static_cast<float>(text.size()) * characterSize * 0.42f;
        sf::RectangleShape bar({width, static_cast<float>(characterSize) * 0.28f});
        bar.setOrigin(width / 2.f, bar.getSize().y / 2.f);
        bar.setPosition(config::WindowWidth / 2.f, centerY);
        bar.setFillColor(sf::Color(color.r, color.g, color.b, 170));
        target.draw(bar);
        return;
    }

    sf::Text label(text, resources.font(), characterSize);
    label.setFillColor(color);
    label.setOutlineThickness(2.f);
    label.setOutlineColor(sf::Color(0, 0, 0, 160));

    const sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    label.setPosition(config::WindowWidth / 2.f, centerY);

    target.draw(label);
}

void TextRenderer::drawPanel(sf::RenderTarget& target,
                             float centerY, float width, float height, sf::Color fill)
{
    sf::RectangleShape panel({width, height});
    panel.setOrigin(width / 2.f, height / 2.f);
    panel.setPosition(config::WindowWidth / 2.f, centerY);
    panel.setFillColor(fill);
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(255, 255, 255, 60));
    target.draw(panel);
}

} // namespace flappy
