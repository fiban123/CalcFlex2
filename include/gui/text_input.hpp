#pragma once

#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <string>

struct TextInput{
    std::string string;
    sf::Text text;
    size_t cursor_string_index;

    sf::Vertex cursor_line_start;
    sf::Vertex cursor_line_end;

    sf::RectangleShape rect;

    void update_text(unsigned font_size, sf::Color bg_color, sf::Color text_color, sf::Font& font, unsigned spacing);
    void update_text_pos(unsigned spacing);

    void draw(sf::RenderWindow& window);

    void resize(sf::Vector2f new_size, unsigned spacing);

    TextInput(std::string start_text, sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned font_size, sf::Color bg_color, sf::Color text_color, unsigned spacing);

    TextInput() = default;
};