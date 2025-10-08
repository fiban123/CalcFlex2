#pragma once

#include "gui_config.hpp"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <vector>

struct Lines{
    sf::RenderWindow* window;
    sf::Vector2u* window_size;

    std::vector<sf::Vertex> line_vertices;

    void draw();

    void resize_update();

    void update_lines();

    Lines(sf::RenderWindow* _window, sf::Vector2u* _window_size);
};