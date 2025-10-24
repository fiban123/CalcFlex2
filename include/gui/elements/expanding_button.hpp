#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include "checkbox.hpp"
#include <string>
#include <functional>

struct ExpandingButton{
    sf::RectangleShape rect;
    sf::Vector2f expanded_bound_rect_pos;
    sf::Vector2f expanded_bound_rect_size;

    sf::Text label;

    CheckboxStyle* style;

    std::vector<Checkbox> expanding_checkboxes;

    std::function<void(size_t, size_t)> callback;
    std::vector<std::vector<std::string> >* labels;
    std::vector<std::vector<bool*> >* states;;;

    bool hovering = false;
    bool expanded = false;

    bool point_collide(sf::Vector2i pos);

    void draw(sf::RenderWindow& window);

    void update(sf::Vector2i mouse_pos, bool left_click);

    void update_click(sf::Vector2i click_pos);

    void update_pos(sf::Vector2f new_pos);
    void update_label(sf::String label_string);

    ExpandingButton(sf::Vector2f pos, sf::Vector2f size, std::function<void(size_t, size_t)> _callback, 
                    sf::String _label, CheckboxStyle* _style, std::vector<std::vector<std::string> >* _labels,
                    std::vector<std::vector<bool> >& initial_states, std::vector<std::vector<bool*> >* _states);

    ExpandingButton() = default;
};