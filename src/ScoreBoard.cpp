#include "flappy/ScoreBoard.hpp"

#include "flappy/Config.hpp"

#include <fstream>

namespace flappy {

ScoreBoard::ScoreBoard()
{
    load();
}

void ScoreBoard::add(int delta)
{
    current_ += delta;
    if (current_ > best_) {
        best_ = current_;
        newRecord_ = true;
        save();
    }
}

void ScoreBoard::reset()
{
    current_ = 0;
    newRecord_ = false;
}

void ScoreBoard::load()
{
    std::ifstream in(config::HighScoreFile);
    if (in) {
        int value = 0;
        if (in >> value && value >= 0) {
            best_ = value;
        }
    }
}

void ScoreBoard::save() const
{
    std::ofstream out(config::HighScoreFile, std::ios::trunc);
    if (out) {
        out << best_ << '\n';
    }
}

} // namespace flappy
