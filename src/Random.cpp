#include "flappy/Random.hpp"

#include <random>

namespace flappy {
namespace {

std::mt19937& engine()
{
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

} // namespace

float Random::uniform(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine());
}

int Random::uniform(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine());
}

void Random::seed(unsigned int value)
{
    engine().seed(value);
}

} // namespace flappy
