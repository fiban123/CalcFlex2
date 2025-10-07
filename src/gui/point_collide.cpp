#include "point_collide.hpp"

bool rect_point_collide(sf::Vector2i pos, sf::RectangleShape& rect){
    return rect_point_collide(pos, rect.getPosition(), rect.getSize());
}

bool rect_point_collide(sf::Vector2i pos, sf::Vector2f rect_pos, sf::Vector2f rect_size){
    return pos.x > rect_pos.x && pos.x < rect_pos.x + rect_size.x &&
           pos.y > rect_pos.y && pos.y < rect_pos.y + rect_size.y;
}
