#include "text_setting.hpp"

#include <iostream>

void TextSetting::update(sf::Vector2i mouse_pos, bool left_click) {}

TextSetting::TextSetting(std::string& label_string, std::string& setting_str,
                         std::string& info_str, sf::Vector2f pos,
                         TextSettingStyle* _style)
    : style(_style) {
    // label is at top with info button
    // then comes input field

    label = TextArea(label_string, pos, {0, style->label_height}, &style->label_style,
                     XBound::LEFT, YBound::CENTER);

    float max_len = style->label_style.font_size;
    if (!label.text_lines.empty()) {
        max_len = std::max(max_len, label.text_lines[0].getLocalBounds().width);
    }

    max_len = label.text_lines[0].getLocalBounds().width;
    label.resize({max_len + 2 * style->spacing, style->label_height});

    sf::Vector2f button_pos{pos.x + style->label_style.spacing + label.rect.getSize().x,
                            pos.y};
    info_button = HoverButton(button_pos, {style->label_height, style->label_height}, "i",
                              &style->info_button_style);

    sf::Vector2f input_pos{pos.x, pos.y + style->label_height + style->spacing};

    input =
        TextInput(setting_str, input_pos, style->text_input_size, &style->input_style);

    sf::Vector2f info_pos{button_pos.x, button_pos.y};

    unsigned newline_count = std::ranges::count(info_str, '\n');

    float info_height = (1 + newline_count) *
                        (style->info_style.font_size + style->info_style.entry_spacing);

    std::cout << info_height << std::endl;

    info = TextArea(info_str, info_pos, {0, info_height}, &style->info_style,
                    XBound::LEFT, YBound::TOP);

    max_len = style->info_style.font_size;
    if (!info.text_lines.empty()) {
        max_len = std::max(max_len, info.text_lines[0].getLocalBounds().width);
    }

    info.resize({max_len + 2 * style->spacing, info_height});
    info.update_text_pos();
}

void TextSetting::update_pos(sf::Vector2f pos) {}

void TextSetting::draw(sf::RenderWindow& window) {
    label.draw(window);
    info_button.draw(window);
    input.draw(window);
    if (info_button.hovering) {
        info.draw(window);
    }
}
