#pragma once

#include "button.hpp"
#include "hover_button.hpp"
#include "text_input.hpp"
#include "textarea.hpp"

struct TextSettingStyle {
    float label_height;
    sf::Vector2f text_input_size;
    float spacing;

    TextAreaStyle label_style;
    TextAreaStyle info_style;
    TextInputStyle input_style;
    HoverButtonStyle info_button_style;
};

struct TextSetting {
    TextInput input;
    TextArea label;
    TextArea info;
    HoverButton info_button;

    TextSettingStyle* style;

    void update(sf::Vector2i mouse_pos, bool left_click);
    void update_pos(sf::Vector2f pos);
    void draw(sf::RenderWindow& window);

    TextSetting(std::string& label_string, std::string& setting_str,
                std::string& info_str, sf::Vector2f pos, TextSettingStyle* style);

    TextSetting() = default;
};
