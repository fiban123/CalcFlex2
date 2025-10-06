#include "text_input.hpp"

#include <iostream>

void TextInput::remove(unsigned n, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font){
    string.erase(cursor_string_index - 1, 1);
    cursor_string_index--;
    update_text(font_size, bg_color, text_color, font, spacing);
    update_cursor(text_color, spacing);
}

void TextInput::enter_unicode_char(unsigned c, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font)
{
    if (c == 8 && !string.empty()){
        remove(1, spacing, font_size, bg_color, text_color, font);
    }
    else if (c > 31 && c < 128){
        enter_text(std::string(1, (char) c), 1, text_color, spacing, font_size, bg_color, text_color, font);
    }
}

void TextInput::enter_text(std::string text, unsigned offset, sf::Color cursor_line_color, unsigned spacing, unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font){
    string.insert(cursor_string_index, text);
    cursor_string_index += offset;

    update_text(font_size, bg_color, text_color, font, spacing);
    update_cursor(cursor_line_color, spacing);
}

void TextInput::update_text(unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font &font, unsigned spacing){
    character_width = font.getGlyph('a', font_size, false).advance;

    text = sf::Text(string, font, font_size);

    text.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = text.getLocalBounds();

    text.setOrigin(label_bounds.left + label_bounds.width, label_bounds.top + label_bounds.height / 2.0f);
    
    update_text_pos(spacing);

    if (cursor_string_index >= string.length()){
        cursor_string_index = string.length();
        update_cursor(text_color, spacing);
    }
}

void TextInput::update_text_pos(unsigned spacing){
    text.setPosition({rect.getPosition().x + rect.getSize().x - spacing, rect.getPosition().y + rect.getSize().y / 2.0f});
}

void TextInput::update_cursor(sf::Color cursor_line_color, unsigned spacing){
    float left = rect.getPosition().x;
    float bottom = rect.getPosition().y;
    float x = left + rect.getSize().x - text.getGlobalBounds().width + cursor_string_index * character_width - spacing - 3;

    cursor_line_vertices[0].position = {x, bottom + rect.getSize().y};
    cursor_line_vertices[0].color = cursor_line_color;
    cursor_line_vertices[1].position = {x, bottom};
    cursor_line_vertices[1].color = cursor_line_color;
}

void TextInput::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(text);
    window.draw(cursor_line_vertices.data(), cursor_line_vertices.size(), sf::PrimitiveType::Lines);
}

void TextInput::resize(sf::Vector2f new_size, unsigned spacing, sf::Color cursor_line_color){
    rect.setSize(new_size);
    update_text_pos(spacing);
    update_cursor(cursor_line_color, spacing);
}

TextInput::TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned font_size, sf::Color bg_color, sf::Color text_color, unsigned spacing){
    string = start_text;
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(bg_color);

    update_text(font_size, bg_color, text_color, font, spacing);
    cursor_string_index = start_text.length();
    update_cursor(sf::Color::White, spacing);
}
