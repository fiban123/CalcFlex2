#include "config_layout.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "gui_config.hpp"

void ConfigLayout::resize_update(sf::Vector2u size) {}

void ConfigLayout::text_entered(unsigned c) { s.text_entered(c); }

void ConfigLayout::move_cursor(bool sign) {}

void ConfigLayout::update(sf::Vector2i mouse_pos, bool left_click) {
    s.update(mouse_pos, left_click);
}

void ConfigLayout::draw(sf::RenderWindow& window) { s.draw(window); }

void ConfigLayout::update_click(sf::Vector2i mouse_pos) { s.update_click(mouse_pos); }

void ConfigLayout::update_scroll(sf::Vector2i mouse_pos, float delta) {}

ConfigLayout::ConfigLayout(sf::Font* font, sf::Vector2u window_size,
                           sf::RenderWindow* window)
    : LayoutBase(font, window_size, window) {
    // create style

    style = TextSettingStyle{
        40,
        40,
        10,
        {TEXT_COLOR, BLACK, OUTLINE_CONTRAST, 1, 10, 10, 23, font},
        {TEXT_COLOR, BUTTON_BG_COLOR, DIM_HIGHLIGHT_COLOR, 1, 10, 10, 20, font},
        {TEXT_COLOR,
         {TEXT_COLOR, BUTTON_BG_COLOR, OUTLINE_HIGHLIGHT_COLOR, 1, 10, 10, 30, font}},
        {BUTTON_BG_COLOR, BUTTON_HOVER_OUTLINE_COLOR, TEXT_COLOR, font, 1, 10, 22}};

    std::string label = "Result Representation Type [exact, float]";
    std::string setting = "float";
    std::string info =
        "if the representation type is exact, results\n"
        "will be displayed as exact, rational numbers\n"
        "if possible. if the representation type is\n"
        "float, results will always be displayed as\n"
        "sometimes imperfect, floating-point values.";

    s = TextSetting(label, setting, info, {50, 50}, &style, 200, false);
}
