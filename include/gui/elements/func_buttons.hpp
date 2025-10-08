#pragma once

#include "button.hpp"
#include "checkbox.hpp"

#include "gui_config.hpp"

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <vector>

inline const std::vector<std::string> func_group_button_labels = FUNCTION_GROUP_BUTTON_LABELS;
inline const std::vector<bool> func_group_button_states = FUNCTION_GROUP_BUTTON_STATES;

inline const std::vector<std::vector<std::string> > func_button_labels = FUNCTION_BUTTON_LABELS;
inline const std::vector<std::vector<std::string> > func_button_strings = FUNCTION_BUTTON_STRINGS;
inline const std::vector<std::vector<unsigned> > func_button_offsets = FUNCTION_BUTTON_OFFSETS;


struct FunctionButton{
    Button b;
    sf::Vector2f pos;
    std::string label;

    FunctionButton() = default;
};

struct FunctionButtons{
    sf::RenderWindow* window;
    sf::Vector2u* window_size;
    sf::Font* font;

    float y_offset;

    CheckboxStyle checkbox_style;
    ButtonStyle button_style;

    std::vector<Checkbox> func_groups;
    
    std::vector<FunctionButton> func_buttons;
    std::vector<sf::Vertex> func_group_delimeters;
    std::vector<sf::Vertex> func_group_delimeters_transformed;

    sf::Vector2f rect_pos;
    sf::Vector2f rect_pos_transformed;
    sf::Vector2f rect_size;

    sf::RectangleShape black_rect;

    std::function<void(std::string, unsigned)> func_callback;

    void group_button_callback();

    void draw();
    void update(sf::Vector2i mouse_pos, bool left_click);
    void update_click(sf::Vector2i click_pos);
    void update_scroll(sf::Vector2i mouse_pos, float delta);
    //void update_scroll(float delta);
    void resize_update();
    void update_button_offsets();
    
    void update_buttons();

    FunctionButtons(sf::RenderWindow* _window, sf::Vector2u* _window_size, sf::Font* _font, std::function<void(std::string, unsigned)> func_callback);
};

