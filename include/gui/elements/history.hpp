#pragma once

#include "textarea.hpp"

struct History{
    TextArea text_area;
    TextAreaStyle text_area_style;

    float text_area_pos_x;

    sf::RenderWindow* window;
    sf::Vector2u* window_size;
    sf::Font* font;

    void draw();

    void resize_update();

    void add_entry(std::string string);

    History(sf::RenderWindow* window, sf::Vector2u* window_size, sf::Font* font);

    History() = default;
};