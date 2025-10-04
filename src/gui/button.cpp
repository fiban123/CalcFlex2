#include "button.hpp"
#include "config.hpp"

#include <iostream>

void Button::draw(sf::RenderWindow* window){
    window->draw(rect);
}

bool Button::point_collide(sf::Vector2i pos){
    return pos.x > rect.getPosition().x && pos.x < rect.getPosition().x + rect.getSize().x &&
           pos.y > rect.getPosition().y && pos.y < rect.getPosition().y + rect.getSize().y;
}


void Button::update(sf::Vector2i mouse_pos){

    if(point_collide(mouse_pos)){
        std::cout << "hj\n";
        rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
    }
    else{
        rect.setOutlineThickness(0);
    }
}

void Button::update_click(sf::Vector2i click_pos){
    if (point_collide(click_pos)){
        std::cout << "isjdisdj\n";
    }
}

void Button::set_text(std::string text){

}

Button::Button(sf::Color _bg_color, sf::Color _hover_border_color, sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback){
    rect.setFillColor(_bg_color);
    rect.setOutlineColor(_hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);
    callback = _callback;
}
