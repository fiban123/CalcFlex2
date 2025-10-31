#include "config_layout.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "gui_config.hpp"

void ConfigLayout::resize_update(sf::Vector2u size) {}

void ConfigLayout::text_entered(unsigned c) {}

void ConfigLayout::move_cursor(bool sign) {}

void ConfigLayout::update(sf::Vector2i mouse_pos, bool left_click) {}

void ConfigLayout::draw(sf::RenderWindow& window) { s.draw(window); }

void ConfigLayout::update_click(sf::Vector2i mouse_pos) {}

void ConfigLayout::update_scroll(sf::Vector2i mouse_pos, float delta) {}

ConfigLayout::ConfigLayout(sf::Font* font, sf::Vector2u window_size,
                           sf::RenderWindow* window)
    : LayoutBase(font, window_size, window) {
    // create style

    style = TextSettingStyle{
        30,
        {200, 30},
        10,
        {TEXT_COLOR, BUTTON_BG_COLOR, 10, 10, 20, font},
        {TEXT_COLOR, BUTTON_BG_COLOR, 10, 10, 16, font},
        {TEXT_COLOR, BUTTON_BG_COLOR, TEXT_COLOR, 10, 20, font},
        {BUTTON_BG_COLOR, BUTTON_HOVER_OUTLINE_COLOR, BUTTON_PRESS_BG_COLOR, font, 16}};
    std::string label = "sjdsjd";
    std::string setting = "kkkkkkkkkk";
    std::string info = "oooooooooooooo\noo";

    s = TextSetting(label, setting, info, {50, 50}, &style);
}
