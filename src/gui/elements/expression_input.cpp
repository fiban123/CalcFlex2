#include "expression_input.hpp"

#include <iostream>

void ExpressionInput::draw() { text_input.draw(*window); }

void ExpressionInput::resize_update() { text_input.resize({window_size->x - 2.0f * SPACING, EXPRESSION_INPUT_HEIGHT}); }

void ExpressionInput::enter_unicode_char(unsigned c) { text_input.enter_unicode_char(c); }

void ExpressionInput::enter_text(std::string s, unsigned offset) { text_input.enter_text(s, offset); }

void ExpressionInput::clear() {
    text_input.string = "";
    text_input.update_text();
}

void ExpressionInput::clear_entry() {
    if (text_input.string.empty()) {
        return;
    }

    size_t end_pos = text_input.cursor_string_index;
    size_t start_pos = text_input.cursor_string_index - 1;

    std::cout << end_pos << " " << text_input.string.size() << std::endl;

    if (std::isalnum(text_input.string[start_pos]) == 0) {
        std::cout << "sidjsdj" << std::endl;
    }
    else {
        while (std::isalnum(text_input.string[start_pos]) != 0) {
            start_pos--;
            if (start_pos == 0) {
                break;
            }
        }
        if (start_pos != 0) {
            start_pos++;
        }
    }

    text_input.string.erase(text_input.string.begin() + start_pos, text_input.string.begin() + end_pos);
    size_t delta = end_pos - start_pos - 1;
    text_input.cursor_string_index -= delta;

    std::cout << end_pos << " " << start_pos << " " << delta << std::endl;
    text_input.update_text();
    text_input.update_cursor();
}

void ExpressionInput::remove(unsigned n) { text_input.remove(n); }

void ExpressionInput::move_cursor(bool sign) {
    ssize_t new_pos = sign ? text_input.cursor_string_index + 1 : text_input.cursor_string_index - 1;
    text_input.cursor_string_index = std::clamp(new_pos, 0ll, (ssize_t)text_input.string.length());

    text_input.update_cursor();
}

ExpressionInput::ExpressionInput(sf::RenderWindow* _window, sf::Vector2u* _window_size, sf::Font* _font)
    : window(_window), window_size(_window_size), font(_font) {
    text_input_style = TextInputStyle{.text_color = TEXT_COLOR,
                                      .bg_color = EXPRESSION_INPUT_BG_COLOR,
                                      .cursor_color = TEXT_COLOR,
                                      .spacing = SPACING,
                                      .font_size = EXPRESSION_INPUT_FONT_SIZE,
                                      .font = font};

    text_input = TextInput("", {SPACING, EXPRESSION_INPUT_TOP_OFFSET},
                           {window_size->x - 2 * SPACING, EXPRESSION_INPUT_HEIGHT}, &text_input_style);
}
