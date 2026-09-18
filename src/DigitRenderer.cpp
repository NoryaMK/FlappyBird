#include "flappy/DigitRenderer.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <array>
#include <vector>

namespace flappy {
namespace {

// 七段数码管：a b c d e f g
constexpr std::array<std::array<bool, 7>, 10> kSegments = {{
    {{true,  true,  true,  true,  true,  true,  false}}, // 0
    {{false, true,  true,  false, false, false, false}}, // 1
    {{true,  true,  false, true,  true,  false, true }}, // 2
    {{true,  true,  true,  true,  false, false, true }}, // 3
    {{false, true,  true,  false, false, true,  true }}, // 4
    {{true,  false, true,  true,  false, true,  true }}, // 5
    {{true,  false, true,  true,  true,  true,  true }}, // 6
    {{true,  true,  true,  false, false, false, false}}, // 7
    {{true,  true,  true,  true,  true,  true,  true }}, // 8
    {{true,  true,  true,  true,  false, true,  true }}, // 9
}};

std::vector<int> digitsOf(int number)
{
    std::vector<int> digits;
    if (number <= 0) {
        digits.push_back(0);
        return digits;
    }
    while (number > 0) {
        digits.insert(digits.begin(), number % 10);
        number /= 10;
    }
    return digits;
}

void drawDigit(sf::RenderTarget& target, int digit, float x, float y,
               float w, float h, float t, sf::Color color)
{
    const auto& seg = kSegments[static_cast<std::size_t>(digit)];
    const std::array<sf::FloatRect, 7> rects = {{
        {x,         y,             w, t},        // a
        {x + w - t, y,             t, h / 2.f},  // b
        {x + w - t, y + h / 2.f,   t, h / 2.f},  // c
        {x,         y + h - t,     w, t},        // d
        {x,         y + h / 2.f,   t, h / 2.f},  // e
        {x,         y,             t, h / 2.f},  // f
        {x,         y + h / 2.f - t / 2.f, w, t} // g
    }};

    for (std::size_t i = 0; i < rects.size(); ++i) {
        if (!seg[i]) continue;
        sf::RectangleShape shape({rects[i].width, rects[i].height});
        shape.setPosition(rects[i].left, rects[i].top);
        shape.setFillColor(color);
        target.draw(shape);
    }
}

} // namespace

float DigitRenderer::measureWidth(int number, float digitHeight)
{
    const auto digits = digitsOf(number);
    const float w = digitHeight * 0.62f;
    const float gap = digitHeight * 0.18f;
    return static_cast<float>(digits.size()) * w +
           static_cast<float>(digits.size() - 1) * gap;
}

void DigitRenderer::draw(sf::RenderTarget& target, int number,
                         sf::Vector2f center, float digitHeight, sf::Color color)
{
    const auto digits = digitsOf(number);
    const float w = digitHeight * 0.62f;
    const float gap = digitHeight * 0.18f;
    const float t = digitHeight * 0.16f;
    const float total = measureWidth(number, digitHeight);

    float x = center.x - total / 2.f;
    const float y = center.y - digitHeight / 2.f;

    for (int d : digits) {
        // 先画一层深色描边，保证在浅色背景上也清晰。
        drawDigit(target, d, x + 3.f, y + 3.f, w, digitHeight, t, sf::Color(0, 0, 0, 120));
        drawDigit(target, d, x, y, w, digitHeight, t, color);
        x += w + gap;
    }
}

} // namespace flappy
