#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <string>
#include <functional>

struct CheckboxStyle{
    sf::Color bg_color;
    sf::Color hover_border_color;
    sf::Color press_bg_color;
    sf::Color checked_border_color;
    sf::Color unchecked_border_color;
    sf::Font* font;
    unsigned font_size;
};

struct Checkbox{
    sf::RectangleShape rect;
    sf::Text label;

    bool checked;
    bool hovering;

    std::function<void()> callback;

    CheckboxStyle* style;

    bool point_collide(sf::Vector2i pos);

    void draw(sf::RenderWindow& window);

    void update(sf::Vector2i mouse_pos, bool left_click);

    void update_click(sf::Vector2i click_pos);

    void update_pos(sf::Vector2f new_pos);
    void update_label(sf::String label_string);

    Checkbox(sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback, sf::String _label, CheckboxStyle* style, bool checked);
};