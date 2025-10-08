#pragma once


#define SFML_STATIC
#include <SFML/Graphics.hpp>


struct TextElement{
    std::string string;
    sf::Text text;
    unsigned character_width;
    size_t cursor_string_index = 0;
    
    TextAreaStyle* style;

    sf::RectangleShape rect;

    void update_text();
    void update_text_pos();

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size);

    TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, TextAreaStyle* _style);

    TextInput() = default;
};