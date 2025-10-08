#include "checkbox.hpp"


#include "button.hpp"
#include "gui_config.hpp"
#include "point_collide.hpp"

#include <iostream>

void Checkbox::draw(sf::RenderWindow& window){

    window.draw(rect);
    window.draw(label);
}

void Checkbox::update(sf::Vector2i mouse_pos, bool left_click){
    if (point_collide(mouse_pos)){
        if (left_click){
            rect.setFillColor(style->press_bg_color);
        }
        else{
            rect.setFillColor(style->bg_color);
        }
        rect.setOutlineColor(style->hover_border_color);
    }
    else{
        rect.setOutlineColor(sf::Color::Transparent);
        if (checked){
            rect.setOutlineColor(style->checked_border_color);
        }
        rect.setFillColor(style->bg_color);
    }
}

bool Checkbox::point_collide(sf::Vector2i pos){
    return rect_point_collide(pos, rect);
}


void Checkbox::update_click(sf::Vector2i click_pos){
    if (point_collide(click_pos)){
        checked = !checked;
        callback();
    }
}

void Checkbox::update_pos(sf::Vector2f new_pos){
    rect.setPosition(new_pos);

    label.setPosition({new_pos.x + rect.getSize().x / 2.0f, new_pos.y + rect.getSize().y / 2.0f});
}

void Checkbox::update_label(sf::String label_string){
    label = sf::Text(label_string, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f});
}

Checkbox::Checkbox(sf::Vector2f pos, sf::Vector2f size, std::function<void()> _callback, sf::String _label, CheckboxStyle* _style, bool _checked) : 
        style(_style), checked(_checked){
    
    rect.setFillColor(style->bg_color);
    rect.setOutlineColor(style->hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
    callback = _callback;

    label = sf::Text(_label, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({pos.x + size.x / 2.0f, pos.y + size.y / 2.0f});
}