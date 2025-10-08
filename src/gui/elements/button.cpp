#include "button.hpp"
#include "config.hpp"
#include "point_collide.hpp"

#include <iostream>

void Button::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(label);
}

void Button::update(sf::Vector2i mouse_pos, bool left_click){
    if (point_collide(mouse_pos)){
        if (left_click){
            rect.setFillColor(style->press_bg_color);
        }
        else{
            rect.setFillColor(style->bg_color);
        }
        rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
    }
    else{
        rect.setOutlineThickness(0);
        rect.setFillColor(style->bg_color);
    }
}

bool Button::point_collide(sf::Vector2i pos){
    return rect_point_collide(pos, rect);
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

void Button::update_label(sf::String label_string){
    label = sf::Text(label_string, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f});
}

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback, sf::String _label, ButtonStyle* _style) : 
        style(_style){
    
    rect.setFillColor(style->bg_color);
    rect.setOutlineColor(style->hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);
    callback = _callback;

    label = sf::Text(_label, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({pos.x + size.x / 2.0f, pos.y + size.y / 2.0f});
}