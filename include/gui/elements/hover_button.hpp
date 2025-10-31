#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>

struct HoverButtonStyle {
    sf::Color bg_color;
    sf::Color hover_border_color;
    sf::Color text_color;
    sf::Font* font;
    float outline_thickness;
    float spacing;
    unsigned font_size;
};

struct HoverButton {
    sf::RectangleShape rect;
    sf::Text label;

    bool hovering = false;
    HoverButtonStyle* style;

    bool point_collide(sf::Vector2i pos);
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2i mouse_pos, bool left_click);

    void update_pos(sf::Vector2f new_pos);
    void update_label(std::string new_label);

    HoverButton(sf::Vector2f pos, sf::Vector2f size, std::string _label,
                HoverButtonStyle* _style);

    HoverButton() = default;
};
