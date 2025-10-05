#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>

#include <functional>

struct Button{
    sf::RectangleShape rect;
    sf::Text label;

    std::function<void()> callback;

    bool point_collide(sf::Vector2i pos);


    void draw(sf::RenderWindow& window);

    void update(sf::Vector2i mouse_pos, bool left_click, sf::Color bg_color, sf::Color click_bg_color);

    void update_click(sf::Vector2i click_pos);

    void update_pos(sf::Vector2f new_pos);

    Button(sf::Color _bg_color, sf::Color _hover_border_color, sf::Color _click_bg_color, sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback, sf::String _label, sf::Font* font, unsigned font_size);
};