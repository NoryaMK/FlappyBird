#pragma once

#include <SFML/Window/Event.hpp>

namespace sf { class RenderTarget; class RenderWindow; }

namespace flappy {

class StateMachine;
class ResourceManager;
class ScoreBoard;

// 各状态共享的“上下文”，避免使用全局变量。
struct Context {
    sf::RenderWindow* window    = nullptr;
    ResourceManager*  resources = nullptr;
    ScoreBoard*       score     = nullptr;
};

enum class StateID { Menu, Play, GameOver };

// 状态基类：菜单 / 游戏中 / 结束 都只实现这三个接口。
class State {
public:
    State(StateMachine& machine, Context context)
        : machine_(machine), context_(context) {}

    virtual ~State() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderTarget& target) const = 0;

protected:
    StateMachine& machine_;
    Context       context_;
};

} // namespace flappy
