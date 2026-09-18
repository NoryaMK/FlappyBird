#include "flappy/ResourceManager.hpp"

#include <fstream>

namespace flappy {

ResourceManager::ResourceManager()
{
    // 优先使用仓库内的字体，其次退化到常见的系统字体路径。
    fontLoaded_ = tryLoadFont({
        "assets/fonts/game.ttf",
        "../assets/fonts/game.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/Library/Fonts/Arial.ttf",
        "/System/Library/Fonts/Supplemental/Arial.ttf",
        "C:/Windows/Fonts/arial.ttf",
    });
}

bool ResourceManager::tryLoadFont(const std::vector<std::string>& candidates)
{
    for (const auto& path : candidates) {
        // 先确认文件存在，避免 SFML 在控制台打印一堆加载失败的告警。
        std::ifstream probe(path, std::ios::binary);
        if (!probe) {
            continue;
        }
        if (font_.loadFromFile(path)) {
            return true;
        }
    }
    return false;
}

} // namespace flappy
