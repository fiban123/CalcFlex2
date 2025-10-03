#pragma once

#include <SFML/Graphics.hpp>
#include <string>

struct Button{
    sf::RectangleShape rect;

    void draw();

    void set_text(std::string text);
};