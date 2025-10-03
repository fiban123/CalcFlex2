#include "button.hpp"
#include "config.hpp"

#include <iostream>

void Button::draw(sf::RenderWindow* window){
    window->draw(rect);
}

void Button::update(sf::RenderWindow* window){
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);

    if(
        mouse_pos.x > rect.getPosition().x && mouse_pos.x < rect.getPosition().x + rect.getSize().x &&
        mouse_pos.y > rect.getPosition().y && mouse_pos.y < rect.getPosition().y + rect.getSize().y ){
            rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                callback();
            }
    }
    else{
        rect.setOutlineThickness(0);
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
