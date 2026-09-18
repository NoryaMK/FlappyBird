#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <vector>

namespace flappy {

// 资源加载与持有。字体是可选的：找不到字体时游戏仍可运行，
// 文字由 DigitRenderer / 图形代替，因此仓库不需要附带任何二进制资源。
class ResourceManager {
public:
    ResourceManager();

    bool hasFont() const { return fontLoaded_; }
    const sf::Font& font() const { return font_; }

private:
    bool tryLoadFont(const std::vector<std::string>& candidates);

    sf::Font font_;
    bool     fontLoaded_ = false;
};

} // namespace flappy
