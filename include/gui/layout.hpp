#pragma once

#include "text_input.hpp"
#include "main_buttons.hpp"
#include "expression_input.hpp"
#include "config.hpp"

#include <vector>
#include <string>


struct Layout{
    sf::Font* font;
    sf::Vector2u window_size;
    sf::RenderWindow* window;

    MainButtons main_buttons;

    ExpressionInput expression_input;

    void button_callback(size_t bx, size_t by);

    void resize_update(sf::Vector2u _window_size);

    void text_entered(unsigned c);
    void move_cursor(bool sign);

    void update(sf::Vector2i mouse_pos, bool left_click);
    void draw(sf::RenderWindow& window);
    void update_click(sf::Vector2i click_pos);

    Layout(sf::Font* _font, sf::Vector2u _window_size, sf::RenderWindow* _window);
};