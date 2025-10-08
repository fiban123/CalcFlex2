#pragma once

#include "text_input.hpp"
#include "gui_config.hpp"

struct ExpressionInput{
    TextInput text_input;
    TextInputStyle text_input_style;

    sf::RenderWindow* window;
    sf::Vector2u* window_size;
    sf::Font* font;

    void draw();

    void resize_update();

    void enter_unicode_char(unsigned c);
    void enter_text(std::string s, unsigned offset);
    void clear();
    void clear_entry();
    void remove(unsigned n);

    void move_cursor(bool sign);

    ExpressionInput(sf::RenderWindow* window, sf::Vector2u* window_size, sf::Font* font);

    ExpressionInput() = default;
};
