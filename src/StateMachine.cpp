#include "flappy/StateMachine.hpp"

#include "flappy/GameOverState.hpp"
#include "flappy/MenuState.hpp"
#include "flappy/PlayState.hpp"

namespace flappy {

StateMachine::StateMachine(Context context)
    : context_(context)
{
}

std::unique_ptr<State> StateMachine::createState(StateID id)
{
    switch (id) {
        case StateID::Menu:     return std::make_unique<MenuState>(*this, context_);
        case StateID::Play:     return std::make_unique<PlayState>(*this, context_);
        case StateID::GameOver: return std::make_unique<GameOverState>(*this, context_);
    }
    return nullptr;
}

void StateMachine::push(StateID id)  { pending_.push_back({Action::Push, id}); }
void StateMachine::pop()             { pending_.push_back({Action::Pop}); }
void StateMachine::clear()           { pending_.push_back({Action::Clear}); }

void StateMachine::handleEvent(const sf::Event& event)
{
    if (!stack_.empty()) {
        stack_.back()->handleEvent(event);
    }
    applyPendingChanges();
}

void StateMachine::update(float dt)
{
    if (!stack_.empty()) {
        stack_.back()->update(dt);
    }
    applyPendingChanges();
}

void StateMachine::draw(sf::RenderTarget& target) const
{
    for (const auto& state : stack_) {
        state->draw(target);
    }
}

void StateMachine::applyPendingChanges()
{
    // 先复制再清空：状态构造函数里可能又提交了新的请求。
    const auto changes = pending_;
    pending_.clear();

    for (const auto& change : changes) {
        switch (change.action) {
            case Action::Push:
                stack_.push_back(createState(change.id));
                break;
            case Action::Pop:
                if (!stack_.empty()) stack_.pop_back();
                break;
            case Action::Clear:
                stack_.clear();
                break;
        }
    }
}

} // namespace flappy
