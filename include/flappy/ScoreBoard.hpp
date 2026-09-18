#pragma once

namespace flappy {

// 负责当前分数与最高分的读写，与渲染、玩法完全解耦。
class ScoreBoard {
public:
    ScoreBoard();

    void add(int delta = 1);
    void reset();

    int current() const { return current_; }
    int best() const { return best_; }
    bool isNewRecord() const { return newRecord_; }

    void load();
    void save() const;

private:
    int  current_   = 0;
    int  best_      = 0;
    bool newRecord_ = false;
};

} // namespace flappy
