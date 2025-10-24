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
    bool colliding = point_collide(mouse_pos);

    if (expanded){
        colliding = colliding || rect_point_collide(mouse_pos, expanded_bound_rect_pos, expanded_bound_rect_size);
    }

    if (colliding){
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
        checkbox.update_click(click_pos);
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

ExpandingButton::ExpandingButton(   sf::Vector2f pos, sf::Vector2f size, std::function<void(size_t, size_t)> _callback, 
                                    sf::String _label, CheckboxStyle* _style, std::vector<std::vector<std::string> >* _labels,
                                    std::vector<std::vector<bool> >& initial_states, std::vector<std::vector<bool*> >* _states) : 
        callback(_callback), style(_style), labels(_labels), states(_states){

    rect.setFillColor(style->bg_color);
    rect.setOutlineColor(style->hover_border_color);
    rect.setPosition(pos);
    rect.setSize(size);

    label = sf::Text(_label, *style->font, style->font_size);
    label.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = label.getLocalBounds();
    label.setOrigin(label_bounds.left + label_bounds.width / 2.0f, label_bounds.top + label_bounds.height / 2.0f);

    label.setPosition({pos.x + size.x / 2.0f, pos.y + size.y / 2.0f});

    size_t rows = labels->size();
    size_t cols;
    if (rows == 0){
        cols = 0;
    }
    else{
        cols = labels->at(0).size();
    }
    

    // initialize states
    states->resize(rows);
    for (size_t i = 0; i < rows; i++){
        states->at(i).resize(cols);
    }

    sf::Vector2f start = {pos.x + BUTTON_SIZE, pos.y};

    // initialize checkboxes
    expanding_checkboxes.reserve(cols * rows);

    for (size_t col = 0; col < cols; col++){
        for (size_t row = 0; row < rows; row++){
            float x = start.x + col * BUTTON_SIZE;
            float y = start.y + row * BUTTON_SIZE;

            expanding_checkboxes.emplace_back(  sf::Vector2f{x, y}, sf::Vector2f{BUTTON_SIZE, BUTTON_SIZE}, 
                                                [this, col, row]{callback(col, row);}, labels->at(row)[col], style, 
                                                initial_states[row][col]
            );

            //expanding_checkboxes.back().callback();

            states->at(row)[col] = &(expanding_checkboxes.back().checked);
        }
    }
    if (rows != 0){
        //expanding_checkboxes.back().callback();
    }

    // init bounding box
    expanded_bound_rect_pos = start;
    expanded_bound_rect_size = {cols * BUTTON_SIZE, rows * BUTTON_SIZE};
}