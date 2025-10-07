#pragma once


#define SFML_STATIC
#include <SFML/Graphics.hpp>

bool rect_point_collide(sf::Vector2i pos, sf::RectangleShape& rect);

bool rect_point_collide(sf::Vector2i pos, sf::Vector2f rect_pos, sf::Vector2f rect_size);
