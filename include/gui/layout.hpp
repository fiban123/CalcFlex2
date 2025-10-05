#pragma once

#include "button.hpp"
#include "text_input.hpp"

#include <vector>
#include <string>

inline const std::vector<std::vector<std::string> > main_buttons = {
    {"C", "CE", "<-", "%", "^"},
    {"!", "(", ")", "^2", "/"},
    {"pi", "7", "8", "9", "*"},
    {"e", "4", "5", "6", "-"},
    {"1/", "1", "2", "3", "+"},
    {"sqrt", ".", "0", ",", "="}
};

struct Layout{
    std::vector<Button> button_vec;
    TextInput expression_input;
    sf::Vector2u window_size;
    sf::Font* font;

    void init();
    void init_expression_input();
    void init_buttons();
    void init_main_buttons();

    void resize_update(sf::Vector2u _window_size);
    void resize_update_buttons();
    void resize_update_expression_input();
    void resize_update_main_buttons();

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw(sf::RenderWindow& window);
    void update_click(sf::Vector2i click_pos);

    Layout(sf::Font* _font, sf::Vector2u _window_size) : font(_font), window_size(_window_size){}; 
};