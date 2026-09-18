#include "flappy/Pipe.hpp"

#include "flappy/Config.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace flappy {
namespace {

const sf::Color kPipeFill(86, 186, 74);
const sf::Color kPipeLight(132, 216, 110);
const sf::Color kPipeEdge(48, 110, 44);

void drawPipeBody(sf::RenderTarget& target, const sf::FloatRect& rect)
{
    sf::RectangleShape body({rect.width, rect.height});
    body.setPosition(rect.left, rect.top);
    body.setFillColor(kPipeFill);
    body.setOutlineThickness(2.f);
    body.setOutlineColor(kPipeEdge);
    target.draw(body);

    // 高光，做出一点立体感
    sf::RectangleShape highlight({rect.width * 0.22f, rect.height});
    highlight.setPosition(rect.left + rect.width * 0.14f, rect.top);
    highlight.setFillColor(kPipeLight);
    target.draw(highlight);
}

void drawPipeCap(sf::RenderTarget& target, float x, float y)
{
    const float capWidth  = config::PipeWidth + 10.f;
    const float capHeight = 24.f;

    sf::RectangleShape cap({capWidth, capHeight});
    cap.setPosition(x - 5.f, y);
    cap.setFillColor(kPipeFill);
    cap.setOutlineThickness(2.f);
    cap.setOutlineColor(kPipeEdge);
    target.draw(cap);

    sf::RectangleShape highlight({capWidth * 0.2f, capHeight});
    highlight.setPosition(x - 5.f + capWidth * 0.14f, y);
    highlight.setFillColor(kPipeLight);
    target.draw(highlight);
}

} // namespace

Pipe::Pipe(float x, float gapCenterY)
    : x_(x), gapCenterY_(gapCenterY)
{
}

void Pipe::update(float dt)
{
    x_ -= config::PipeSpeed * dt;
}

float Pipe::right() const
{
    return x_ + config::PipeWidth;
}

bool Pipe::isOffScreen() const
{
    return right() < -20.f;
}

sf::FloatRect Pipe::topBounds() const
{
    const float height = gapCenterY_ - config::PipeGap / 2.f;
    return {x_, 0.f, config::PipeWidth, height};
}

sf::FloatRect Pipe::bottomBounds() const
{
    const float top = gapCenterY_ + config::PipeGap / 2.f;
    return {x_, top, config::PipeWidth, config::GroundY - top};
}

void Pipe::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    const sf::FloatRect top    = topBounds();
    const sf::FloatRect bottom = bottomBounds();

    drawPipeBody(target, top);
    drawPipeBody(target, bottom);
    drawPipeCap(target, x_, top.top + top.height - 24.f);
    drawPipeCap(target, x_, bottom.top);
}

} // namespace flappy
