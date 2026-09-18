#pragma once

#include "flappy/State.hpp"

#include <memory>
#include <vector>

namespace flappy {

// 栈式状态机：GameOver 压在 Play 之上，所以结束画面背后仍能看到最后一帧。
// 只有栈顶接收输入与更新，整个栈都会被绘制。
class StateMachine {
public:
    explicit StateMachine(Context context);

    void push(StateID id);
    void pop();
    void clear();

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderTarget& target) const;

    bool isEmpty() const { return stack_.empty(); }

private:
    enum class Action { Push, Pop, Clear };

    struct PendingChange {
        Action  action;
        StateID id = StateID::Menu;
    };

    std::unique_ptr<State> createState(StateID id);
    void applyPendingChanges();

    Context context_;
    std::vector<std::unique_ptr<State>> stack_;
    std::vector<PendingChange>          pending_;
};

} // namespace flappy
