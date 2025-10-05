#include "button.hpp"
#include "config.hpp"

#include <iostream>

void Button::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(label);

}

bool Button::point_collide(sf::Vector2i pos){
    return pos.x > rect.getPosition().x && pos.x < rect.getPosition().x + rect.getSize().x &&
           pos.y > rect.getPosition().y && pos.y < rect.getPosition().y + rect.getSize().y;
}


void Button::update(sf::Vector2i mouse_pos, bool left_click){
    if(point_collide(mouse_pos)){
        if (left_click){
            rect.setFillColor(click_bg_color);
        }
        else{
            rect.setFillColor(bg_color);
        }
        rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
    }
    else{
        rect.setOutlineThickness(0);
        rect.setFillColor(bg_color);
    }
}

void Button::update_click(sf::Vector2i click_pos){
    if (point_collide(click_pos)){
        callback();
    }
}

void Button::update_pos(sf::Vector2f new_pos){
    rect.setPosition(new_pos);

    label.setPosition({new_pos.x + rect.getSize().x / 2.0f, new_pos.y + rect.getSize().y / 2.0f});
}

Button::Button(sf::Color _bg_color, sf::Color _hover_border_color, sf::Color _click_bg_color, sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback, sf::String _label, sf::Font& font){
    rect.setFillColor(_bg_color);
    rect.setOutlineColor(_hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);
    click_bg_color = _click_bg_color;
    bg_color = _bg_color;
    callback = _callback;

    label = sf::Text(_label, font, 22);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({pos.x + size.x / 2.0f, pos.y + size.y / 2.0f});
}
