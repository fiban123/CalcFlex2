#include "result_bar.hpp"

#include <iostream>

#include "gui_config.hpp"

void ResultBar::draw() { text_area.draw(*window); }

void ResultBar::resize_update() {
    text_area.resize({window_size->x - 2.f * SPACING, RESULT_BAR_HEIGHT});
}

void ResultBar::set_string(std::string string) {
    text_area.string = string;
    text_area.update_text();
}

ResultBar::ResultBar(sf::RenderWindow* _window, sf::Vector2u* _window_size,
                     sf::Font* _font)
    : window(_window), window_size(_window_size), font(_font) {
    text_area_style = TextAreaStyle{.text_color = TEXT_COLOR,
                                    .bg_color = INFO_BAR_BG_COLOR,
                                    .spacing = SPACING,
                                    .font_size = RESULT_BAR_FONT_SIZE,
                                    .font = font};

    text_area = TextArea("", {SPACING, RESULT_BAR_TOP_OFFSET},
                         {window_size->x - 2.f * SPACING, RESULT_BAR_HEIGHT},
                         &text_area_style, XBound::RIGHT, YBound::CENTER);
}
