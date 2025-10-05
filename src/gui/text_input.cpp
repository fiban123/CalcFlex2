#include "text_input.hpp"

#include <iostream>

void TextInput::update_text(unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font& font, unsigned spacing){
    text = sf::Text(string, font, font_size);

    text.setFillColor(sf::Color::White);

    std::cout << font.getInfo().family << "\n";

    sf::FloatRect label_bounds = text.getLocalBounds();

    text.setOrigin(label_bounds.left + label_bounds.width, label_bounds.top + label_bounds.height / 2.0f);
    
    update_text_pos(spacing);
}

void TextInput::update_text_pos(unsigned spacing){
    text.setPosition({rect.getPosition().x + rect.getSize().x - spacing, rect.getPosition().y + rect.getSize().y / 2.0f});
}

void TextInput::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(text);
}

void TextInput::resize(sf::Vector2f new_size, unsigned spacing){
    rect.setSize(new_size);
    update_text_pos(spacing);
}

TextInput::TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned font_size, sf::Color bg_color, sf::Color text_color, unsigned spacing){
    string = start_text;
    rect.setPosition(pos);
    rect.setSize(size);
    rect.setFillColor(bg_color);

    update_text(font_size, bg_color, text_color, font, spacing);
}
