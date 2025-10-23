#include "expanding_button.hpp"
#include "gui_config.hpp"
#include "point_collide.hpp"

#include <iostream>

void ExpandingButton::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(label);

    if (expanded){
        for (Checkbox& checkbox : expanding_checkboxes){
            checkbox.draw(window);
        }
    }

}

void ExpandingButton::update(sf::Vector2i mouse_pos, bool left_click){
    if (point_collide(mouse_pos)){
        rect.setOutlineThickness(-BUTTON_OUTLINE_WIDTH);
        expanded = true;
        for (Checkbox& checkbox : expanding_checkboxes){
            checkbox.update(mouse_pos, left_click);
        }

    }
    else{
        rect.setOutlineThickness(0);
        expanded = false;
    }
}

bool ExpandingButton::point_collide(sf::Vector2i pos){
    return rect_point_collide(pos, rect);
}


void ExpandingButton::update_click(sf::Vector2i click_pos){
    for (Checkbox& checkbox : expanding_checkboxes){
        if (checkbox.point_collide(click_pos)){
            checkbox.checked = !checkbox.checked;
        }
    }
}

void ExpandingButton::update_pos(sf::Vector2f new_pos){
    rect.setPosition(new_pos);

    label.setPosition({new_pos.x + rect.getSize().x / 2.0f, new_pos.y + rect.getSize().y / 2.0f});
}

void ExpandingButton::update_label(sf::String label_string){
    label = sf::Text(label_string, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({rect.getPosition().x + rect.getSize().x / 2.0f, rect.getPosition().y + rect.getSize().y / 2.0f});
}

ExpandingButton::ExpandingButton(sf::Vector2f pos, sf::Vector2f size, std::function<void(size_t, size_t)> _callback, sf::String _label, 
                                CheckboxStyle* _style, std::vector<std::vector<std::string> >* _labels,
                                std::vector<std::vector<bool> >* checked,
                                std::function<void(size_t, size_t)> callback) : 
        callback(_callback), style(_style), labels(_labels){
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

    // initialize checkboxes
    for (size_t col = 0; col < labels->at(0).size(); col++){
        for (size_t row = 0; row < labels->size(); row++){
            float x = pos.x + col * BUTTON_SIZE;
            float y = pos.y + row * BUTTON_SIZE;

            expanding_checkboxes.emplace_back(  sf::Vector2f{x, y}, sf::Vector2f{BUTTON_SIZE, BUTTON_SIZE}, 
                                                []{}, labels->at(row)[col], style, 
                                                checked->at(row)[col]);
        }
    }
}