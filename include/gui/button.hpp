#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>

#include <functional>

struct Button{
    sf::RectangleShape rect;

    std::function<void()> callback;


    void draw(sf::RenderWindow* window);

    void update(sf::RenderWindow* window);

    void set_text(std::string text);

    Button(sf::Color _bg_color, sf::Color _hover_border_color, sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback);
};