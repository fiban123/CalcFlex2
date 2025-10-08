#pragma once

#include "textarea.hpp"
#include "button.hpp"

struct InfoBar{
    TextArea text_area;
    TextAreaStyle text_area_style;

    ButtonStyle info_button_style;
    Button info_button;

    sf::RenderWindow* window;
    sf::Vector2u* window_size;
    sf::Font* font;

    void info_button_callback();

    void draw();
    void update(sf::Vector2i mouse_pos, bool left_click);
    void update_click(sf::Vector2i click_pos);

    void resize_update();

    void set_string(std::string string);

    InfoBar(sf::RenderWindow* window, sf::Vector2u* window_size, sf::Font* font);

    InfoBar() = default;
};