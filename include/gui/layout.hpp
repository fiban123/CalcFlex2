#pragma once

#include "button.hpp"
#include "text_input.hpp"
#include "config.hpp"

#include <vector>
#include <string>

inline const std::vector<std::vector<std::string> > main_button_labels = MAIN_BUTTON_LABELS;
inline const std::vector<std::vector<std::string> > main_button_strings = MAIN_BUTTON_STRINGS;
inline const std::vector<std::vector<int> > main_button_offsets = MAIN_BUTTON_OFFSETS;

struct Layout{
    std::vector<Button> button_vec;
    TextInput expression_input;
    sf::Vector2u window_size;
    sf::Font* font;

    void button_callback(size_t bx, size_t by);

    void init();
    void init_expression_input();
    void init_buttons();
    void init_main_buttons();

    void resize_update(sf::Vector2u _window_size);
    void resize_update_buttons();
    void resize_update_expression_input();
    void resize_update_main_buttons();

    void text_entered(unsigned c);
    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw(sf::RenderWindow& window);
    void update_click(sf::Vector2i click_pos);

    Layout(sf::Font* _font, sf::Vector2u _window_size) : font(_font), window_size(_window_size){}; 
};