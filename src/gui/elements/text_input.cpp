#include "text_input.hpp"

#include <iostream>

void TextInput::remove(unsigned n){
    n = std::min(cursor_string_index, (size_t) n);
    if (cursor_string_index != 0){
        string.erase(cursor_string_index - 1, n);
    }
    cursor_string_index -= n;

    update_text();
    update_cursor();
}

void TextInput::enter_unicode_char(unsigned c)
{
    if (c == 8 && !string.empty()){
        remove(1);
    }
    else if (c > 31 && c < 128){
        enter_text(std::string(1, (char) c), 1);
    }
}

void TextInput::enter_text(std::string text, unsigned offset){
    string.insert(cursor_string_index, text);
    cursor_string_index += offset;

    update_text();
    update_cursor();
}

void TextInput::update_text(){
    character_width = style->font->getGlyph('a', style->font_size, false).advance;

    text = sf::Text(string, *style->font, style->font_size);

    text.setFillColor(sf::Color::White);

    sf::FloatRect label_bounds = text.getLocalBounds();

    text.setOrigin(label_bounds.left + label_bounds.width, label_bounds.top + label_bounds.height / 2.0f);
    
    update_text_pos();

    if (cursor_string_index >= string.length()){
        cursor_string_index = string.length();
        update_cursor();
    }
}

void TextInput::update_text_pos(
){
    text.setPosition({rect.getPosition().x + rect.getSize().x - style->spacing, rect.getPosition().y + rect.getSize().y / 2.0f});
}

void TextInput::update_cursor(){
    float left = rect.getPosition().x;
    float bottom = rect.getPosition().y;
    float x = left + rect.getSize().x - text.getGlobalBounds().width + cursor_string_index * character_width - style->spacing - 3;

    cursor_line_vertices[0].position = {x, bottom + rect.getSize().y};
    cursor_line_vertices[0].color = style->cursor_color;
    cursor_line_vertices[1].position = {x, bottom};
    cursor_line_vertices[1].color = style->cursor_color;
}

void TextInput::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(text);
    window.draw(cursor_line_vertices.data(), cursor_line_vertices.size(), sf::PrimitiveType::Lines);
}

void TextInput::resize(sf::Vector2f new_size){
    rect.setSize(new_size);
    update_text_pos();
    update_cursor();
}

TextInput::TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, TextInputStyle* _style) :
        style(_style){
    string = start_text;
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(style->bg_color);

    update_text();
    cursor_string_index = start_text.length();
    update_cursor();
}
