#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <unordered_map>

#include "config_layout.hpp"
#include "layout_base.hpp"
#include "main_layout.hpp"

enum class Layouts { MAIN, CONFIG };

inline std::unordered_map<Layouts, std::unique_ptr<LayoutBase> >
    layouts;

inline LayoutBase* layout;

inline void set_layout(Layouts _layout) {
    layout = layouts[_layout].get();
}

inline void make_layouts(
    sf::Font* font,
    sf::Vector2u window_size,
    sf::RenderWindow* window,
    std::function<Result(std::string)> callback) {
    layouts.emplace(Layouts::MAIN,
                    std::make_unique<Layout>(
                        font, window_size, window, callback));

    layouts.emplace(
        Layouts::CONFIG,
        std::make_unique<ConfigLayout>(font, window_size, window));
}
