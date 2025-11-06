#include "text_input.hpp"

#include <iostream>

void TextInput::remove(unsigned n) {
    n = std::min(cursor_string_index, (size_t)n);
    if (cursor_string_index != 0) {
        text_area.string.erase(cursor_string_index - 1, n);
    }
    cursor_string_index -= n;

    update_text();
    update_cursor();
}

void TextInput::enter_unicode_char(unsigned c) {
    if (c == 8 && !text_area.string.empty()) {
        remove(1);
    }
    else if (c > 31 && c < 128) {
        enter_text(std::string(1, (char)c), 1);
    }
}

void TextInput::enter_text(std::string text, unsigned offset) {
    text_area.string.insert(cursor_string_index, text);
    cursor_string_index += offset;

    update_text();
    update_cursor();
}

void TextInput::move_cursor(bool sign) {
    ssize_t new_pos =
        sign ? cursor_string_index + 1 : cursor_string_index - 1;
    cursor_string_index =
        std::clamp(new_pos, 0ll, (ssize_t)text_area.string.length());

    update_cursor();
}

void TextInput::update_style() {
    text_area.update_style();
    update_cursor();
}

void TextInput::update_selected() {
    if (selected) {
        text_area.style = &style->selected_text_area_style;
    }
    else {
        text_area.style = &style->text_area_style;
    }
    update_text();
}

void TextInput::update_text() {
    text_area.update_text();
    character_width =
        style->text_area_style.font
            ->getGlyph('a', style->text_area_style.font_size, false)
            .advance;

    if (cursor_string_index >= text_area.string.length()) {
        cursor_string_index = text_area.string.length();
        update_cursor();
    }
}

void TextInput::update_text_pos() { text_area.update_text_pos(); }

void TextInput::update_cursor() {
    float bottom = text_area.rect.getPosition().y;
    float x;
    std::cout << "ushduwdhwduhdsdhuwdhn\n\n";
    if (text_area.text_lines.size() == 0) {
        std::cout << "ka2\n";
        switch (text_area.xbound) {
            case (XBound::LEFT): {
                x = text_area.rect.getPosition().x;
                break;
            }
            case (XBound::RIGHT): {
                x = text_area.rect.getPosition().x +
                    text_area.rect.getLocalBounds().width;
                break;
            }
            case (XBound::CENTER): {
                x = text_area.rect.getPosition().x +
                    text_area.rect.getLocalBounds().width / 2.f;
                break;
            }
        }
    }

    else {
        std::cout << "ka1\n";
        float left = text_area.text_lines[0].getPosition().x;
        std::cout << left << " " << cursor_string_index << " "
                  << character_width << "\n";
        x = left + cursor_string_index * character_width;
    }

    std::cout << x << "\n";

    cursor_line_vertices[0].position = {
        x, bottom + text_area.rect.getSize().y};
    cursor_line_vertices[0].color = style->cursor_color;
    cursor_line_vertices[1].position = {x, bottom};
    cursor_line_vertices[1].color = style->cursor_color;
}

void TextInput::draw(sf::RenderWindow& window) {
    text_area.draw(window);
    if (selected) {
        window.draw(cursor_line_vertices.data(),
                    cursor_line_vertices.size(),
                    sf::PrimitiveType::Lines);
    }
}

void TextInput::resize(sf::Vector2f new_size) {
    text_area.resize(new_size);
    update_cursor();
}

TextInput::TextInput(std::string start_text,
                     sf::Vector2f pos,
                     sf::Vector2f size,
                     TextInputStyle* _style,
                     bool _selected,
                     XBound _xbound,
                     YBound _ybound)
    : style(_style), selected(_selected) {
    text_area = TextArea(start_text,
                         pos,
                         size,
                         &style->text_area_style,
                         _xbound,
                         _ybound);
    cursor_string_index = start_text.length();
    update_text();
    update_cursor();
}
