#include "expression_input.hpp"

#include <iostream>

#include "gui_config.hpp"

void ExpressionInput::draw() { text_input.draw(*window); }

void ExpressionInput::resize_update() {
    text_input.resize({window_size->x - 2.0f * SPACING, EXPRESSION_INPUT_HEIGHT});
}

void ExpressionInput::enter_unicode_char(unsigned c) { text_input.enter_unicode_char(c); }

void ExpressionInput::enter_text(std::string s, unsigned offset) {
    text_input.enter_text(s, offset);
}

void ExpressionInput::clear() {
    text_input.text_area.string = "";
    text_input.update_text();
}

void ExpressionInput::clear_entry() {
    if (text_input.text_area.string.empty()) {
        return;
    }

    size_t end_pos = text_input.cursor_string_index;
    size_t start_pos = text_input.cursor_string_index - 1;

    std::cout << end_pos << " " << text_input.text_area.string.size() << std::endl;

    if (std::isalnum(text_input.text_area.string[start_pos]) == 0) {
        std::cout << "sidjsdj" << std::endl;
    }
    else {
        while (std::isalnum(text_input.text_area.string[start_pos]) != 0) {
            start_pos--;
            if (start_pos == 0) {
                break;
            }
        }
        if (start_pos != 0) {
            start_pos++;
        }
    }

    text_input.text_area.string.erase(text_input.text_area.string.begin() + start_pos - 1,
                                      text_input.text_area.string.begin() + end_pos);
    size_t delta = end_pos - start_pos - 1;
    text_input.cursor_string_index -= delta;

    std::cout << end_pos << " " << start_pos << " " << delta << std::endl;
    text_input.update_text();
    text_input.update_cursor();
}

void ExpressionInput::remove(unsigned n) { text_input.remove(n); }

void ExpressionInput::move_cursor(bool sign) { text_input.move_cursor(sign); }

ExpressionInput::ExpressionInput(sf::RenderWindow* _window, sf::Vector2u* _window_size,
                                 sf::Font* _font)
    : window(_window), window_size(_window_size), font(_font) {
    text_input_style =
        TextInputStyle{.cursor_color = TEXT_COLOR,
                       .text_area_style = {.text_color = TEXT_COLOR,
                                           .bg_color = EXPRESSION_INPUT_BG_COLOR,
                                           .outline_color = BLACK,
                                           .outline_width = 0,
                                           .spacing = SPACING,
                                           .entry_spacing = SPACING,
                                           .font_size = EXPRESSION_INPUT_FONT_SIZE,
                                           .font = font}};

    text_input = TextInput("", {SPACING, EXPRESSION_INPUT_TOP_OFFSET},
                           {window_size->x - 2 * SPACING, EXPRESSION_INPUT_HEIGHT},
                           &text_input_style, true, XBound::RIGHT, YBound::CENTER);
}
