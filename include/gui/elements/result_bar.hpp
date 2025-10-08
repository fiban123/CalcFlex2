#pragma once

#include "textarea.hpp"
#include "button.hpp"

struct ResultBar{
    TextArea text_area;
    TextAreaStyle text_area_style;

    sf::RenderWindow* window;
    sf::Vector2u* window_size;
    sf::Font* font;

    void draw();

    void resize_update();

    void set_string(std::string string);

    ResultBar(sf::RenderWindow* window, sf::Vector2u* window_size, sf::Font* font);

    ResultBar() = default;
};