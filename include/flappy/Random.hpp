#pragma once

namespace flappy {

// 单一职责：只负责随机数，方便将来替换成固定种子做回放/测试。
class Random {
public:
    static float uniform(float min, float max);
    static int   uniform(int min, int max);
    static void  seed(unsigned int value);
};

} // namespace flappy
