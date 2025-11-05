#include "text_setting.hpp"

#include <iostream>

#include "gui_config.hpp"
#include "point_collide.hpp"

void TextSetting::update(sf::Vector2i mouse_pos, bool left_click) {
    info_button.update(mouse_pos, left_click);
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

void TextSetting::text_entered(unsigned c) {
    if (input.selected) {
        input.enter_unicode_char(c);
    }
}
void TextSetting::update_click(sf::Vector2i mouse_pos) {
    if (rect_point_collide(mouse_pos, rect)) {
        input.selected = true;
        std::cout << "shsdh\n";
    }
    else {
        input.selected = false;
    }
}

void TextSetting::move_cursor(bool sign) {
    if (input.selected) {
        input.move_cursor(sign);
    }
}

TextSetting::TextSetting(std::string& label_string, std::string& setting_str,
                         std::string& info_str, sf::Vector2f pos,
                         TextSettingStyle* _style, float text_input_width, bool _selected)
    : style(_style) {
    // label is at top with info button
    // then comes input field

    label = TextArea(label_string, pos, {0, style->label_height}, &style->label_style,
                     XBound::CENTER, YBound::CENTER);

    float label_max_len = style->label_style.font_size;
    if (!label.text_lines.empty()) {
        label_max_len =
            std::max(label_max_len, label.text_lines[0].getLocalBounds().width);
    }

    label_max_len = label.text_lines[0].getLocalBounds().width;
    label.resize({label_max_len + 2 * style->spacing, style->label_height});

    // button and input
    sf::Vector2f button_pos{pos.x + style->label_style.spacing + label.rect.getSize().x,
                            pos.y};
    info_button = HoverButton(button_pos, {style->label_height, style->label_height}, "i",
                              &style->info_button_style);

    sf::Vector2f input_pos{pos.x, pos.y + style->label_height + style->spacing};

    input =
        TextInput(setting_str, input_pos, {text_input_width, style->text_input_height},
                  &style->input_style, _selected, XBound::LEFT, YBound::CENTER);

    // info

    sf::Vector2f info_pos{button_pos.x + style->label_height, button_pos.y};

    unsigned newline_count = std::ranges::count(info_str, '\n');

    float info_height = (1 + newline_count) *
                        (style->info_style.font_size + style->info_style.entry_spacing);

    info = TextArea(info_str, info_pos, {0, info_height}, &style->info_style,
                    XBound::CENTER, YBound::CENTER);
    info.rect.setOutlineColor(DIM_HIGHLIGHT_COLOR);
    info.rect.setOutlineThickness(1);

    float info_max_len = style->info_style.font_size;
    if (!info.text_lines.empty()) {
        info_max_len = std::max(info_max_len, info.text_lines[0].getLocalBounds().width);
    }

    info.resize({info_max_len + 2 * style->spacing, info_height});
    info.update_text_pos();

    // rect
    rect.setPosition(pos);
    rect.setSize(
        {std::max(label_max_len + style->label_style.spacing + style->label_height,
                  text_input_width),
         style->label_height + style->spacing + style->text_input_height});
}
